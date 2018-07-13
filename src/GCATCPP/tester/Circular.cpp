//
// Created by Martin on 12.07.2018.
//

#include "Circular.h"
#include <string>
#include <iostream>
#include <regex>

bool Circular::test(std::shared_ptr<AbstractGenCode> code) {

}


bool Circular::is_circular(std::shared_ptr<AbstractGenCode> code) {
    std::string string_sequence = code->as_string_sequence();
    bool is_code_circular = true;

    for (unsigned int i = 1; i < (1 + code->get_word_length()[0]) / 2; ++i) {
        for (unsigned int j = 0; j < string_sequence.length(); j += code->get_word_length()[0]) {
            std::string current_substring = string_sequence.substr(j, i);
            unsigned int start_word_idx = {j / (unsigned) code->get_word_length()[0]};

            is_code_circular = is_code_circular & this->rec_is_circular(code,
                                                                        std::vector<unsigned int>(),
                                                                        current_substring,
                                                                        start_word_idx);
        }
    }

    return is_code_circular;
}

bool Circular::rec_is_circular(std::shared_ptr<AbstractGenCode> code,
                               std::vector<unsigned int> chained_indexes,
                               std::string current_substring,
                               unsigned int current_word_pos) {

    std::regex r("(?=(" + current_substring + ")).");
    auto it_find = std::find(chained_indexes.begin(), chained_indexes.end(), current_word_pos);

    if (chained_indexes.size() % 2 == 0 && it_find != chained_indexes.end()) {
        auto index = std::distance(chained_indexes.begin(), it_find);
        if (index == 0) {
            this->add_circle(chained_indexes);
        }
        return false;
    }

    chained_indexes.push_back(current_word_pos);
    std::smatch sm;
    bool is_code_circular = true;

    std::string string_sequence = code->as_string_sequence();

    for (auto it = std::sregex_iterator(string_sequence.begin(), string_sequence.end(), r);
         it != std::sregex_iterator();
         ++it) {

        unsigned int letter_pos = (unsigned int) it->position();
        unsigned int inverse_size = ((unsigned int) code->get_word_length()[0]) - ((unsigned int) current_substring.length());

        if (letter_pos % code->get_word_length()[0] == inverse_size) {
            unsigned int word_pos = (letter_pos / code->get_word_length()[0]);
            std::string new_sub_word = string_sequence.substr(word_pos * code->get_word_length()[0],
                                                                         inverse_size);
            is_code_circular = is_code_circular &
                               this->rec_is_circular(code, chained_indexes, new_sub_word, word_pos);


        }

    }


    return is_code_circular;
}

void Circular::add_circle(std::vector<unsigned int> chained_indexes) {
    int min_pos = int(distance(chained_indexes.begin(), min_element(chained_indexes.begin(), chained_indexes.end())));
    std::rotate(chained_indexes.begin(), chained_indexes.begin() + min_pos, chained_indexes.end());

    for (auto vector : this->circle) {
        if (equal(vector.begin(), vector.end(), chained_indexes.begin())) {
            return;
        }
    }

    this->circle.push_back(chained_indexes);
}