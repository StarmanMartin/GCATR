//
// Created by Martin on 10.07.2018.
//

#ifndef GCATCPP_ABSTRACTGENCODE_H
#define GCATCPP_ABSTRACTGENCODE_H

#include "Acid.h"
#include "Code.h"
#include "../interfaces/AbstractTranslatable.h"


class AbstractGenCode : public Code, public AbstractTranslatable {
public:
    explicit AbstractGenCode(const std::vector<std::string> &);
    explicit AbstractGenCode(std::string, unsigned int);
    
    AbstractGenCode(const AbstractGenCode &agc);

    bool test_code() override;
    
    virtual bool is_self_complementary();

    acid::acids get_acid() override;



    void transform_tuples_by_name(const std::string& rule_name); // NOLINT


    void setTranslTableByIdx(int idx, int forWordLength) override ;
    void setTranslTableByName(const std::string &name, int forWordLength) override;
    void setTranslTableToStandardCode(int forWordLength) override;


    void setTranslTableByIdx(int idx) ;
    void setTranslTableByName(const std::string &name);
    void setTranslTableToStandardCode();

    std::vector<std::string> get_amino_acids() override;
    std::vector<std::string> get_a_set_amino_acids() override;

    std::vector<std::string> construct_transl_table(int wordLength, acid::acids acid_type) const override;


protected:

    acid::acids acid;

    void reset(std::vector<std::string>) override;

};

#endif //GCATCPP_ABSTRACTGENCODE_H
