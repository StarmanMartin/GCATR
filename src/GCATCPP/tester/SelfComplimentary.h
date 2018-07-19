//
// Created by Martin on 17.07.2018.
//

#ifndef GCATCPP_SELFCOMPLIMENTARY_H
#define GCATCPP_SELFCOMPLIMENTARY_H

#include "AbstractTester.h"

class SelfComplimentary : public AbstractTester {
public:
    virtual bool test(AbstractGenCode *code);
};

#endif //GCATCPP_SELFCOMPLIMENTARY_H
