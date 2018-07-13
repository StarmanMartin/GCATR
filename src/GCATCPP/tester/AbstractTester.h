//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_ABSTRACTTESTER_H
#define GCATCPP_ABSTRACTTESTER_H

#include "../codes/AbstractGenCode.h"

class AbstractTester {
private:
    std::string error_msg;
public:

    explicit AbstractTester(){};

    virtual bool test(std::shared_ptr<AbstractGenCode> code) = 0;
    virtual std::string get_error_msg() const;
};


#endif //GCATCPP_ABSTRACTTESTER_H
