//
// Created by martins on 17.10.19.
//

#ifndef GCATCPP_ABSTRACTTUPLECONTAINER_H
#define GCATCPP_ABSTRACTTUPLECONTAINER_H


#include <vector>
#include <string>
#include "../codes/Acid.h"

class AbstractTupleContainer {
public:
    virtual std::vector<std::string> get_tuples() = 0;
    virtual std::vector<std::string> get_nucleotide_tuples() = 0;
    virtual std::vector<int> get_word_length() = 0;

    virtual acid::acids get_acid();
};


#endif //GCATCPP_ABSTRACTTUPLECONTAINER_H
