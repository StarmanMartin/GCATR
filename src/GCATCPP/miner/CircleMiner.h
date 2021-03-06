//
// Created by Martin on 17.07.2018.
//

#ifndef GCATCPP_CIRCLEMINER_H
#define GCATCPP_CIRCLEMINER_H

#include <vector>
#include <string>

#include "../graph/Graph.h"

class AbstractCode;

namespace miner {
    class CircleMiner {
    public:
        static std::vector<std::vector<std::string>> mine_path_as_vector(AbstractCode *);

        static graph::Graph mine_path_as_graph(AbstractCode *);

    private:
        static std::vector<graph::Graph> mine_all_path_as_graph(AbstractCode *);
    };
}


#endif //GCATCPP_CIRCLEMINER_H
