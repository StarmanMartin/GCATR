//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_ACID_H
#define GCATCPP_ACID_H

#include <vector>
#include <map>

namespace acid {

    enum bases {URACIL = 'U', THYMINE = 'T',CYTOSINE = 'C',ADENINE = 'A',GUANINE = 'G'};
    enum acids {DNA=0, RNA=1, NONE=2};

    const int acid_base_length = 4;

    const char  dna[acid_base_length] = {THYMINE, ADENINE, CYTOSINE, GUANINE};
    const char  rna [acid_base_length] = {URACIL, ADENINE, CYTOSINE, GUANINE};

    const std::map<bases,const std::string> bases_name_list {
            { URACIL, "URACIL" },
            { THYMINE, "THYMINE" },
            { CYTOSINE, "CYTOSINE" },
            { ADENINE, "ADENINE" },
            { GUANINE, "GUANINE" }
    };

    const std::map<acids,const std::string> acid_name_list {
            { DNA, "DNA" },
            { RNA, "RNA" },
            { NONE, "NONE" }
    };

    acids check_acid_type(std::string);
    const std::string base_to_string(bases);
    const std::string acid_to_string(acids);

}

#endif