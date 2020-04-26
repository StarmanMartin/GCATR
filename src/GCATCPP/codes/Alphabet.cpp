//
// Created by Martin on 2/16/2019.
//

#include "Alphabet.h"

Alphabet::Alphabet(const std::string &code) {
    this->acid = acid::acids::NONE;
    this->set_alphabet(code);
}

Alphabet::Alphabet() {
    this->acid = acid::acids::NONE;
    this->alphabet.clear();
    this->alphabet_values.clear();
}

void Alphabet::set_alphabet(const std::string &new_alphabet) {

    this->alphabet.clear();
    this->alphabet_values.clear();

    this->acid = acid::check_acid_type(new_alphabet);
    if(this->acid != acid::acids::NONE) {
        return;
    }

    for (auto &c : new_alphabet) {
        this->alphabet.insert(c);
    }

    auto alphabet_it = this->alphabet.begin();
    for (size_t i = 0; i < this->alphabet.size(); ++i) {
        this->alphabet_values.insert(std::pair<char, int>(*alphabet_it, (int) i));
        alphabet_it++;
    }
}

std::string Alphabet::as_string() const {

    if(this->acid != acid::acids::NONE) {
        return acid::acid_as_alphabet(this->acid);
    }

    std::string result;
    for (char const &s : this->alphabet) { result += s; }

    return result;
}

int Alphabet::get_letter_value(const char &c) {

    if(this->acid != acid::acids::NONE) {
        return acid::get_base_value((acid::bases) c);
    }

    auto find_res = this->alphabet_values.find(c);
    if (find_res != alphabet_values.end()) {
        return (int) find_res->second;
    }

    return -1;
}