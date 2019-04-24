#include <utility>

//
// Created by Martin on 2/7/2019.
//



//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <numeric>
#include <iostream>
#include <regex>
#include <sstream>
#include <iterator>
#include <utility>
#include "../tester/AbstractTester.h"
#include "../modification/AbstractModifier.h"
#include "../geneticCode/CodonTranslTables.h"

#include "AbstractCode.h"

#define EMPTY_SEQUNECE "#"


AbstractCode::AbstractCode(std::string sequence, unsigned int word_length) : string_sequence(sequence) {
    this->word_length = {};

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

    this->reset(code_vec);
}

AbstractCode::AbstractCode(const std::vector<std::string> &code_vec) {
    this->reset(code_vec);
}

AbstractCode::AbstractCode(const AbstractCode &agc) : AbstractErrorManager(agc) {
    this->code_vec = agc.code_vec;
    this->is_tested = false;
    this->is_ok = agc.is_ok;
    this->string_sequence = agc.string_sequence;
    std::vector<int> temp_length(agc.word_length);
    this->word_length = temp_length;
    this->set_alphabet(agc.get_alphabet_as_string());
    this->is_alphabet_set = agc.is_alphabet_set;
}

void AbstractCode::reset(std::vector<std::string> code_vec) {
    this->code_vec = std::move(code_vec);
    this->is_tested = false;
    this->is_ok = false;
    this->string_sequence = EMPTY_SEQUNECE;
    this->word_length = {};
    this->is_alphabet_set = false;
    this->set_code_properties();
}


bool AbstractCode::test_code() {
    if (this->is_tested) {
        return this->is_ok;
    }

    this->is_tested = true;
    this->is_ok = true;

    if (this->code_vec.empty()) {
        this->add_error_msg("Code is empty!");
        return (this->is_ok = false);
    }

    this->set_code_properties();

    return (this->is_ok = true);
}

void AbstractCode::set_code_properties() {
    this->word_length.clear();
    for (const auto &word : this->code_vec) {
        auto l = (signed) word.length();
        bool found = (std::find(word_length.begin(), word_length.end(), l) != word_length.end());
        if (!found) {
            this->word_length.push_back(l);
        }
    }

    if (!this->is_alphabet_set) {
        this->set_alphabet(this->as_string_sequence());
        this->is_alphabet_set = false;
    }
}

std::string AbstractCode::as_string_sequence() {
    if (this->string_sequence != EMPTY_SEQUNECE) {
        return this->string_sequence;
    } if(this->code_vec.empty()) {
        return "";
    }

    std::string result;
    for (std::string const &s : this->code_vec) { result += s; }

    return this->string_sequence = result;
}

std::vector<std::string> AbstractCode::as_vector() const {
    return this->code_vec;
}

void AbstractCode::set_alphabet(std::string new_alphabet) {

    this->alphabet.set_alphabet(std::move(new_alphabet));
    this->is_alphabet_set = true;
}

const Alphabet& AbstractCode::get_alphabet() const {
    return this->alphabet;
}

std::string AbstractCode::get_alphabet_as_string() const {
    return this->alphabet.as_string();
}

size_t AbstractCode::get_letter_value(const char &c) {
    return static_cast<size_t>(this->alphabet.get_letter_value(c));
}

std::vector<int> AbstractCode::get_word_length() {
    this->test_code();
    return this->word_length;
}

bool AbstractCode::run_test(std::shared_ptr<AbstractTester> t) {
    bool result = t->test(this);
    this->add_error_msges(t->get_error_msg());
    return result;
}

bool AbstractCode::run_test(std::shared_ptr<AbstractTester> t, int k) {
    bool result = t->test(this, k);
    this->add_error_msges(t->get_error_msg());
    return result;
}

void AbstractCode::run_modification(std::shared_ptr<AbstractModifier> t, void *args) {
    auto result = t->modify(this, args);
    this->add_error_msges(t->get_error_msg());
    this->reset(result);
    this->test_code();
}

const std::string AbstractCode::to_string() const {

    const char *const delim = ", ";

    std::ostringstream imploded;
    std::copy(this->code_vec.begin(), this->code_vec.end(),
              std::ostream_iterator<std::string>(imploded, delim));

    return imploded.str();
}
