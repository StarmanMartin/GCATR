//
// Created by Martin on 10.07.2018.
//

#ifndef GCATCPP_ABSTRACTGENCODE_H
#define GCATCPP_ABSTRACTGENCODE_H

#include <vector>

class AbstractGenCode {
public:
    explicit AbstractGenCode(std::vector<std::string>);

    virtual bool test();

    virtual bool is_circular() = 0;

public:
    std::vector<std::string> code_vec;
    bool is_tested;
    bool is_ok;
    std::string string_sequence;
    std::string error_msg;

    std::vector< int > word_length;
    std::vector< std::vector<unsigned int> > circle;

    virtual std::string as_string_sequence();

    virtual void add_circle(std::vector< unsigned int >);
};

#endif //GCATCPP_ABSTRACTGENCODE_H
