//
// Created by martins on 05.10.19.
//

#ifndef GCATCPP_SEQUENCE_H
#define GCATCPP_SEQUENCE_H

#include <map>

#include "../codes/Acid.h"
#include "../codes/Alphabet.h"
#include "../helper/AbstractErrorManager.h"
#include "../interfaces/AbstractTupleContainer.h"
#include "../interfaces/AbstractTranslatable.h"

class Sequence: public err::AbstractErrorManager, public AbstractTupleContainer, public AbstractTranslatable {
public:
    Sequence(const std::string & seq, size_t tuple_length);
    bool test_seq();


    std::map<std::string, int> get_tuple_count() const;
    size_t get_number_tuples() const;
    std::string get_alphabet() const;

    std::vector<std::string> get_tuples() override;
    std::vector<std::string> get_nucleotide_tuples() override;

    std::vector<std::string> get_amino_acids() override ;
    std::vector<std::string> get_a_set_amino_acids() override;

    bool is_translatable();
    acid::acids get_acid() override;
    std::vector<int> get_word_length() override;
private:
    std::string seq;
    size_t tuple_length;
    acid::acids acid;
    bool is_seq;
    Alphabet alphabet;
    std::map<std::string, int> word_count;
    size_t all_words;
    unsigned long seq_length;
    std::vector<std::string> code_vec;
};


#endif //GCATCPP_SEQUENCE_H
