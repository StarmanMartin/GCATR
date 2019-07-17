//
// Created by Martin on 10.07.2018.
//

#ifndef GCATCPP_ABSTRACTGENCODE_H
#define GCATCPP_ABSTRACTGENCODE_H

#include "Acid.h"
#include "Code.h"





class AbstractGenCode : public Code {
public:
    explicit AbstractGenCode(const std::vector<std::string> &);
    explicit AbstractGenCode(std::string, unsigned int);
    
    AbstractGenCode(const AbstractGenCode &agc);

    bool test_code() override;

    virtual bool is_self_complementary() = 0;

    acid::acids get_acid();

    void setTranslTableByIdx(int idx, int forWordLength=-1);
    void setTranslTableByName(const std::string &name, int forWordLength=-1);
    void setTranslTableToStandardCode(int forWordLength=-1);

    void transform_tuples_by_name(const std::string& rule_name); // NOLINT



    std::vector<std::string> get_amino_acids();
    std::vector<std::string> get_a_set_amino_acids();

protected:
    std::map<int, int> transl_table_idx;

    acid::acids acid;

    void reset(std::vector<std::string>) override;
    void init_trans_table();
    const std::vector<std::string> factor_transl_table(int wordLength) const;

};

#endif //GCATCPP_ABSTRACTGENCODE_H
