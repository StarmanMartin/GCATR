//
// Created by Martin on 13.07.2018.
//

#include "BDATools.h"
#include "../codes/Acid.h"
#include "../interfaces/AbstractTupleContainer.h"
#include <memory>
#include <sstream>
#include <utility>

using namespace BDA;


BDATools::BDATools(std::shared_ptr<AbstractTupleContainer> code) : code(std::move(code)) {
    this->rules = {};
}

bool BDATools::add_rule(unsigned int i_1, unsigned int i_2, char Q_11, char Q_12, char Q_21, char Q_22) {
    BDA_Rule rule(i_1, i_2, Q_11, Q_12, Q_21, Q_22);
    return this->add_rule(rule);
}

bool BDATools::add_rule(const BDA_Rule& rule) {
    if (this->validate_rule(rule)) {
        this->rules.push_back(rule);
        return true;
    }

    return false;
}

std::vector<std::string> BDATools::run_bda_for_all_rna_codons() {
    auto code_vec = this->get_all_rna_codons();

    std::vector<std::string> result_vec(code_vec.size());

    return this->run_bda_for_code(code_vec);

}

std::vector<std::string> BDATools::run_bda_for_code() {
    auto code_vec = this->code->get_tuples();


    if (this->code->get_word_length()[0] != BDA_WORD_LENGTH) {
        this->add_error_msg("Bda only developed for word length of 3");
    }

    if (this->code->get_word_length().size() != 1) {
        this->add_error_msg("No mixed codes allowed.");
        return {};
    }
    
    return this->run_bda_for_code(code_vec);
}

std::vector<std::string> BDATools::run_bda_for_code(std::vector<std::string> code_vec) {
    
    std::vector<std::string> result_vec(code_vec.size());


    for (const BDA_Rule& rule : this->rules) {
        for (size_t i = 0; i < code_vec.size(); ++i) {
            std::stringstream os;
            if (code_vec[i][rule.i_1] == rule.Q_12) {
                os << result_vec[i] << "1";
            } else if (code_vec[i][rule.i_1] == rule.Q_11) {
                os << result_vec[i] << "0";
            } else {
                if (code_vec[i][rule.i_2] == rule.Q_21 || code_vec[i][rule.i_2] == rule.Q_22) {
                    os << result_vec[i] << "0";
                } else {
                    os << result_vec[i] << "1";
                }
            }

            result_vec[i] = os.str();
        }
    }

    return result_vec;
}



std::shared_ptr<AbstractTupleContainer> BDATools::get_code() {
    return this->code;
}

bool BDATools::validate_rule(const BDA_Rule& rule) {
    if (rule.i_1 == rule.i_2) {
        this->add_error_msg("i1 must not be equal to i2");
        return false;
    }

    if ((rule.i_1 >= BDA_WORD_LENGTH) || (rule.i_2 >= BDA_WORD_LENGTH)) {
        this->add_error_msg("i1 must not bebetween 1 and 3");
        return false;
    }

    std::stringstream os;

    os << rule.Q_11 << rule.Q_12 << rule.Q_21 << rule.Q_22;
    if (!acid::is_acid_type(os.str(), this->code->get_acid())) {
        auto acid_name = acid::acid_to_string(this->code->get_acid());
        this->add_error_msg("The code is a " + acid_name + " code. The rule bases have to be " + acid_name);
        return false;
    }

    return true;
}

 std::vector<std::string> BDATools::get_all_rna_codons() {
    std::vector<std::string> result(64);
    int s = 0;
    for (int i = 0; i < acid::acid_base_length; ++i) {
        for (int j = 0; j < acid::acid_base_length; ++j) {
            for (int k = 0; k < acid::acid_base_length; ++k) {
                std::string codon = std::string(1,acid::rna[i]) +  std::string(1,acid::rna[k]) + std::string(1,acid::rna[j]);
                result[s] = codon;
                s++;
            }
        }
    }

    return result;
}
