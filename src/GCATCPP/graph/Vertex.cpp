//
// Created by Martin on 18.07.2018.
//
#include "../codes/Acid.h"

#include "Vertex.h"

using namespace graph;

Vertex::Vertex(std::string label) : label(label), index(0) {
    this->calculate_index();
}

int Vertex::compare(const Vertex &e) const {
    if (this->get_label().length() < e.get_label().length()) {
        return -1;
    }

    if (this->get_label().length() > e.get_label().length()) {
        return 1;
    }

    return this->get_index() - e.get_index();
}

std::string Vertex::get_label() const {
    return this->label;
}

int Vertex::get_index() const {
    return this->index;
}

void Vertex::calculate_index() {
    int length = acid::acid_base_length;
    int power_val = 1;

    for (int i = 0; i < this->get_label().length(); ++i) {
        this->index += acid::get_base_value((acid::bases) this->get_label()[i]) * power_val;
        power_val *= length;
    }
}