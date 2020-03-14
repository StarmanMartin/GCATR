//
// Created by martins on 14.03.20.
//

#include "kCircularityMiner.h"

#include "../codes/AbstractCode.h"
#include "../tester/Circular.h"

using namespace miner;

int kCircularityMiner::mine_k_value(AbstractCode *code) {
    Circular cTester;

    auto circles = cTester.get_circles(code);

    if(circles.empty()) {
        return -1;
    }

    size_t minK = -1;

    for (const auto &circle_graph : circles) {
        size_t csize = circle_graph.get_edges().size();
        if (csize % 2 == 1 && csize < minK) {
            minK = csize;
        } else if (csize % 2 == 0 && csize / 2 < minK) {
            minK = csize / 2;
        }
    }

    return int(minK);
}
