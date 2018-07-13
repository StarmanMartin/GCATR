//
// Created by Martin on 13.07.2018.
//

#ifndef GCATCPP_ABSTRACTMODIFIER_H
#define GCATCPP_ABSTRACTMODIFIER_H

#include <iostream>
#include <vector>

class AbstractGenCode;

class AbstractModifier {
protected:
    std::string error_msg;
public:

    explicit AbstractModifier() {};

    virtual std::vector<std::string> modify(AbstractGenCode *code, void* args) = 0;

    std::string get_error_msg() const;
};


#endif //GCATCPP_ABSTRACTMODIFIER_H
