//
// Created by Martin on 2/14/2019.
//

#ifndef GCATCPP_KCIRCULAR_H
#define GCATCPP_KCIRCULAR_H

#include "AbstractTester.h"

class KCircular : public AbstractTester {
public:
    bool test(AbstractCode *code, int k) override;
    bool test(AbstractCode *code) override;

};


#endif //GCATCPP_KCIRCULAR_H
