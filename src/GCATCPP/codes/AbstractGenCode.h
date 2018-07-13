//
// Created by Martin on 10.07.2018.
//

#ifndef GCATCPP_ABSTRACTGENCODE_H
#define GCATCPP_ABSTRACTGENCODE_H

#include <vector>
#include <memory>

#include "Acid.h"

class AbstractTester;

class AbstractModifier;

class AbstractGenCode {
public:
    explicit AbstractGenCode(std::vector<std::string>);
    AbstractGenCode(const AbstractGenCode &agc);

    virtual bool test_code();

    std::vector<int> get_word_length() const;

    std::string as_string_sequence();

    std::vector<std::string> as_vector();

    virtual bool is_circular()= 0;

    virtual void shift_tuples(int shifts = 1) = 0;

protected:
    std::vector<std::string> code_vec;
    bool is_tested;
    bool is_ok;
    std::string string_sequence;
    std::string error_msg;

    acid::acids acid;

    std::vector<int> word_length;

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
