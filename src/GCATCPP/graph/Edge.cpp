//
// Created by Martin on 18.07.2018.
//

#include <math.h>
#include <sstream>
#include <stdlib.h>

#include "Edge.h"
#include "../codes/Acid.h"
#include "Vertex.h"

#define PLACEHOLER '#'

using namespace graph;

Edge::Edge(std::shared_ptr<Vertex> from, std::shared_ptr<Vertex> to) : from(from), to(to), index(0) {
    this->calculate_index();
}

int Edge::compare(const Edge &v) const {
    return this->get_index() - v.get_index();
}


int Edge::get_index() const {
    return this->index;
}


std::string Edge::get_label() const {
    return this->from->get_label() + " -> " + this->to->get_label();
}

std::shared_ptr<Vertex> Edge::get_from() const {
    return this->from;
}

std::shared_ptr<Vertex> Edge::get_to() const {
    return this->to;
}

void Edge::calculate_index() {
    std::stringstream filler;
    int diff = abs((signed) this->from->get_label().length() - (signed) this->to->get_label().length());
    for (int i = 0; i < diff; ++i) { filler << PLACEHOLER; }

    std::string label;
    if (this->from->get_label().length() > this->to->get_label().length()) {
        label = this->from->get_label() + filler.str() + this->to->get_label();
    } else {
        label = filler.str() + this->from->get_label() + this->to->get_label();
    }

    int length = acid::acid_base_length + 1;
    int power_val = 1;

    for (int i = 0; i < label.length(); ++i) {
        if (label[i] != PLACEHOLER) {
            this->index += acid::get_base_value((acid::bases) label[i]) * power_val;
        } else {
            this->index += acid::acid_base_length * power_val;
        }
        power_val *= length;
    }
}