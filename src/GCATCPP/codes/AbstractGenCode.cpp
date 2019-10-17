//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <regex>
#include <utility>
#include "../tester/AbstractTester.h"
#include "../geneticCode/CodonTranslTables.h"

#include "AbstractGenCode.h"
#include "../modification/TransformTuples.h"
#include "../tester/SelfComplimentary.h"

#define EMPTY_SEQUNECE "#"


AbstractGenCode::AbstractGenCode(std::string sequence, unsigned int word_length) : Code(std::move(sequence), word_length) {
    this->acid = acid::acids::NONE;
}

AbstractGenCode::AbstractGenCode(const std::vector<std::string> &code_vec) : Code(code_vec) {
    this->acid = acid::acids::NONE;
}

AbstractGenCode::AbstractGenCode(const AbstractGenCode &agc) : Code(agc) {
    this->acid = acid::acids::NONE;
}

void AbstractGenCode::reset(std::vector<std::string> code_vec) {
    AbstractCode::reset(code_vec);
    this->acid = acid::check_acid_type(this->as_string_sequence());
    this->transl_table_idx = {};
}

bool AbstractGenCode::test_code() {
    if (this->is_tested || !Code::test_code()) {
        return this->is_ok;
    }

    this->acid = acid::check_acid_type(this->as_string_sequence());

    if (this->acid == acid::NONE) {
        this->add_error_msg("Code contains not known bases!");
        return (this->is_ok = false);
    }

    this->set_alphabet(acid::acid_as_alphabet(this->acid));

    return (this->is_ok = true);
}

acid::acids AbstractGenCode::get_acid() {
    this->test_code();
    return this->acid;
}

bool AbstractGenCode::is_self_complementary() {
    if (!this->test_code()) { return false; }
    auto tester = std::make_shared<SelfComplimentary>();
    return this->run_test(tester);
}


void AbstractGenCode::transform_tuples_by_name(const std::string &rule_name) {
    if (!this->test_code()) { return; }
    auto tester = std::make_shared<TransformTuples>(rule_name, this->get_acid());
    this->run_modification(tester);
}

void AbstractGenCode::setTranslTableByIdx(int idx, int forWordLength) {
    if (!this->test_code()) {
        return;
    }
    AbstractTranslatable::setTranslTableByIdx(idx, forWordLength);
}

void AbstractGenCode::setTranslTableByName(const std::string &name, int forWordLength) {
    if (!this->test_code()) {
        return;
    }
    AbstractTranslatable::setTranslTableByName(name, forWordLength);
}

void AbstractGenCode::setTranslTableToStandardCode(int forWordLength) {
    if (!this->test_code()) {
        return;
    }

    AbstractTranslatable::setTranslTableToStandardCode(forWordLength);
}

void AbstractGenCode::setTranslTableByIdx(int idx) {
    return this->setTranslTableByIdx(idx, this->get_word_length()[0]);
}

void AbstractGenCode::setTranslTableByName(const std::string &name) {
    return this->setTranslTableByName(name, this->get_word_length()[0]);
}

void AbstractGenCode::setTranslTableToStandardCode() {
    return this->setTranslTableToStandardCode(this->get_word_length()[0]);
}

std::vector<std::string> AbstractGenCode::construct_transl_table(int wordLength, acid::acids acid_type) const {
    return AbstractTranslatable::construct_transl_table(wordLength, acid_type);
}

std::vector<std::string> AbstractGenCode::get_amino_acids() {
    if (!this->test_code()) {
        this->add_error_msg("Code can not be translated");
        return {};
    }

    return this->_get_amino_acids(this);
}

std::vector<std::string> AbstractGenCode::get_a_set_amino_acids() {
    if (!this->test_code()) {
        this->add_error_msg("Code can not be translated");
        return {};
    }

    return this->_get_a_set_amino_acids(this);
}


