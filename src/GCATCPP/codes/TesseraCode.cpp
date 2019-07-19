//
// Created by martins on 18.06.19.
//

#include "TesseraCode.h"

bool TesseraCode::test_code() {
    if (this->is_tested || !AbstractGenCode::test_code()) {
        return this->is_ok;
    }

    if(this->word_length.size() != 1 || this->word_length[0] != 4) {
        return (this->is_ok = false);
    }

    for(const std::string &w : this->code_vec){
        auto t = TransformTuples::find_transformation_from_sequences(w.substr(0,2), w.substr(2,2));
        bool has_match = false;
        for(const auto & name : this->tessera_transformation_names) {
            auto temp_trans = TransformTuples(name, this->acid);
            if(t <= temp_trans) {
                has_match = true;
                break;
            }
        }

        if(!has_match) {
            this->add_error_msg("The word " + w + " is not a correct Tessera.");
            return (this->is_ok = false);
        }

    }

    return (this->is_ok = true);
}