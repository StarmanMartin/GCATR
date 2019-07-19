//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <numeric>
#include <iostream>
#include <regex>
#include <utility>
#include <algorithm>
#include <sstream>
#include "GenCode.h"
#include "../tester/Circular.h"
#include "../tester/C_n.h"
#include "../tester/CommaFree.h"

#include "../modification/ShiftTuples.h"

#include "../graph/Graph.h"



bool GenCode::test_code() {
    if (this->is_tested || !AbstractGenCode::test_code()) {
        return this->is_ok;
    }

    return (this->is_ok = true);
}