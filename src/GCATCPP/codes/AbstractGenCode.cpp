//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <numeric>
#include <iostream>
#include <regex>

#include "../tester/AbstractTester.h"

#include "AbstractGenCode.h"

#define EMPTY_SEQUNECE "#"



AbstractGenCode::AbstractGenCode( std::vector <std::string> code_vec) :
        code_vec(code_vec), is_tested(false), is_ok(false), string_sequence(EMPTY_SEQUNECE) {
    std::vector<int> temp_length(0);
    this->word_length = temp_length;

    std::vector< std::vector<unsigned int> > temp_circle(0);
    this->circle = temp_circle;

}


bool AbstractGenCode::test() {
    if (this->is_tested) {
        return this->is_ok;
    }

    this->is_tested = true;
    this->is_ok = true;

    if (this->code_vec.size() == 0) {
        this->error_msg = "Code is empty!";
        return (this->is_ok = false);
    }

    this->acid = acid::check_acid_type(this->as_string_sequence());

    if (this->acid == acid::NONE) {
        this->error_msg = "Code contains not known bases!";
        return (this->is_ok = false);
    }

    return true;
}

std::string AbstractGenCode::as_string_sequence() {
    if (this->string_sequence != EMPTY_SEQUNECE) {
        return this->string_sequence;
    }

    std::string result;
    for (std::string const &s : this->code_vec) { result += s; }

    return this->string_sequence = result;
}

std::vector< int > AbstractGenCode::get_word_length() const {
    return this->word_length;
}

virtual bool AbstractGenCode::run_test(std::shared_ptr<AbstractTester> t) {
    t->test(this);
}