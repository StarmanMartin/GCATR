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

#include "AbstractGenCode.h"

#define EMPTY_SEQUNECE "#"


AbstractGenCode::AbstractGenCode(std::string sequence, unsigned int word_length) : Code(sequence, word_length) {
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
    this->acid = acid::acids::NONE;
    this->transl_table_idx  = {};
}

void AbstractGenCode::init_trans_table() {
    if(this->transl_table_idx.size() == 0) {
        for (auto wl : this->get_word_length()) {
            this->setTranslTableToStandardCode(wl);
        }
    }
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

    return (this->is_ok = true);
}

acid::acids AbstractGenCode::get_acid() {
    this->test_code();
    return this->acid;
}

void AbstractGenCode::setTranslTableByIdx(int idx, int forWordLength) {
    this->transl_table_idx[forWordLength] = idx;
}

void AbstractGenCode::setTranslTableByName(const std::string &name, int forWordLength) {
    switch(forWordLength) {
        case 3:
            this->transl_table_idx[forWordLength] = gen_codes::CodonTranslTables::getInstance().getIdxByName(name);
            break;
        default:
            break;
    }

}

void AbstractGenCode::setTranslTableToStandardCode(int forWordLength) {
    this->transl_table_idx[forWordLength] = 1;
}

const std::vector<std::string> AbstractGenCode::factor_transl_table(int wordLength) const {
    if(!this->transl_table_idx.count(wordLength)) {
        return std::vector<std::string>();
    }

    int translCodeIdx = this->transl_table_idx.at(wordLength);

    switch(wordLength) {
        case 3:
            return gen_codes::CodonTranslTables::getInstance().getCodeByIndex(translCodeIdx, this->acid);
        default:
            return std::vector<std::string>();
    }
}

std::vector<std::string> AbstractGenCode::get_amino_acids() {
    std::vector<std::string> vec_acids;
    this->test_code();
    this->init_trans_table();
    std::map<int, std::vector<std::string>> translTables;
    for(const std::string &codon : this->code_vec) {
        auto wordLength = (int) codon.length();
        if(!translTables.count(wordLength)) {
            translTables[wordLength] = this->factor_transl_table(wordLength);
        }

        auto it = std::find(translTables[wordLength].begin(), translTables[wordLength].end(), codon);
        if (it != translTables[wordLength].end()) {
            it++;
            vec_acids.push_back(*it);
        } else
            vec_acids.push_back(codon);
    }

    return vec_acids;
}

