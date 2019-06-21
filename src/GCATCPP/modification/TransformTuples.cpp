#include <utility>
#include <regex>
#include <map>
#include <string>

//
// Created by martins on 18.06.19.
//

#include "TransformTuples.h"
#include "../codes/AbstractCode.h"


TransformTuples::TransformTuples(std::vector<std::string> rule_set) : rule_set(std::move(rule_set)),
                                                                      AbstractModifier() {

}


std::vector<std::string> TransformTuples::modify(AbstractCode *code) {
    this->replacements = {};

    auto code_vec = code->as_vector();
    for (auto &word : code_vec) {
        for (const auto &rule : this->rule_set) {
            this->find_replacements(word, rule);
        }

        transform_word(word);
    }

    return code_vec;
}

std::string TransformTuples::modify_word(std::string word) {
    this->replacements = {};

    for (const auto &rule : this->rule_set) {
        this->find_replacements(word, rule);
    }

    transform_word(word);

    return word;
}

void TransformTuples::transform_word(std::string &word) {
    for(auto &rule : this->replacements) {
        word.replace(rule.first, 1, reinterpret_cast<const char *>(rule.second));
    }
}


void TransformTuples::find_replacements(const std::string &word, const std::string &rule) {

    std::smatch sm;


    for (size_t i = 1; i < rule.length(); ++i) {
        std::string from;
        char to;
        from += rule.at(i - 1);
        to = rule.at(i - 1);
        std::regex r(from);
        if (regex_search(word, sm, r)) {
            for (unsigned m_i = 0; m_i < sm.size(); ++m_i) {
                this->replacements.insert(std::pair<size_t, char>(sm.position(m_i), to));
            }
        }
    }
}
