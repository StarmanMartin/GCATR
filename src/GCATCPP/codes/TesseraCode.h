//
// Created by martins on 18.06.19.
//

#ifndef GCATCPP_TESSERACODE_H
#define GCATCPP_TESSERACODE_H

#define TESSERA_TRANSFORMATIONS 4

#include <utility>

#include "AbstractGenCode.h"
#include "../modification/TransformTuples.h"

class TesseraCode : public AbstractGenCode{

public:
    explicit TesseraCode(const std::vector<std::string>& code_vec) : AbstractGenCode(code_vec){}

    explicit TesseraCode(std::string sequence) : TesseraCode(std::move(sequence), 4){}

    TesseraCode(const TesseraCode &agc) = default;

    bool test_code() override;

    static std::shared_ptr<TesseraCode> tesseraCodeFromCodons(std::shared_ptr<AbstractGenCode> code);

protected:
    std::string tessera_transformation_names[TESSERA_TRANSFORMATIONS] = {SW, YR, I, KM};

    TesseraCode(std::string sequence, unsigned int word_length) : AbstractGenCode(std::move(sequence), word_length){}

};


#endif //GCATCPP_TESSERACODE_H
