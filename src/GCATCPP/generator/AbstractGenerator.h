//
// Created by Martin on 10.10.2018.
//

#ifndef GCATCPP_ABSTRACTGENERATOR_H
#define GCATCPP_ABSTRACTGENERATOR_H


#include <string>
#include <vector>

#include "../helper/AbstractErrorManager.h"

class AbstractGenerator : public err::AbstractErrorManager {
public:
    explicit AbstractGenerator() : AbstractErrorManager() {};
    virtual std::vector<std::string> run() = 0;
};


#endif //GCATCPP_ABSTRACTGENERATOR_H
