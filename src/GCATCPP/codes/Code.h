//
// Created by Martin on 2/7/2019.
//

#ifndef GCATCPP_CODE_H
#define GCATCPP_CODE_H


#include "AbstractCode.h"

class Code : public AbstractCode {
public:
    explicit Code(const std::vector<std::string> &);
    explicit Code(std::string, unsigned int);

    Code(const Code &agc);

    bool test_code() override;
    bool is_k_circular(int k) override;

    bool is_circular() override;
    bool is_cn_circular() override;
    bool is_comma_free() override;
    seq::Seq_Result find_code_in_sequence(const std::string& seq, int frame) override;
    void shift_tuples(size_t shifts=1) override; // NOLINT
    void transform_tuples(const std::string& from_rule, const std::string& to_rule) override; // NOLINT
};

#endif //GCATCPP_CODE_H
