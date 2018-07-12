//
// Created by Martin on 27.06.2018.
//
#include <string>
#include <numeric>
#include <iostream>
#include <regex>

#include "StdGenCode.h"


StdGenCode::StdGenCode(std::vector<std::string> code_vec) : AbstractGenCode(code_vec) {

}


bool StdGenCode::test() {

    if (!AbstractGenCode::test()) {
        return this->is_ok;
    }


    this->word_length.empty();
    this->word_length.push_back((signed) this->code_vec[0].length());

    for (std::string word : this->code_vec) {
        if (this->word_length[0] != (signed) word.length()) {
            this->error_msg = "Word size dose not match";
            this->word_length.empty();
            return (this->is_ok = false);
        }
    }

    return true;
}

bool StdGenCode::is_circular() {
    if (!this->test()) { return false; }

    std::string string_sequence = this->as_string_sequence();
    bool is_code_circular = true;

    for (unsigned int i = 1; i < (1+this->word_length[0]) / 2; ++i) {
        for (unsigned int j = 0; j < string_sequence.length(); j += this->word_length[0]) {
            std::string current_substring = string_sequence.substr(j, i);
            unsigned int start_word_idx = {j / (unsigned) this->word_length[0]};

            is_code_circular = is_code_circular & this->rec_is_circular(std::vector<unsigned int>(),
                                                                        current_substring,
                                                                        start_word_idx);
        }
    }

    return is_code_circular;
}

bool StdGenCode::rec_is_circular(std::vector<unsigned int> chained_indexes,
                                 std::string current_substring,
                                 unsigned int current_word_pos) {

    std::regex r("(?=(" + current_substring + ")).");
    auto it_find = std::find(chained_indexes.begin(), chained_indexes.end(), current_word_pos);

    if (chained_indexes.size() % 2 == 0 && it_find != chained_indexes.end()) {
        auto index = std::distance(chained_indexes.begin(), it_find);
        if(index == 0) {
            this->add_circle(chained_indexes);
        }
        return false;
    }

    chained_indexes.push_back(current_word_pos);
    std::smatch sm;
    bool is_code_circular = true;

    for (auto it = std::sregex_iterator(this->string_sequence.begin(), this->string_sequence.end(), r);
         it != std::sregex_iterator();
         ++it) {

        unsigned int letter_pos = (unsigned int) it->position();
        unsigned int inverse_size = ((unsigned int) this->word_length[0]) - ((unsigned int) current_substring.length());

         if (letter_pos % this->word_length[0] == inverse_size) {
            unsigned int word_pos = (letter_pos / this->word_length[0]);
            std::string new_sub_word = this->as_string_sequence().substr(word_pos * this->word_length[0],
                                                                         inverse_size);
            is_code_circular = is_code_circular &
                               this->rec_is_circular(chained_indexes, new_sub_word, word_pos);


        }

    }


    return is_code_circular;
}