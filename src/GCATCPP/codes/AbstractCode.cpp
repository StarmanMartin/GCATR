#include <utility>

//
// Created by Martin on 2/7/2019.
//



//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <regex>
#include <iterator>
#include <unordered_set>
#include <algorithm>


#include "../tester/AbstractTester.h"
#include "../modification/AbstractModifier.h"
#include "../geneticCode/CodonTranslTables.h"

#include "AbstractCode.h"

#define EMPTY_SEQUNECE "#"


AbstractCode::AbstractCode(const std::string &sequence, unsigned int word_length) : string_sequence(sequence),
                                                                                    is_tested(false), is_ok(false),
                                                                                    is_alphabet_set(false) {
    this->word_length = {};

    std::vector<std::string> code_temp_vec(sequence.length() / word_length);
    this->word_length.push_back((signed) word_length);

    for (struct {
             unsigned int letter;
             int word;
         } idx = {0, 0};
         idx.letter + word_length - 1 < sequence.length();
         idx.word++, idx.letter += word_length) {
        code_temp_vec[idx.word] = sequence.substr(idx.letter, word_length);

    }

    this->reset(code_temp_vec);
}

AbstractCode::AbstractCode(const std::vector<std::string> &code_vec) : is_tested(false), is_ok(false), is_alphabet_set(false) {
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

void AbstractCode::reset(std::vector<std::string> code_param_vec) {
    this->code_vec.clear();
    std::unordered_set<std::string> s(code_param_vec.begin(), code_param_vec.end());
    this->code_vec.assign(s.begin(), s.end());
    sort(this->code_vec.begin(), this->code_vec.end());
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
        this->is_alphabet_set = true;
    }
}

std::string AbstractCode::as_string_sequence() {
    if (this->string_sequence != EMPTY_SEQUNECE) {
        return this->string_sequence;
    }
    if (this->code_vec.empty()) {
        return "";
    }

    std::string result;
    for (std::string const &s : this->code_vec) { result += s; }

    return this->string_sequence = result;
}

std::vector<std::string> AbstractCode::as_vector() const {
    return this->code_vec;
}

std::vector<std::string> AbstractCode::as_set() const{
    std::set<std::string> code_set(this->code_vec.begin(), this->code_vec.end());
    std::vector<std::string> code_vec_set(code_set.size());
    std::copy(code_set.begin(), code_set.end(), code_vec_set.begin());


    return code_vec_set;
}

void AbstractCode::set_alphabet(const std::string &new_alphabet) {

    this->alphabet.set_alphabet(new_alphabet);
    this->is_alphabet_set = true;
}

const Alphabet &AbstractCode::get_alphabet() const {
    return this->alphabet;
}

std::string AbstractCode::get_alphabet_as_string() const {
    return this->alphabet.as_string();
}

size_t AbstractCode::get_letter_value(const char &c) {
    return static_cast<size_t>(this->alphabet.get_letter_value(c));
}

std::vector<int> AbstractCode::get_word_length() {
    if (!this->test_code()) {
        return {0};
    }
    return this->word_length;
}

bool AbstractCode::run_test(const std::shared_ptr<AbstractTester> &t) {
    bool result = t->test(this);
    this->add_error_msges(t->get_error_msg());
    return result;
}

bool AbstractCode::run_test(const std::shared_ptr<AbstractTester> &t, int k) {
    bool result = t->test(this, k);
    this->add_error_msges(t->get_error_msg());
    return result;
}

void AbstractCode::run_modification(const std::shared_ptr<AbstractModifier> &t) {
    auto result = t->modify(this);
    this->add_error_msges(t->get_error_msg());
    this->reset(result);
    this->test_code();
}

std::string AbstractCode::to_string() const {

    const char *const delim = ", ";

    std::ostringstream imploded;
    std::copy(this->code_vec.begin(), this->code_vec.end(),
              std::ostream_iterator<std::string>(imploded, delim));

    return imploded.str();
}

bool AbstractCode::is_translatable() {
    return false;
}

int AbstractCode::calculateModulo(int frame, int length) {
    if (frame < 0) {
        return calculateModulo(frame + length, length);
    }
    return (frame % length);
}

std::vector<std::string> AbstractCode::get_tuples() {
    return this->code_vec;
}

std::vector<std::string> AbstractCode::get_nucleotide_tuples() {
    if(this->is_translatable()) {
        return this->code_vec;
    }

    return std::vector<std::string>();
}
