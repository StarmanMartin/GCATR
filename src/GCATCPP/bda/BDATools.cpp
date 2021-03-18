//
// Created by Martin on 13.07.2018.
//

#include "BDATools.h"
#include "../codes/Acid.h"
#include "../interfaces/AbstractTupleContainer.h"
#include "../sequences/Sequence.h"
#include <memory>
#include <sstream>
#include <math.h>
#include <utility>

using namespace BDA;


BDATools::BDATools(std::shared_ptr<AbstractTupleContainer> code) : code(std::move(code)) {
    this->rules = {};
    this->tuple_size = this->code->get_word_length()[0];
}


BDATools::BDATools(const std::string &sequence, int tuple_length) : tuple_size(tuple_length) {
    this->rules = {};
    this->code = std::make_shared<Sequence>(sequence, tuple_length);
    this->tuple_size = this->code->get_word_length()[0];
}

bool BDATools::r_add_rule(unsigned int i_1, unsigned int i_2, char Q_11, char Q_12, char Q_21, char Q_22) {
    return this->add_rule(i_1, i_2, Q_11, Q_12, Q_21, Q_22);
}

bool BDATools::add_rule(unsigned int i_1, unsigned int i_2, char Q_11, char Q_12, char Q_21, char Q_22) {
    BDA_Rule rule(i_1, i_2, Q_11, Q_12, Q_21, Q_22);
    return this->add_rule(rule);
}

bool BDATools::add_rule(const BDA_Rule &rule) {
    if (this->validate_rule(rule)) {
        this->rules.push_back(rule);
        return true;
    }

    return false;
}

std::vector<BDA_Rule> BDATools::get_rules() {
    return this->rules;
}

std::vector<std::string> BDATools::run_bda_for_all_rna_codons() {
    auto code_vec = BDA::BDATools::get_all_rna_codons();

    return this->_run_bda_for_code(code_vec);

}

std::vector<std::string> BDATools::run_bda_for_code() {
    auto code_vec = this->code->get_tuples();

    if (this->tuple_size < BDA_WORD_LENGTH) {
        this->add_error_msg("Bda only developed for word length of at least 3");
    }

    if (this->code->get_word_length().size() != 1) {
        this->add_error_msg("No mixed codes allowed.");
        return {};
    }

    return this->_run_bda_for_code(code_vec);
}

std::vector<std::string> BDATools::_run_bda_for_code(std::vector<std::string> code_vec) {

    std::vector<std::string> result_vec(code_vec.size() * 2);

    for (size_t idx = 0; idx < code_vec.size(); ++idx) {
        size_t i = idx * 2;
        result_vec[i] = code_vec[idx];
        ++i;
        for (const BDA_Rule &rule : this->rules) {
            std::stringstream os;
            if (code_vec[idx][rule.i_1] == rule.Q_12) {
                os << result_vec[i] << "1";
            } else if (code_vec[idx][rule.i_1] == rule.Q_11) {
                os << result_vec[i] << "0";
            } else {
                if (code_vec[idx][rule.i_2] == rule.Q_21 || code_vec[idx][rule.i_2] == rule.Q_22) {
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

bool BDATools::validate_rule(const BDA_Rule &rule) {
    if (rule.i_1 == rule.i_2) {
        throw std::invalid_argument("i1 must not be equal to i2");
    }

    if ((rule.i_1 >= this->tuple_size) || (rule.i_2 >= this->tuple_size) ||
        (rule.i_1 < 0) || (rule.i_2 < 0)) {
        std::ostringstream stringStream;
        stringStream << "i1 and i2 must not be between 1 and " << this->tuple_size + 1;
        throw std::invalid_argument(stringStream.str());
    }

    std::stringstream os;

    os << rule.Q_11 << rule.Q_12 << rule.Q_21 << rule.Q_22;
    if (!acid::is_acid_type(os.str(), this->code->get_acid())) {
        auto acid_name = acid::acid_to_string(this->code->get_acid());
        throw std::invalid_argument("The code is a " + acid_name + " code. The rule bases have to be " + acid_name);
    }

    return true;
}

std::vector<std::string> BDATools::get_all_rna_tuples(int length = 3) {
    std::vector<std::string> result(pow(4, length), "");
    for (int i = 1; i <= length; ++i) {
        int mode = int(pow(4, length - i));
        for (int i2 = 0; i2 < result.size(); ++i2) {
            char first = acid::rna[int(i2 / mode) % 4];
            result[i2] += std::string(1, first);
        }
    }

    return result;
}

std::vector<std::string> BDATools::get_all_rna_codons() {
    std::vector<std::string> result(64);
    int s = 0;
    for (char i : acid::rna) {
        for (char j : acid::rna) {
            for (char k : acid::rna) {
                std::string codon = std::string(1, i) + std::string(1, k) + std::string(1, j);
                result[s] = codon;
                s++;
            }
        }
    }

    return result;
}

std::vector<std::string> BDATools::get_tuples() {
    return this->code->get_tuples();
}
