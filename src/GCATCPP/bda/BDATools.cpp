//
// Created by Martin on 13.07.2018.
//

#include "BDATools.h"
#include "../codes/Acid.h"
#include "../codes/StdGenCode.h"
#include <memory>
#include <sstream>

using namespace BDA;

BDATools::BDATools(std::shared_ptr<AbstractGenCode> code): code(code) {
    this->rules = {};
}

bool BDATools::add_rule(unsigned int i_1,unsigned int i_2, char Q_11, char Q_12, char Q_21, char Q_22){
    BDA_Rule rule(i_1, i_2, Q_11,  Q_12, Q_21, Q_22);
    return this->add_rule(rule);
}

bool BDATools::add_rule(BDA_Rule rule){
    if(this->validate_rule(rule)) {
        this->rules.push_back(rule);
        return true;
    }

    return false;
}

std::vector<std::string> BDATools::run_bda_for_code(){
    auto code_vec = this->code->as_vector();
    std::vector<std::string> result_vec(code_vec.size());


    for(BDA_Rule rule : this->rules) {
        for (int i = 0; i < code_vec.size(); ++i) {
            std::stringstream os;
            char i_1_letter = code_vec[i][rule.i_1];
            if(code_vec[i][rule.i_1] == rule.Q_12) {
                os << result_vec[i] << "1";
            } else if(code_vec[i][rule.i_1] == rule.Q_11) {
                os << result_vec[i] << "0";
            } else {
                if(code_vec[i][rule.i_2] == rule.Q_21 || code_vec[i][rule.i_2] == rule.Q_22) {
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


bool BDATools::validate_rule(BDA_Rule rule) {
    if(rule.i_1 == rule.i_2) {
        return false;
    }

    if((rule.i_1 >= BDA_WORD_LENGTH) || (rule.i_2 >= BDA_WORD_LENGTH)) {
        return false;
    }

    std::stringstream os;

    os << rule.Q_11 << rule.Q_12 << rule.Q_21 << rule.Q_22;
auto debug_1 = acid::acid_to_string(this->code->get_acid());
    if(!acid::is_acide_type(os.str(), this->code->get_acid())) {
        return false;
    }

    return true;
}