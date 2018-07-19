//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_ABSTRACTTESTER_H
#define GCATCPP_ABSTRACTTESTER_H

#include <memory>

#include "../codes/AbstractGenCode.h"
#include "../helper/AbstractErrorManager.h"

class AbstractTester : public err::AbstractErrorManager {
public:

    explicit AbstractTester() {};

    virtual bool test(AbstractGenCode *code) = 0;
};


#endif //GCATCPP_ABSTRACTTESTER_H
