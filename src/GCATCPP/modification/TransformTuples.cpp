#include <utility>
#include <regex>
#include <map>
#include <string>

//
// Created by martins on 18.06.19.
//

#include "TransformTuples.h"
#include "../helper/ErrorManager.h"
#include "../codes/AbstractCode.h"


TransformTuples::TransformTuples(const std::string &from_rule, const std::string &to_rule) {
    std::string uniqu_from;
    for (int i = 0; i < from_rule.length(); ++i) {
        auto letter = from_rule.substr(i, 1);
        if (uniqu_from.find(letter) != std::string::npos) {
            this->add_error_msg(
                    "Each symbol in the FROM string must be uniqu!." + letter + " appears twice in: " + from_rule);
            this->has_error = true;
            this->rule_set = TransformTuples::transformation_by_name("");;
            return;
        }

        uniqu_from += letter;
    }

    if (from_rule.length() != to_rule.length()) {
        this->add_error_msg("The FROM string and the TO string must have the same length!.");
        this->has_error = true;
        this->rule_set = TransformTuples::transformation_by_name("");;
        return;
    }

    this->rule_set = {uniqu_from, to_rule};
}


TransformTuples::TransformTuples(const std::string &name, acid::acids acid) {
    this->rule_set = TransformTuples::transformation_by_name(name, acid);
    if (name != I && this->rule_set[0].length() == 0) {
        this->add_error_msg("The name could not be found please check the documentation for mor info!");
        this->has_error = true;
    }
}


std::vector<std::string> TransformTuples::modify(AbstractCode *code) {
    if (this->has_error) {
        this->add_error_msg("Error appeared! Something must be rong with your transformation rules!");
        return code->as_vector();
    }

    auto code_vec = code->as_vector();
    for (auto &word : code_vec) {
        this->replacements = {};
        for (size_t i = 0; i < this->rule_set[0].length(); ++i) {
            this->find_replacements(word, this->rule_set[0].at(i), this->rule_set[1].at(i));
        }

        transform_word(word);
    }

    return code_vec;
}

std::string TransformTuples::modify_word(std::string word) {
    if (this->has_error) {
        this->add_error_msg("Error appeared! Something must be rong with your transformation rules!");
        return word;
    }

    this->replacements = {};

    for (size_t i = 0; i < this->rule_set[0].length(); ++i) {
        this->find_replacements(word, this->rule_set[0].at(i), this->rule_set[1].at(i));
    }

    transform_word(word);

    return word;
}

void TransformTuples::transform_word(std::string &word) {
    for (auto &rule : this->replacements) {
        word = word.replace(rule.first, 1, std::string(1, rule.second));
    }
}


void TransformTuples::find_replacements(const std::string &word, char from, char to) {

    std::string fromStr;
    fromStr += from;
    std::regex r(fromStr);

    for (std::sregex_iterator ri = std::sregex_iterator(word.begin(), word.end(), r);
         ri != std::sregex_iterator();
         ++ri) {
        std::smatch sm = *ri;
        this->replacements.insert(std::pair<size_t, char>(sm.position(), to));
    }
}

TransformTuples
TransformTuples::find_transformation_from_sequences(const std::string &seq_1, const std::string &seq_2) {
    err::ErrorManager errorManager;
    std::vector<std::string> rule_set = {"", ""};

    if (seq_1.length() != seq_2.length()) {
        errorManager.add_error_msg("To find a transformation, both Sequences must have the same length!");
        TransformTuples t_return("", "");
        t_return.has_error = true;
        return t_return;
    }

    for (size_t i = 0; i < seq_1.length(); ++i) {
        char from = seq_1.at(i);
        char to = seq_2.at(i);

        size_t pos = rule_set[0].find(from);

        if (pos == std::string::npos) {
            rule_set[0] += from;
            rule_set[1] += to;
        } else if (rule_set[1].at(pos) != to) {
            std::string alternative_to = std::string(1, rule_set[1].at(pos));
            errorManager.add_error_msg(
                    std::string(1, from) + " has 2 different mappings. [ " + alternative_to + ", " + std::string(1, to) + " ]");
            TransformTuples t_return("", "");
            t_return.has_error = true;
            return t_return;
        }
    }

    TransformTuples t_return(rule_set[0], rule_set[1]);
    return t_return;
}

bool TransformTuples::compare_to(const TransformTuples &c2, size_t compare_type) const {
    auto set_1 = this->rule_set;
    auto set_2 = c2.rule_set;
    if (this->has_error || c2.has_error) {
        return false;
    }

    if ((compare_type & COMPARE_E) > 0 && set_1[0].length() == set_2[0].length()) {
        compare_type = COMPARE_E;
    } else if ((compare_type & COMPARE_L) > 0 && set_1[0].length() < set_2[0].length()) {
        compare_type = COMPARE_L;
    } else if ((compare_type & COMPARE_G) > 0 && set_1[0].length() > set_2[0].length()) {
        compare_type = COMPARE_L;
        set_2 = this->rule_set;
        set_1 = c2.rule_set;
    } else {
        return false;
    }

    for (size_t i = 0; i < set_1[0].length(); ++i) {
        size_t idx_2 = set_2[0].find(set_1[0].at(i));
        if (idx_2 == std::string::npos) {
            return false;
        }

        if (set_1[1].at(i) != set_2[1].at(idx_2)) {
            return false;
        }
    }

    return true;
}

bool operator==(const TransformTuples &c1, const TransformTuples &c2) {
    return c1.compare_to(c2, COMPARE_E);
}

bool operator!=(const TransformTuples &c1, const TransformTuples &c2) {
    return !(c1 == c2);
}

bool operator>(const TransformTuples &c1, const TransformTuples &c2) {
    return c1.compare_to(c2, COMPARE_G);
}

bool operator>=(const TransformTuples &c1, const TransformTuples &c2) {
    return c1.compare_to(c2, COMPARE_GE);
}

bool operator<(const TransformTuples &c1, const TransformTuples &c2) {
    return c1.compare_to(c2, COMPARE_L);
}

bool operator<=(const TransformTuples &c1, const TransformTuples &c2) {
    return c1.compare_to(c2, COMPARE_LE);
}
