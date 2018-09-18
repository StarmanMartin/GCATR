//
// Created by Martin on 10.07.2018.
//

#ifndef GCATCPP_ABSTRACTGENCODE_H
#define GCATCPP_ABSTRACTGENCODE_H

#include <utility>
#include <vector>
#include <memory>

#include "Acid.h"
#include "../helper/AbstractErrorManager.h"

class AbstractTester;

class AbstractModifier;

namespace seq {

    struct Seq_Result {
        std::vector<std::string> words;
        std::vector<std::string> parts;
        std::string rest;
        std::vector<unsigned int> idx_list;
        std::string seq;
        unsigned int longest_match;
        double total_match_in_percent;

        explicit Seq_Result(std::string seq) :
                seq(std::move(seq)), longest_match(0), total_match_in_percent(0) {}
    };

    typedef struct Seq_Result Seq_Result;
}



class AbstractGenCode : public err::AbstractErrorManager {
public:
    explicit AbstractGenCode(const std::vector<std::string> &);
    explicit AbstractGenCode(std::string, unsigned int);
    
    AbstractGenCode(const AbstractGenCode &agc);

    virtual bool test_code();

    std::vector<int> get_word_length();

    std::string as_string_sequence();

    std::vector<std::string> as_vector() const;

    virtual bool is_circular()= 0;
    virtual bool is_cn_circular() = 0;
    virtual bool is_self_complementary() = 0;
    virtual bool is_comma_free() = 0;

    virtual void shift_tuples(int shifts=1) = 0; // NOLINT

    virtual seq::Seq_Result find_code_in_sequence(const std::string &) = 0;

    acid::acids get_acid();

    void setTranslTableByIdx(int idx, int forWordLength);
    void setTranslTableByName(const std::string &name, int forWordLength);
    void setTranslTableToStandardCode(int forWordLength);

    std::vector<std::string> get_amino_acids();

protected:
    std::map<int, int> transl_table_idx;
    std::vector<std::string> code_vec;
    bool is_tested;
    bool is_ok;
    std::string string_sequence;

    acid::acids acid;

    std::vector<int> word_length;

    ~AbstractGenCode() override {
        this->print_errors();
    };

    void reset(std::vector<std::string>);
    const std::vector<std::string> factor_transl_table(int wordLength) const;

    bool run_test(std::shared_ptr<AbstractTester>);

    void run_modification(std::shared_ptr<AbstractModifier>, void *args);

    const std::string to_string() const;

    explicit operator std::string() const override { return this->to_string(); }

    friend std::ostream &operator<<(std::ostream &_stream, AbstractGenCode const &mc) {
        _stream << mc.to_string();
        return _stream;
    }
};

#endif //GCATCPP_ABSTRACTGENCODE_H
