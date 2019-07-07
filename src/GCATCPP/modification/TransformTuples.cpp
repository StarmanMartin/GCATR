#include <utility>
#include <regex>
#include <map>
#include <string>

//
// Created by martins on 18.06.19.
//

#include "TransformTuples.h"
#include "../codes/AbstractCode.h"



TransformTuples::TransformTuples(const std::string &from_rule, const std::string &to_rule) {
    this->rule_set = {};
    if(from_rule.length() != to_rule.length()) {
        return;
    }

    for(size_t i = 0; i < from_rule.length(); i++) {
        std::string new_rule = "";
        new_rule += from_rule.at(i);
        new_rule += to_rule.at(i);
        rule_set.emplace_back(new_rule);
    }
}



TransformTuples::TransformTuples(const std::string &name, acid::acids acid) {
    this->rule_set = TransformTuples::transformation_by_name(name, acid);
}


std::vector<std::string> TransformTuples::modify(AbstractCode *code) {


    auto code_vec = code->as_vector();
    for (auto &word : code_vec) {
        this->replacements = {};
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
        char a[] = {rule.second};
        std::string replacement(a);
        word = word.replace(rule.first, 1, replacement);
    }
}


void TransformTuples::find_replacements(const std::string &word, const std::string &rule) {

    for (size_t i = 1; i < rule.length(); ++i) {
        std::string from;
        char to;
        from += rule.at(i - 1);
        to = rule.at(i);
        std::regex r(from);

        for(std::sregex_iterator ri = std::sregex_iterator(word.begin(), word.end(), r);
            ri != std::sregex_iterator();
            ++ri ) {
            std::smatch sm = *ri;
            this->replacements.insert(std::pair<size_t, char>(sm.position(), to));
        }
    }
}