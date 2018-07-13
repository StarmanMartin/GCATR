//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_ABSTRACTTESTER_H
#define GCATCPP_ABSTRACTTESTER_H

#include <memory>

#include "../codes/AbstractGenCode.h"

class AbstractTester {
private:
    std::string error_msg;
public:

    explicit AbstractTester() {};

    virtual bool test(AbstractGenCode *code) = 0;

    std::string get_error_msg() const;
};


#endif //GCATCPP_ABSTRACTTESTER_H
