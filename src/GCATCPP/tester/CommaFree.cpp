//
// Created by Martin on 12.07.2018.
//

#include "CommaFree.h"
#include <string>
#include <iostream>
#include <regex>
#include "../miner/LongestPathMiner.h"
#include "../graph/Graph.h"

bool CommaFree::test(AbstractCode *code) {
    return this->is_comma_free(code);
}


bool CommaFree::is_comma_free(AbstractCode *code) {
    this->suppress_errors();
    auto res = miner::LongestPathMiner::mine_path_as_vector(code);
    return !res.empty() && res[0].size() < 4;

}

bool CommaFree::rec_is_comma_free(AbstractCode *code,
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