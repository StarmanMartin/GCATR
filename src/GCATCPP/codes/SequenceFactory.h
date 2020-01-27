//
// Created by Martin on 2/12/2019.
//

#ifndef GCATCPP_SEQUENCEFACTORY_H
#define GCATCPP_SEQUENCEFACTORY_H

#include <memory>

#include "../sequences/Sequence.h"
#include "../helper/StringUtils.h"

#define CODE_TPYE_TESSERA 0b100u
#define CODE_TPYE_CODON 0b010u
#define CODE_TPYE_GEN 0b111u

class SequenceFactory {
public:

    static std::shared_ptr<Sequence> rFactor(std::vector<std::string> &code, int tuple_length) {
        if (code.size() == 1) {
            if (tuple_length > 0) {
                std::string a = code.at(0);
                return SequenceFactory::factor(a, (unsigned) tuple_length);
            } else {
                return SequenceFactory::factor(code.at(0));
            }
        }

        return SequenceFactory::factor(code);

    }

    static std::shared_ptr<Sequence> factor(std::string &code) {
        auto as_vector = utils::StringUtils::split(code, ' ');
        return SequenceFactory::factor(as_vector);

    }

    static std::shared_ptr<Sequence> factor(std::string &seq, unsigned int tuple_length) {
        return std::make_shared<Sequence>(seq, tuple_length);
    }

    static std::shared_ptr<Sequence> factor(std::vector<std::string> code) {
        if(code.empty()) {
            return std::make_shared<Sequence>("", 0);
        }

        size_t tuple_length = code[0].length();
        std::string s;
        for (const auto &piece : code) s += piece;

        return std::make_shared<Sequence>(s, tuple_length);
    }
};

#endif //GCATCPP_SEQUENCEFACTORY_H
