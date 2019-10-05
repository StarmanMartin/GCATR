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
        if (base_match.size() == 2) {
            std::string base =  base_match[1].str();

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
