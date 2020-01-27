//
// Created by martins on 17.10.19.
//

#ifndef GCATCPP_ABSTRACTTRANSLATABLE_H
#define GCATCPP_ABSTRACTTRANSLATABLE_H


#include <string>
#include <map>
#include <vector>
#include "../codes/Acid.h"

class AbstractTupleContainer;

class AbstractTranslatable {
protected:
    std::map<int, int> transl_table_idx;
    void init_trans_table(const std::vector<int>& word_length);
    std::vector<std::string> _get_amino_acids(AbstractTupleContainer* self);
    std::vector<std::string> _get_a_set_amino_acids(AbstractTupleContainer* self);

public:
    virtual void setTranslTableByIdx(int idx, int forWordLength);
    virtual void setTranslTableByName(const std::string &name, int forWordLength);
    virtual void setTranslTableToStandardCode(int forWordLength);
    virtual std::vector<std::string> get_amino_acids() = 0;
    virtual std::vector<std::string> get_a_set_amino_acids() = 0;

    virtual std::vector<std::string> construct_transl_table(int wordLength, acid::acids acid_type) const;
};


#endif //GCATCPP_ABSTRACTTRANSLATABLE_H
