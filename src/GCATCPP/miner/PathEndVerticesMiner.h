//
// Created by martins on 16.07.20.
//

#ifndef GCATCPP_PATHENDVERTICESMINER_H
#define GCATCPP_PATHENDVERTICESMINER_H


#include <vector>
#include <string>

class AbstractCode;

namespace miner {
    class PathEndVerticesMiner {
    public:
        static std::vector<std::string> mine_vertices_as_vector(AbstractCode *);
    };
}

#endif //GCATCPP_PATHENDVERTICESMINER_H
