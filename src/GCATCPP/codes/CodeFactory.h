//
// Created by Martin on 2/12/2019.
//

#ifndef GCATCPP_CODEFACTORY_H
#define GCATCPP_CODEFACTORY_H

#include <memory>

#include "AbstractCode.h"
#include "StdGenCode.h"
#include "TesseraCode.h"
#include "../helper/StringUtils.h"
#include "GenCode.h"

#define CODE_TPYE_TESSERA 0b100u
#define CODE_TPYE_CODON 0b010u
#define CODE_TPYE_GEN 0b111u

class CodeFactory {
public:


    static std::shared_ptr<AbstractGenCode>
    rFactorGenCode(const std::vector<std::string> &code, int tuple_length) {
        if(tuple_length <= 0) {
            throw std::invalid_argument("Tuple length has to be at least 1");
        }

        return CodeFactory::rFactorTypesGenCode(code, tuple_length, CODE_TPYE_GEN);
    }
    static std::shared_ptr<AbstractGenCode>
    rFactorGenCode(const std::vector<std::string> &code) {
        return CodeFactory::rFactorTypesGenCode(code, -1, CODE_TPYE_GEN);
    }

    static std::shared_ptr<AbstractGenCode> rFactorTypesCodonCode(const std::vector<std::string> &code) {
        return CodeFactory::rFactorTypesGenCode(code, 3, CODE_TPYE_CODON);
    }

    static std::shared_ptr<AbstractGenCode> rFactorTypesTesseraCode(const std::vector<std::string> &code) {
        return rFactorTypesGenCode(code, 4, CODE_TPYE_TESSERA);
    }

    static std::shared_ptr<AbstractGenCode> rFactorTypesTesseraCodeFromCodons(const std::vector<std::string> &code) {
        auto codons = rFactorTypesCodonCode(code);
        return TesseraCode::tesseraCodeFromCodons(codons);
    }

    static std::shared_ptr<AbstractCode> rFactor(std::vector<std::string> &code) {
        if (code.size() == 1) {
            return CodeFactory::factor(code.at(0));
        }

        return CodeFactory::factor(code);
    }

    static std::shared_ptr<AbstractCode> rFactor(std::vector<std::string> &code, int tuple_length) {
        if(tuple_length <= 0) {
            throw std::invalid_argument("Tuple length has to be at least 1");
        }

        std::string a = code.at(0);
        return CodeFactory::factor(a, (unsigned) tuple_length);
    }

    static std::shared_ptr<AbstractCode> factor(std::string &code) {
        auto as_vector = utils::StringUtils::split(code, ' ');
        return CodeFactory::factor(as_vector);

    }

    static std::shared_ptr<AbstractCode> factor(std::string &seq, unsigned int tuple_length) {
        if(tuple_length <= 0) {
            throw std::invalid_argument("Tuple length has to be at least 1");
        }

        Code temp(seq, tuple_length);
        return CodeFactory::factor(temp.as_unsorted_vector());
    }

    static std::shared_ptr<AbstractCode> factor(std::vector<std::string> code) {
        return std::make_shared<Code>(code);
    }

private:
    static std::shared_ptr<AbstractGenCode>
    rFactorTypesGenCode(std::vector<std::string> code, int tuple_length, size_t code_type = CODE_TPYE_GEN) {
        if (code.size() == 1) {
            code = CodeFactory::factorGenCode(code.at(0));
        }
        if (code.size() == 1 && tuple_length > 0) {
            code = CodeFactory::factorGenCode(code.at(0), (unsigned) tuple_length);
        }

        return CodeFactory::factorGenCode(code, code_type);
    }

    static std::vector<std::string> factorGenCode(std::string &code) {
        return utils::StringUtils::split(code, ' ');

    }

    static std::vector<std::string> factorGenCode(std::string &seq, unsigned int tuple_length) {
        Code temp(seq, tuple_length);
        return temp.as_unsorted_vector();
    }

    static std::shared_ptr<AbstractGenCode> factorGenCode(std::vector<std::string> code, size_t code_type) {
        if (code_type & CODE_TPYE_TESSERA) {
            auto tessera_code = std::make_shared<TesseraCode>(code);
            if (tessera_code->test_code()) {
                return tessera_code;
            } else if (0 == (code_type & CODE_TPYE_GEN)) {
                return tessera_code;
            }
        } else if (code_type & CODE_TPYE_CODON) {
            auto std_code = std::make_shared<StdGenCode>(code);
            if (std_code->test_code()) {
                return std_code;
            } else if (0 == (code_type & CODE_TPYE_GEN)) {
                return std_code;
            }
        }

        return std::make_shared<GenCode>(code);
    }
};

#endif //GCATCPP_CODEFACTORY_H
