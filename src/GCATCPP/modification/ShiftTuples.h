//
// Created by Martin on 13.07.2018.
//

#ifndef GCATCPP_SHIFTTUPLES_H
#define GCATCPP_SHIFTTUPLES_H

#include "AbstractModifier.h"

class ShiftTuples : public AbstractModifier {
public:
    std::vector<std::string> modify(AbstractGenCode* code, void* args) override;
    std::string modify_word(std::string word, void *args) override;
};


#endif //GCATCPP_SHIFTTUPLES_H
