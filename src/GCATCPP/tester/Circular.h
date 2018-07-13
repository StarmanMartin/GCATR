//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_CIRCULAR_H
#define GCATCPP_CIRCULAR_H

#include "AbstractTester.h"

class Circular : public AbstractTester {
public:
    virtual bool test(AbstractGenCode *code);

private:
    std::vector<std::vector<unsigned int> > circle;

    void add_circle(std::vector<unsigned int>);

    bool is_circular(AbstractGenCode *code);

    bool rec_is_circular(AbstractGenCode *code,
                         std::vector<unsigned int> chained_indexes,
                         std::string current_substring,
                         unsigned int current_word_pos);
};


#endif //GCATCPP_CIRCULAR_H
