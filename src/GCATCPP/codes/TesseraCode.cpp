//
// Created by martins on 18.06.19.
//

#include <sstream>
#include "TesseraCode.h"

bool TesseraCode::test_code() {
    if (this->is_tested || !AbstractGenCode::test_code()) {
        return this->is_ok;
    }

    if (this->word_length.size() != 1 || this->word_length[0] != 4) {
        return (this->is_ok = false);
    }

    for (const std::string &w : this->code_vec) {
        auto t = TransformTuples::find_transformation_from_sequences(w.substr(0, 2), w.substr(2, 2));
        bool has_match = false;
        for (const auto &name : this->tessera_transformation_names) {
            auto temp_trans = TransformTuples(name, this->acid);
            if (t <= temp_trans) {
                has_match = true;
                break;
            }
        }

        if (!has_match) {
            this->add_error_msg("The word " + w + " is not a correct Tessera.");
            return (this->is_ok = false);
        }

    }

    return (this->is_ok = true);
}

std::shared_ptr<TesseraCode> TesseraCode::tesseraCodeFromCodons(const std::shared_ptr<AbstractGenCode>& codons) {
    if (codons->test_code() && codons->get_word_length()[0] != 3) {
        throw std::invalid_argument("Codons are not correct.");
    }

    std::map<std::string, std::string> mapping;
    mapping["A"] = I;
    mapping["U"] = SW;
    mapping["T"] = SW;
    mapping["C"] = KM;
    mapping["G"] = YR;

    std::vector<std::string> words;

    for (const auto &c: codons->as_unsorted_vector()) {
        TransformTuples pi1(mapping[c.substr(0, 1)], codons->get_acid());
        TransformTuples pi2(mapping[c.substr(1, 1)], codons->get_acid());
        std::stringstream ss;
        std::string N4 = c.substr(2, 1);
        std::string N3 = pi1.modify_word(N4);
        std::string N2 = pi2.modify_word(N3);
        std::string N1 = pi1.modify_word(N2);

        ss << N1 << N2 << N3 << N4;

        words.push_back(ss.str());
    }
    return std::make_shared<TesseraCode>(words);
}

std::shared_ptr<AbstractGenCode> TesseraCode::codonsCodesFromTessera(const std::shared_ptr<TesseraCode>& tessCode) {
    if (tessCode->test_code() && tessCode->get_word_length()[0] != 4) {
        throw std::invalid_argument("Tesserae are not correct.");
    }

    std::map<std::string, std::string> mapping;
    mapping[I] = "A";
    mapping[SW] = "U";
    mapping[SW] = "T";
    mapping[KM] = "C";
    mapping[YR] = "G";

    std::vector<std::string> words;

    for (const auto &c: tessCode->as_unsorted_vector()) {
        auto t1 = TransformTuples::find_transformation_from_sequences(c.substr(0, 1), c.substr(1, 1));
        auto t1Name = t1.getKleinFourTransformationName(tessCode->get_acid());


        auto t2 = TransformTuples::find_transformation_from_sequences(c.substr(1, 1), c.substr(2, 1));
        auto t2Name = t2.getKleinFourTransformationName(tessCode->get_acid());

        std::stringstream ss;

        ss << mapping[t1Name] <<  mapping[t2Name] << c.substr(3, 1);

        words.push_back(ss.str());
    }
    return std::make_shared<AbstractGenCode>(words);
}
