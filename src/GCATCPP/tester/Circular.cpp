//
// Created by Martin on 12.07.2018.
//

#include "Circular.h"
#include <string>
#include <iostream>
#include <regex>
#include <climits>

bool Circular::test(AbstractCode *code) {
    this->longest_path = {};
    this->circle = {};
    this->longest_path_size = 0;

    return this->is_circular(code);
}


bool Circular::is_circular(AbstractCode *code) {
    std::string string_sequence = code->as_string_sequence();
    bool is_code_circular = true;

    for (unsigned int i = 1; i < code->get_word_length()[0]; ++i) {
        for (unsigned int j = 0; j < string_sequence.length(); j += code->get_word_length()[0]) {
            std::string current_prefix = string_sequence.substr(j, i);
            std::string current_suffix = string_sequence.substr(j + i, code->get_word_length()[0] - i);
            unsigned int start_word_idx = {j / (unsigned) code->get_word_length()[0]};
            graph::Graph path;
            path.add_vertices(current_prefix, current_suffix);
            is_code_circular = is_code_circular & this->rec_is_circular(code,
                                                                        std::vector<unsigned int>(),
                                                                        path,
                                                                        current_prefix,
                                                                        start_word_idx);
        }
    }

    return is_code_circular;
}

bool Circular::rec_is_circular(AbstractCode *code,
                               std::vector<unsigned int> chained_indexes,
                               graph::Graph path,
                               std::string current_prefix,
                               unsigned int current_word_pos) {

    std::regex r("(?=(" + current_prefix + ")).");

   for(int i = 0; i < chained_indexes.size(); ++i) {
        auto word_pos = chained_indexes[i];
        if (word_pos == current_word_pos) {
            if ((chained_indexes.size() - i) % 2 == 0) {
                if (i == 0) {
                    this->add_circle(path);
                }
                return false;
            }
        }
    }

    chained_indexes.push_back(current_word_pos);
    std::smatch sm;
    bool is_code_circular = true;

    std::string string_sequence = code->as_string_sequence();
    bool found_extension = false;
    for (auto it = std::sregex_iterator(string_sequence.begin(), string_sequence.end(), r);
         it != std::sregex_iterator();
         ++it) {

        unsigned int letter_pos = (unsigned int) it->position();
        unsigned int inverse_size =
                ((unsigned int) code->get_word_length()[0]) - ((unsigned int) current_prefix.length());

        if (letter_pos % code->get_word_length()[0] == inverse_size) {
            found_extension = true;
            unsigned int word_pos = (letter_pos / code->get_word_length()[0]);
            std::string new_sub_word = string_sequence.substr(word_pos * code->get_word_length()[0], inverse_size);

            graph::Graph copyOfGraph(path);
            copyOfGraph.add_vertices(new_sub_word, current_prefix);
            is_code_circular = is_code_circular &
                               this->rec_is_circular(code, chained_indexes, copyOfGraph, new_sub_word, word_pos);

            //0ACACCCA
            //1ACCCAAA
            //2AAACACC
            //3CACCCAA
            //4CCAAACA
            //5CCCAAAC
            //6AACACCC
            //7CAAACAC
        }

    }

    if (!found_extension) {
        this->add_longest_path(path);
    }

    return is_code_circular;
}

void Circular::add_circle(graph::Graph circle_path) {
    this->longest_path_size = UINT_MAX;
    this->longest_path = {};
    for (auto graph : this->circle) {
        if (graph.compare(circle_path) == 0) {
            return;
        }
    }

    this->circle.push_back(circle_path);
}

void Circular::add_longest_path(graph::Graph circle_path) {
    if (this->longest_path_size > circle_path.get_edges().size()) { return; }

    if (this->longest_path_size < circle_path.get_edges().size()) {
        this->longest_path_size = (unsigned int) circle_path.get_edges().size();
        this->longest_path = {circle_path};
    } else {
        for (auto graph : this->longest_path) {
            if (graph.compare(circle_path) == 0) {
                return;
            }
        }

        this->longest_path.push_back(circle_path);
    }


}

std::vector<graph::Graph> Circular::get_circles() {
    return this->circle;
}

std::vector<graph::Graph> Circular::get_longest_path() {
    return this->longest_path;

}