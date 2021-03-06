//
// Created by Martin on 2/7/2019.
//

#ifndef GCATCPP_ABSTRACTCODE_H
#define GCATCPP_ABSTRACTCODE_H


#include <utility>
#include <vector>
#include <set>
#include <memory>

#include "../helper/AbstractErrorManager.h"
#include "Alphabet.h"
#include "../interfaces/AbstractTupleContainer.h"

class AbstractTester;

class AbstractModifier;

namespace seq {

    struct Seq_Result {
        std::vector<std::string> words;
        std::vector<std::string> parts;
        std::vector<std::size_t> circularPermutations;
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



class AbstractCode : public err::AbstractErrorManager, public AbstractTupleContainer {
public:
    explicit AbstractCode(const std::vector<std::string> &);
    explicit AbstractCode(const std::string&, unsigned int);

    AbstractCode(const AbstractCode &agc);

    virtual bool test_code();



    std::vector<int> get_word_length() override;

    std::string as_string_sequence();

    std::vector<std::string> as_vector() const;
    std::vector<std::string> as_unsorted_vector() const;
    std::vector<std::string> as_set() const;

    virtual bool is_circular()= 0;
    virtual bool is_k_circular(int k)= 0;
    virtual bool is_cn_circular() = 0;
    virtual bool is_comma_free() = 0;


    virtual bool is_translatable();

    virtual void shift_tuples(size_t shifts=1) = 0; // NOLINT
    virtual void transform_tuples(const std::string& from_rule, const std::string& to_rule) = 0; // NOLINT

    virtual seq::Seq_Result find_code_in_sequence(const std::string&, int) = 0;

    const Alphabet& get_alphabet() const;
    std::string get_alphabet_as_string() const;
    void set_alphabet(const std::string&);
    virtual size_t get_letter_value(const char &);

    std::vector<std::string> get_tuples() override;
    std::vector<std::string> get_nucleotide_tuples() override;

    static int calculateModulo(int frame, int length);

    static int getMaxLength(int n, int length);

protected:
    std::vector<std::string> code_vec;
    std::vector<std::string> code_vec_unsorted;
    bool is_tested;
    bool is_ok;

    Alphabet alphabet;
    bool is_alphabet_set;

    std::string string_sequence;

    std::vector<int> word_length;

    ~AbstractCode() override {
        this->print_errors();
    };

    void set_code_properties ();

    virtual void reset(std::vector<std::string>);
    bool run_test(const std::shared_ptr<AbstractTester>&, int k);
    bool run_test(const std::shared_ptr<AbstractTester>&);

    void run_modification(const std::shared_ptr<AbstractModifier>&);

    std::string to_string() const;

    explicit operator std::string() const override { return this->to_string(); }

    friend std::ostream &operator<<(std::ostream &_stream, AbstractCode const &mc) {
        _stream << mc.to_string();
        return _stream;
    }
};

#endif //GCATCPP_ABSTRACTCODE_H
