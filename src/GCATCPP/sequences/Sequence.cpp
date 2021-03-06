//
// Created by martins on 05.10.19.
//

#include <iostream>
#include <regex>
#include <string>
#include "Sequence.h"

Sequence::Sequence(const std::string & seq,  size_t tuple_length) :seq(seq), tuple_length(tuple_length) {
    this->acid = acid::check_acid_type(seq);
    this->alphabet = Alphabet(seq);

    this->all_words = 0;
    this->word_count = {};

    this->seq_length = this->seq.length();

    this->is_seq = false;
    this->is_seq = this->test_seq();
}

bool Sequence::test_seq() {
    if(this->is_seq) { return true; }

    // Simple regular expression matching
    const std::regex seq_regex("^[a-zA-Z0-9]+$");

    if(this->seq_length < this->tuple_length || !std::regex_match(this->seq, seq_regex)) {
        return false;
    }


    // Extraction of a sub-match
    const std::regex base_regex("([a-zA-Z0-9]{" +  std::to_string(this->tuple_length) + "})");
    std::smatch base_match;

    std::string::const_iterator searchStart( this->seq.cbegin() );
    while (std::regex_search(searchStart, this->seq.cend(), base_match, base_regex)) {
        // The first sub_match is the whole string; the next
        // sub_match is the first parenthesized expression.
        searchStart = base_match.suffix().first;
        if (base_match.size() == 2) {
            std::string base =  base_match[1].str();
            this->code_vec.push_back(base);
            auto it = this->word_count.find(base);
            if(it == this->word_count.end()) {
                this->word_count[base]  = 1;
            } else {
                this->word_count[base] ++;
            }
        }
    }

    this->all_words = this->word_count.size();

    return true;
}

std::map<std::string, int> Sequence::get_tuple_count() const {
    return this->word_count;
}

size_t Sequence::get_number_tuples() const {
    return this->all_words;
}

std::string Sequence::get_alphabet() const {
    return this->alphabet.as_string();
}

std::vector<std::string> Sequence::get_tuples() {
    return this->code_vec;
}

std::vector<std::string> Sequence::get_nucleotide_tuples() {
    if(this->is_translatable()) {
        return this->code_vec;
    }

    return std::vector<std::string>();
}

bool Sequence::is_translatable() {
    return this->acid != acid::acids::NONE;
}

acid::acids Sequence::get_acid() {
    return this->acid;
}

std::vector<int> Sequence::get_word_length() {
    return {(int)this->tuple_length};
}

std::vector<std::string> Sequence::get_amino_acids() {
    if(!this->is_translatable()) {
        return this->code_vec;
    }

    return this->_get_amino_acids(this);
}

std::vector<std::string> Sequence::get_a_set_amino_acids() {
    if(!this->is_translatable()) {
        return this->code_vec;
    }

    return this->_get_a_set_amino_acids(this);
}
