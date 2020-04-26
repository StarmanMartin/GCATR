//
// Created by Martin on 27.06.2018.
//
#include "GenCode.h"
#include "../tester/Circular.h"

#include "../modification/ShiftTuples.h"


bool GenCode::test_code() {
    if (this->is_tested || !AbstractGenCode::test_code()) {
        return this->is_ok;
    }

    return (this->is_ok = true);
}