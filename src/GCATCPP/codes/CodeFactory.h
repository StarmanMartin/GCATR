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

    static std::shared_ptr<AbstractGenCode> rFactorGenCode(std::vector<std::string> &code, int tuple_length) {
        if(code.size() == 1) {
            if(tuple_length > 0) {
                std::string a = code.at(0);
                return CodeFactory::factorGenCode(a, (unsigned) tuple_length);
            } else {
                return CodeFactory::factorGenCode(code.at(0));
            }
        }

        return CodeFactory::factorGenCode(code);


    }

    static std::shared_ptr<AbstractGenCode> factorGenCode(std::string& code) {
        auto as_vector = utils::StringUtils::split(code, ' ');
        return CodeFactory::factorGenCode(as_vector);

    }

    static std::shared_ptr<AbstractGenCode> factorGenCode(std::string& seq, unsigned int tuple_length) {
        Code temp(seq, tuple_length);
        return CodeFactory::factorGenCode(temp.as_vector());
    }

    static std::shared_ptr<AbstractGenCode> factorGenCode(std::vector<std::string> code) {
        return std::make_shared<StdGenCode>(code);
    }

    static std::shared_ptr<AbstractCode> rFactor(std::vector<std::string> &code, int tuple_length) {
        if(code.size() == 1) {
            if(tuple_length > 0) {
                std::string a = code.at(0);
                return CodeFactory::factor(a, (unsigned) tuple_length);
            } else {
                return CodeFactory::factor(code.at(0));
            }
        }

        return CodeFactory::factor(code);

    }

    static std::shared_ptr<AbstractCode> factor(std::string& code) {
        auto as_vector = utils::StringUtils::split(code, ' ');
        return CodeFactory::factor(as_vector);

    }

    static std::shared_ptr<AbstractCode> factor(std::string& seq, unsigned int tuple_length) {
        Code temp(seq, tuple_length);
        return CodeFactory::factor(temp.as_vector());
    }

    static std::shared_ptr<AbstractCode> factor(std::vector<std::string> code) {
        return std::make_shared<Code>(code);
    }
};

#endif //GCATCPP_CODEFACTORY_H
