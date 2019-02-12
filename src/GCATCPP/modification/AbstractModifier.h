//
// Created by Martin on 13.07.2018.
//

#ifndef GCATCPP_ABSTRACTMODIFIER_H
#define GCATCPP_ABSTRACTMODIFIER_H

#include <iostream>
#include <vector>

#include "../helper/AbstractErrorManager.h"

class AbstractCode;

class AbstractModifier : public err::AbstractErrorManager {
public:

    explicit AbstractModifier() = default;;

    virtual std::vector<std::string> modify(AbstractCode *code, void *args) = 0;
    virtual std::string modify_word(std::string word, void *args) = 0;
};


#endif //GCATCPP_ABSTRACTMODIFIER_H
