//
// Created by Martin on 12.07.2018.
//
#include <iostream>

#include "Acid.h"

namespace acid {

    bool contains(const char array[], char letter);

    acids check_acid_type(std::string sequence) {
        bool is_dna = true;
        bool is_rna = true;
        for (char base : sequence) {
            if (!contains(dna, base)) {
                is_dna = false;
            }

            if (!contains(rna, base)) {
                is_rna = false;
            }
        }

        if (is_dna) {
            return DNA;
        }

        if (is_rna) {
            return RNA;
        }

        return NONE;
    }

    const std::string base_to_string(bases b) {
        return bases_name_list.find(b)->second;
    }

    const std::string acid_to_string(acids a) {
        return acid_name_list.find(a)->second;
    }

    bool contains(const char array[], char letter) {
        for (int i = 0; i < acid_base_length; ++i) {
            if (array[i] == letter) {
                return true;
            }
        }

        return false;
    }
}
