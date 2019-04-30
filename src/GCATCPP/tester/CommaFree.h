//
// Created by Martin on 12.07.2018.
//

#ifndef GCATCPP_COMMAFREE_H
#define GCATCPP_COMMAFREE_H

#include "AbstractTester.h"

class CommaFree : public AbstractTester {
public:
    virtual bool test(AbstractCode *code);

protected:
    virtual bool is_comma_free(AbstractCode *code);

    bool rec_is_comma_free
            (AbstractCode *code,
                         std::vector<unsigned int> chained_indexes,
                         std::string current_substring,
                         unsigned int current_word_pos);
};


#endif //GCATCPP_COMMAFREE_H
