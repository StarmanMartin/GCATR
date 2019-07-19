//
// Created by martins on 18.06.19.
//

#ifndef GCATCPP_TESSERACODE_H
#define GCATCPP_TESSERACODE_H

#define TESSERA_TRANSFORMATIONS 4

#include "AbstractGenCode.h"
#include "../modification/TransformTuples.h"

class TesseraCode : public AbstractGenCode{

public:
    explicit TesseraCode(const std::vector<std::string>& code_vec) : AbstractGenCode(code_vec){}

    TesseraCode(std::string sequence, unsigned int word_length) : AbstractGenCode(std::move(sequence), word_length){}

    TesseraCode(const TesseraCode &agc) = default;

    bool test_code() override;

protected:
    std::string tessera_transformation_names[TESSERA_TRANSFORMATIONS] = {SW, YR, I, KM};

};


#endif //GCATCPP_TESSERACODE_H
