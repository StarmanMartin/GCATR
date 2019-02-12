//
// Created by Martin on 17.07.2018.
//

#include "SelfComplimentary.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

#include "../codes/Acid.h"
#include "../codes/AbstractGenCode.h"

bool SelfComplimentary::test(AbstractCode *code) {
    AbstractGenCode *gen_code = dynamic_cast<AbstractGenCode *>(code);
    if (gen_code != nullptr) {
        return this->self_complimentary_test(gen_code);
    }

    return false;
}

bool SelfComplimentary::self_complimentary_test(AbstractGenCode *code) {
    std::vector<std::string> vec = code->as_vector();
    bool is_self_complimentary = true;
    std::stringstream not_fitting;

    not_fitting << "Codons without Anti-codon:";
    for (auto i = 0; i < vec.size(); i++) {
        if (vec[i] != "#") {
            auto it = std::find(vec.begin(), vec.end(), acid::get_anti_codon(vec[i], code->get_acid()));
            if (it != vec.end()) {
                vec[i] = "#";
                auto index = std::distance(vec.begin(), it);
                vec[index] = "#";
            } else {
                is_self_complimentary = false;
                not_fitting << " " << vec[i];
            }
        }
    }

    if (!is_self_complimentary) {
        this->add_error_msg(not_fitting.str());
    }

    return is_self_complimentary;
};
