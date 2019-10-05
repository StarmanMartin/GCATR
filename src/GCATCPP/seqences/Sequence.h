//
// Created by martins on 05.10.19.
//

#ifndef GCATCPP_SEQUENCE_H
#define GCATCPP_SEQUENCE_H

#include <map>

#include "../codes/Acid.h"
#include "../codes/Alphabet.h"

class Sequence {
public:
    Sequence(const std::string & seq, size_t tuple_length);
    bool test_seq();


    std::map<std::string, size_t> get_tuple_count() const;
    size_t get_number_tuples() const;
    std::string get_alphabet() const;
private:
    std::string seq;
    size_t tuple_length;
    acid::acids acid;
    bool is_seq;
    Alphabet alphabet;
    std::map<std::string, size_t> word_count;
    size_t all_words;
    unsigned long seq_length;
};


#endif //GCATCPP_SEQUENCE_H
