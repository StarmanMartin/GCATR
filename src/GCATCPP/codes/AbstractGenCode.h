//
// Created by Martin on 10.07.2018.
//

#ifndef GCATCPP_ABSTRACTGENCODE_H
#define GCATCPP_ABSTRACTGENCODE_H

#include <vector>
#include "Acid.h"

class AbstractTester;

class AbstractGenCode {
public:
    explicit AbstractGenCode(std::vector<std::string>);

    virtual bool test();

    virtual bool is_circular() = 0;

    virtual std::vector< int > get_word_length() const;
    virtual std::string as_string_sequence();

protected:
    std::vector<std::string> code_vec;
    bool is_tested;
    bool is_ok;
    std::string string_sequence;
    std::string error_msg;

    acid::acids acid;

    std::vector< int > word_length;

    virtual bool run_test(std::shared_ptr<AbstractTester>);

    const std::string to_string() const { return acid::acid_to_string(this->acid); }
    operator std::string() const { return this->to_string(); }

    friend std::ostream & operator<<(std::ostream & _stream, AbstractGenCode const & mc) {
        _stream << mc.to_string();
        return _stream;
    }
};

#endif //GCATCPP_ABSTRACTGENCODE_H
