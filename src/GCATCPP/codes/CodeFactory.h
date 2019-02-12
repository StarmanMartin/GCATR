//
// Created by Martin on 2/12/2019.
//

#ifndef GCATCPP_CODEFACTORY_H
#define GCATCPP_CODEFACTORY_H

#include <memory>

#include "AbstractCode.h"
#include "StdGenCode.h"
#include "../helper/StringUtils.h"

class CodeFactory {
public:
    static std::shared_ptr<AbstractCode> factor(std::string& code) {
        auto as_vector = utils::StringUtils::split(code, ' ');
        return CodeFactory::factor(as_vector);

    }

    static std::shared_ptr<AbstractCode> factor(std::string& seq, unsigned int& tuple_length) {
        Code temp(seq, tuple_length);
        return CodeFactory::factor(temp.as_vector());
    }

    static std::shared_ptr<AbstractCode> factor(std::vector<std::string> code) {
        std::shared_ptr<AbstractCode> code_obj;

        for(short code_idx = 0; code_idx < 2; ++code_idx) {

            switch (code_idx) {
                case 0:
                    code_obj = std::make_shared<StdGenCode>(code);
                    if(code_obj->test_code()) {
                        return code_obj;
                    }
                    break;
                case 1:
                    code_obj = std::make_shared<Code>(code);
                    if(code_obj->test_code()) {
                        return code_obj;
                    }
                    break;
                default:
                    return nullptr;
            }
        }

        return nullptr;
    }
};

#endif //GCATCPP_CODEFACTORY_H
