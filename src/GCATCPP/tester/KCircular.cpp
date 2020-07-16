//
// Created by Martin on 2/14/2019.
//

#include "KCircular.h"

#include "../miner/kCircularityMiner.h"
#include <stdexcept>


bool KCircular::test(AbstractCode *code, int k) {
    if(k < 0) {
        throw  std::invalid_argument("K-Circular codes for a negative k are not defined");
    }
    int kVal = miner::kCircularityMiner::mine_k_value(code);
    if(kVal <= -1) {
        return true;
    }
    return kVal >= k;
}

bool KCircular::test(AbstractCode *code) {
    return this->test(code, 1);
}