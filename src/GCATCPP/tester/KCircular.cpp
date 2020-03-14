//
// Created by Martin on 2/14/2019.
//

#include "KCircular.h"

#include "../miner/kCircularityMiner.h"


bool KCircular::test(AbstractCode *code, int k) {
    return miner::kCircularityMiner::mine_k_value(code) == k;
}

bool KCircular::test(AbstractCode *code) {
    return this->test(code, 1);
}