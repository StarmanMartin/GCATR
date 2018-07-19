//
// Created by Martin on 13.07.2018.
//

#ifndef GCATCPP_ABSTRACTMODIFIER_H
#define GCATCPP_ABSTRACTMODIFIER_H

#include <iostream>
#include <vector>

#include "../helper/AbstractErrorManager.h"

class AbstractGenCode;

class AbstractModifier : public err::AbstractErrorManager {
public:

    explicit AbstractModifier() {};

    virtual std::vector<std::string> modify(AbstractGenCode *code, void *args) = 0;
};


#endif //GCATCPP_ABSTRACTMODIFIER_H
