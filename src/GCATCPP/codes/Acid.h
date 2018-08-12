//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_ACID_H
#define GCATCPP_ACID_H

#include <vector>
#include <map>

namespace acid {

    typedef enum bases {
        URACIL = 'U', THYMINE = 'T', CYTOSINE = 'C', ADENINE = 'A', GUANINE = 'G'
    } bases;

    typedef enum acids {
        DNA = 0, RNA = 1, NONE = 2
    } acids;

    const int acid_base_length = 4;

    const char dna[acid_base_length] = {THYMINE, CYTOSINE, ADENINE, GUANINE};
    const char rna[acid_base_length] = {URACIL, CYTOSINE, ADENINE, GUANINE};


    const std::map<bases, const std::string> bases_name_list{
            {URACIL,   "URACIL"},
            {THYMINE,  "THYMINE"},
            {CYTOSINE, "CYTOSINE"},
            {ADENINE,  "ADENINE"},
            {GUANINE,  "GUANINE"}
    };

    const std::map<bases, int> bases_value_list{
            {URACIL,   0},
            {THYMINE,  0},
            {CYTOSINE, 1},
            {ADENINE,  2},
            {GUANINE,  3}
    };

    const std::map<acids, const std::string> acid_name_list{
            {DNA,  "DNA"},
            {RNA,  "RNA"},
            {NONE, "NONE"}
    };

    const std::map<bases, bases> compliments_dna {
            {THYMINE,  ADENINE},
            {CYTOSINE, GUANINE},
            {ADENINE, THYMINE},
            {GUANINE, CYTOSINE}
    };

    const std::map<bases, bases> compliments_rna {
            {URACIL,  ADENINE},
            {CYTOSINE, GUANINE},
            {ADENINE, URACIL},
            {GUANINE, CYTOSINE}
    };

    acids check_acid_type(std::string, bool= true, bool= true);

    bool is_acide_type(std::string, acids);

    int get_base_value(bases);

    const std::string base_to_string(bases);

    const std::string acid_to_string(acids);

    std::string get_anti_codon(std::string, acids);
    bases get_compliment(bases, acids);


}

#endif