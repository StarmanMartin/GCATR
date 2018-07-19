//
// Created by Martin on 12.07.2018.
//
#include <iostream>
#include <sstream>

#include "Acid.h"

namespace acid {

    bool contains(const char array[], char letter);

    acids check_acid_type(std::string sequence, bool dna_allowed, bool rna_allowed) {
        bool is_dna = dna_allowed;
        bool is_rna = rna_allowed;
        for (char base : sequence) {
            if (is_dna && !contains(dna, base)) {
                is_dna = false;
            }

            if (is_rna && !contains(rna, base)) {
                is_rna = false;
            }

            if(!is_dna && !is_rna) {
                return NONE;
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

    int get_base_value(bases in_base) {
        auto find_res =  bases_value_list.find(in_base);
        if(find_res != bases_value_list.end()) {
            return find_res->second;
        }

        return -1;
    }

    bool is_acide_type(std::string seq, acids acid_type) {
        return check_acid_type(seq, acid_type==DNA, acid_type==RNA)!=NONE;
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

    std::string get_anti_codon(std::string codon, acids acid) {
        if(acid == NONE || !is_acide_type(codon, acid)) {
            return "";
        }

        std::stringstream anti_codon;
        for(signed int i = (signed int)codon.length() - 1; i >= 0; --i) {
            anti_codon << (char) get_compliment((bases)codon[i], acid);
        }

        return anti_codon.str();
    }

    bases get_compliment(bases in_base, acids acid) {
        auto find_res =  compliments_dna.find(in_base);
        if(acid != RNA && find_res != compliments_rna.end()) {
            return find_res->second;
        }

        return compliments_rna.find(in_base)->second;
    }
}
