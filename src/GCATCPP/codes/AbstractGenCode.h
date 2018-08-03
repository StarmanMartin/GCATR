//
// Created by Martin on 10.07.2018.
//

#ifndef GCATCPP_ABSTRACTGENCODE_H
#define GCATCPP_ABSTRACTGENCODE_H

#include <vector>
#include <memory>

#include "Acid.h"
#include "../helper/AbstractErrorManager.h"

class AbstractTester;

class AbstractModifier;

class AbstractGenCode : public err::AbstractErrorManager {
public:
    explicit AbstractGenCode(std::vector<std::string>);
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

    virtual void shift_tuples(int shifts = 1) = 0;

    acid::acids get_acid();

protected:
    std::vector<std::string> code_vec;
    bool is_tested;
    bool is_ok;
    std::string string_sequence;

    acid::acids acid;

    std::vector<int> word_length;

    virtual ~AbstractGenCode() {
        this->print_errors();
    };

    void reset(std::vector<std::string>);

    bool run_test(std::shared_ptr<AbstractTester>);

    void run_modification(std::shared_ptr<AbstractModifier>, void *args);

    const std::string to_string() const;

    operator std::string() const { return this->to_string(); }

    friend std::ostream &operator<<(std::ostream &_stream, AbstractGenCode const &mc) {
        _stream << mc.to_string();
        return _stream;
    }
};

#endif //GCATCPP_ABSTRACTGENCODE_H
