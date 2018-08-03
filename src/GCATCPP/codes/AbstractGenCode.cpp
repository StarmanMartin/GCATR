//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <numeric>
#include <iostream>
#include <regex>
#include <sstream>
#include <iterator>

#include "../tester/AbstractTester.h"
#include "../modification/AbstractModifier.h"

#include "AbstractGenCode.h"

#define EMPTY_SEQUNECE "#"


AbstractGenCode::AbstractGenCode(std::string sequence, unsigned int word_length) : string_sequence(sequence) {
    this->reset({});

    std::vector<std::string> code_vec(sequence.length() / word_length);
    this->word_length.push_back((signed) word_length);

    for (struct {
             unsigned int letter;
             int word;
         } idx = {0, 0};
         idx.letter < sequence.length();
         idx.word++, idx.letter += word_length) {
        code_vec[idx.word] = sequence.substr(idx.letter, word_length);

    }

    this->code_vec = code_vec;
}

AbstractGenCode::AbstractGenCode(std::vector<std::string> code_vec) {
    this->reset(code_vec);
}

AbstractGenCode::AbstractGenCode(const AbstractGenCode &agc) {
    this->code_vec = agc.code_vec;
    this->is_tested = false;
    this->is_ok = agc.is_ok;
    this->string_sequence = agc.string_sequence;
    std::vector<int> temp_length(agc.word_length);
    this->word_length = temp_length;
}

void AbstractGenCode::reset(std::vector<std::string> code_vec) {
    this->code_vec = code_vec;
    this->is_tested = false;
    this->is_ok = false;
    this->string_sequence = EMPTY_SEQUNECE;
    this->word_length = {};
}


bool AbstractGenCode::test_code() {
    if (this->is_tested) {
        return this->is_ok;
    }

    this->is_tested = true;
    this->is_ok = true;
    this->acid = acid::check_acid_type(this->as_string_sequence());

    if (this->code_vec.size() == 0) {
        this->add_error_msg("Code is empty!");
        return (this->is_ok = false);
    }


    if (this->acid == acid::NONE) {
        this->add_error_msg("Code contains not known bases!");
        return (this->is_ok = false);
    }

    return (this->is_ok = true);
}

acid::acids AbstractGenCode::get_acid() {
    this->test_code();
    return this->acid;
}

std::string AbstractGenCode::as_string_sequence() {
    if (this->string_sequence != EMPTY_SEQUNECE) {
        return this->string_sequence;
    }

    std::string result;
    for (std::string const &s : this->code_vec) { result += s; }

    return this->string_sequence = result;
}

std::vector<std::string> AbstractGenCode::as_vector() const {
    return this->code_vec;
}


std::vector<int> AbstractGenCode::get_word_length() {
    this->test_code();
    return this->word_length;
}

bool AbstractGenCode::run_test(std::shared_ptr<AbstractTester> t) {
    bool result = t->test(this);
    this->add_error_msges(t->get_error_msg());
    return result;
}

void AbstractGenCode::run_modification(std::shared_ptr<AbstractModifier> t, void *args) {
    auto result = t->modify(this, args);
    this->add_error_msges(t->get_error_msg());
    this->reset(result);
    this->test_code();
}

const std::string AbstractGenCode::to_string() const {

    const char *const delim = ", ";

    std::ostringstream imploded;
    std::copy(this->code_vec.begin(), this->code_vec.end(),
              std::ostream_iterator<std::string>(imploded, delim));

    return "Acid: " + acid::acid_to_string(this->acid) + "\n " + imploded.str();
}