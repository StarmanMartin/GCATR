//
// Created by Martin on 18.07.2018.
//

#ifndef GCATCPP_LONGESTPATHMINER_H
#define GCATCPP_LONGESTPATHMINER_H

#include "../graph/Graph.h"

class AbstractGenCode;

namespace miner {
    class LongestPathMiner {
    public:
        static std::vector<std::vector<std::string>> mine_path_as_vector(AbstractGenCode*);
        static std::vector<graph::Graph> mine_path_as_graph(AbstractGenCode*);
    };
}


#endif //GCATCPP_LONGESTPATHMINER_H
