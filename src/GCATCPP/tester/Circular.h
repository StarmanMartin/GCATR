//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_CIRCULAR_H
#define GCATCPP_CIRCULAR_H

#include "AbstractTester.h"

class Circular : public AbstractTester {
public:
    bool test(std::shared_ptr<AbstractGenCode> code);

private:
    std::vector<std::vector<unsigned int> > circle;

    virtual void add_circle(std::vector<unsigned int>);

    bool is_circular(std::shared_ptr<AbstractGenCode> code);

    bool rec_is_circular(std::shared_ptr<AbstractGenCode> code,
                         std::vector<unsigned int> chained_indexes,
                         std::string current_substring,
                         unsigned int current_word_pos);
};


#endif //GCATCPP_CIRCULAR_H
