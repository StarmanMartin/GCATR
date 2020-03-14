//
// Created by martins on 14.03.20.
//

#ifndef GCATCPP_KCIRCULARITYMINER_H
#define GCATCPP_KCIRCULARITYMINER_H

#include <vector>
#include <string>

class AbstractCode;

namespace miner {
    class kCircularityMiner {
    public:
        static int mine_k_value(AbstractCode *);
    };
}


#endif //GCATCPP_KCIRCULARITYMINER_H
