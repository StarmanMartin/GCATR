//
// Created by Martin on 12.07.2018.
//

#include "CommaFree.h"
#include <string>
#include <iostream>
#include <regex>

bool CommaFree::test(AbstractGenCode *code) {
    return this->is_comma_free(code);
}


bool CommaFree::is_comma_free(AbstractGenCode *code) {
    std::string string_sequence = code->as_string_sequence();

    for (unsigned int i = 1; i < code->get_word_length()[0]; ++i) {
        for (unsigned int j = 0; j < string_sequence.length(); j += code->get_word_length()[0]) {
            std::string current_substring = string_sequence.substr(j, i);
            unsigned int start_word_idx = {j / (unsigned) code->get_word_length()[0]};

            if (!this->rec_is_comma_free(code,
                                         std::vector<unsigned int>(),
                                         current_substring,
                                         start_word_idx)) {
                return false;
            }
        }
    }

    return true;
}

bool CommaFree::rec_is_comma_free(AbstractGenCode *code,
                                  std::vector<unsigned int> chained_indexes,
                                  std::string current_substring,
                                  unsigned int current_word_pos) {

    chained_indexes.push_back(current_word_pos);
    if(chained_indexes.size() > 3) {
        std::string codes = code->as_vector()[chained_indexes[0]] + ", " + code->as_vector()[chained_indexes[1]] + ", " + code->as_vector()[chained_indexes[2]];
        this->add_error_msg("Not camma-free set -> " + codes);
        return false;
    }

    std::regex r("(?=(" + current_substring + ")).");
    std::smatch sm;

    std::string string_sequence = code->as_string_sequence();

    for (auto it = std::sregex_iterator(string_sequence.begin(), string_sequence.end(), r);
         it != std::sregex_iterator();
         ++it) {

        unsigned int letter_pos = (unsigned int) it->position();
        unsigned int inverse_size =
                ((unsigned int) code->get_word_length()[0]) - ((unsigned int) current_substring.length());

        if (letter_pos % code->get_word_length()[0] == inverse_size) {
            unsigned int word_pos = (letter_pos / code->get_word_length()[0]);
            std::string new_sub_word = string_sequence.substr(word_pos * code->get_word_length()[0],
                                                              inverse_size);
            if(!this->rec_is_comma_free(code, chained_indexes, new_sub_word, word_pos)) {
                return false;
            }


        }

    }


    return true;
}