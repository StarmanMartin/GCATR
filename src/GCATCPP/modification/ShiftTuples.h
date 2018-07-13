//
// Created by Martin on 13.07.2018.
//

#ifndef GCATCPP_SHIFTTUPLES_H
#define GCATCPP_SHIFTTUPLES_H

#include "AbstractModifier.h"

class ShiftTuples : public AbstractModifier {
public:
    std::vector<std::string> modify(AbstractGenCode* code, void* args);
};


#endif //GCATCPP_SHIFTTUPLES_H
