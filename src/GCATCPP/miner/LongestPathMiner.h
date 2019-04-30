//
// Created by Martin on 18.07.2018.
//

#ifndef GCATCPP_LONGESTPATHMINER_H
#define GCATCPP_LONGESTPATHMINER_H

#include "../graph/Graph.h"

class AbstractCode;

namespace miner {
    class LongestPathMiner {
    public:
        static std::vector<std::vector<std::string>> mine_path_as_vector(AbstractCode *);

        static graph::Graph mine_path_as_graph(AbstractCode *);

    private:
        static std::vector<graph::Graph> mine_all_path_as_graph(AbstractCode *);
    };
}


#endif //GCATCPP_LONGESTPATHMINER_H
