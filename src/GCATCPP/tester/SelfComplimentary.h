//
// Created by Martin on 17.07.2018.
//

#ifndef GCATCPP_SELFCOMPLIMENTARY_H
#define GCATCPP_SELFCOMPLIMENTARY_H

#include "AbstractTester.h"

class AbstractGenCode;

class SelfComplimentary : public AbstractTester {
public:
    virtual bool test(AbstractCode *code) override;
    virtual bool self_complimentary_test(AbstractGenCode *code);
};

#endif //GCATCPP_SELFCOMPLIMENTARY_H
