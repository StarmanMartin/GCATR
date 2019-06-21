//
// Created by martins on 18.06.19.
//

#ifndef GCATCPP_TRANSFORMTUPLES_H
#define GCATCPP_TRANSFORMTUPLES_H


#include "AbstractModifier.h"

class TransformTuples: public AbstractModifier {
public:
    explicit TransformTuples(std::vector<std::string> rule_set);

    std::vector<std::string> modify(AbstractCode* code) override;
    std::string modify_word(std::string word) override;

private:
    std::vector<std::string> rule_set;
    std::map<size_t, char> replacements;
    void transform_word(std::string& word);
    void find_replacements(const std::string &word, const std::string &rule);
};


#endif //GCATCPP_TRANSFORMTUPLES_H
