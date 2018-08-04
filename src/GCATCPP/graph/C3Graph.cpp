//
// Created by Martin on 04.08.2018.
//

#include "C3Graph.h"
using namespace graph;

void C3Graph::add_word(std::string word) {
    if(word.length() != 3) {
        this->add_error_msg("For a C_3 graph the codon length has to be 3");
        return;
    }
    Graph::add_word(word);
    for (size_t i = 1; i < word.length(); ++i) {
        this->add_vertices(word.substr(1,1), word.substr(2,1) + word.substr(0,1));
    }
}