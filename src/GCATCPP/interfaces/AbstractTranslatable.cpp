//
// Created by martins on 17.10.19.
//

#include <algorithm>
#include <set>
#include "AbstractTranslatable.h"
#include "../geneticCode/CodonTranslTables.h"
#include "AbstractTupleContainer.h"


void AbstractTranslatable::setTranslTableByIdx(int idx, int forWordLength) {
   this->transl_table_idx[forWordLength] = idx;
}

void AbstractTranslatable::setTranslTableByName(const std::string &name, int forWordLength) {
   if (forWordLength ==  3) {
            this->transl_table_idx[forWordLength] = gen_codes::CodonTranslTables::getInstance().getIdxByName(name);
    }

}

void AbstractTranslatable::setTranslTableToStandardCode(int forWordLength) {
    this->transl_table_idx[forWordLength] = 1;
}


void AbstractTranslatable::init_trans_table(const std::vector<int>& word_length) {
    if (this->transl_table_idx.empty()) {
        for (auto wl : word_length) {
            this->setTranslTableToStandardCode(wl);
        }
    }
}

std::vector<std::string> AbstractTranslatable::_get_amino_acids(AbstractTupleContainer* self) {
    std::vector<std::string> set_acids;

    this->init_trans_table(self->get_word_length());
    std::map<int, std::vector<std::string>> translTables;
    for (const std::string &codon : self->get_nucleotide_tuples()) {
        auto wordLength = (int) codon.length();
        if (!translTables.count(wordLength)) {
            translTables[wordLength] = this->construct_transl_table(wordLength, self->get_acid());
        }

        auto it = std::find(translTables[wordLength].begin(), translTables[wordLength].end(), codon);
        if (it != translTables[wordLength].end()) {
            it++;
            set_acids.push_back(*it);
        } else
            set_acids.push_back(codon);
    }

    return set_acids;
}

std::vector<std::string> AbstractTranslatable::_get_a_set_amino_acids(AbstractTupleContainer* self) {
    auto vec_acids = this->_get_amino_acids(self);

    std::set<std::string> set_acids(vec_acids.begin(), vec_acids.end());
    vec_acids.clear();
    std::copy(set_acids.begin(), set_acids.end(), std::back_inserter(vec_acids));

    return vec_acids;
}

std::vector<std::string> AbstractTranslatable::construct_transl_table(int wordLength, acid::acids acid_type) const {
    if (!this->transl_table_idx.count(wordLength)) {
        return std::vector<std::string>();
    }

    int translCodeIdx = this->transl_table_idx.at(wordLength);

    if(wordLength == 3) {
        return gen_codes::CodonTranslTables::getInstance().getCodeByIndex(translCodeIdx, acid_type);
    } else {
        return std::vector<std::string>();
    }
}