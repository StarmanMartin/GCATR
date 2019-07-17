//
// Created by Martin on 13.07.2018.
//

#ifndef GCATCPP_SHIFTTUPLES_H
#define GCATCPP_SHIFTTUPLES_H

#include "AbstractModifier.h"

class ShiftTuples : public AbstractModifier {
public:
    explicit ShiftTuples(size_t number): number(number), AbstractModifier() {}

    std::vector<std::string> modify(AbstractCode* code) override;
    std::string modify_word(std::string word) override;
    std::string shift_tuple(std::string word, size_t number);
private:
    size_t number;
};


#endif //GCATCPP_SHIFTTUPLES_H
