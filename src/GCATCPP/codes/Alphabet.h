//
// Created by Martin on 2/16/2019.
//

#ifndef GCATCPP_ALPHABET_H
#define GCATCPP_ALPHABET_H

#include <set>
#include <map>
#include "Acid.h"

class Alphabet {

public:
    explicit Alphabet();

    explicit Alphabet(const std::string &);

    virtual std::string as_string() const;
    void set_alphabet(const std::string &);
    virtual int get_letter_value(const char &);

private:

    std::set<char> alphabet;
    std::map<char, size_t> alphabet_values;

    acid::acids acid;
};


#endif //GCATCPP_ALPHABET_H
