//
// Created by martins on 18.06.19.
//

#ifndef GCATCPP_TESSERACODE_H
#define GCATCPP_TESSERACODE_H

#include "AbstractGenCode.h"

class TesseraCode : public AbstractGenCode{

public:
    explicit TesseraCode(const std::vector<std::string>& code_vec) : AbstractGenCode(code_vec){}

    TesseraCode(std::string sequence, unsigned int word_length) : AbstractGenCode(std::move(sequence), word_length){}

    TesseraCode(const TesseraCode &agc) = default;

    bool test_code() override;

    bool is_self_complementary() override;

    void setTranslTableByIdx(int idx);
    void setTranslTableByName(const std::string &name);
    void setTranslTableToStandardCode();

protected:

};


#endif //GCATCPP_TESSERACODE_H
