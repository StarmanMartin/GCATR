//
// Created by mstar on 19.10.2020.
//

#include "TesseraTable.h"
#include "../modification/TransformTuples.h"
#include "TesseraCode.h"

#include <algorithm>
#include <sstream>

TesseraTable::TesseraTable(const std::vector<std::vector<std::size_t>> &tableStructure, acid::acids acid) {
    this->acid = acid;
    this->reset_fragmet_order();
    this->setTableStructure(tableStructure);
    this->get_dinucleotide_classes();
}

TesseraTable::TesseraTable(acid::acids acid) : acid(acid) {
    this->tableValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    this->fragmentValues = {0, 0, 0, 0};
    this->reset_fragmet_order();
    this->get_dinucleotide_classes();
}

TesseraTable::TesseraTable(std::shared_ptr<TesseraCode> tessCode) {
    this->acid = tessCode->get_acid();

    this->tableValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    this->fragmentValues = {0, 0, 0, 0};

    this->reset_fragmet_order();

    if (!tessCode->test_code() || !tessCode->is_circular()) {
        this->get_dinucleotide_classes();
        return;
    }

    auto order_map = this->generate_dinucleotide_order_map();

    auto words = tessCode->as_unsorted_vector();
    std::map<std::string, size_t> counter = {{"Id", 12 * 6},
                                             {"SW", 12 * 6},
                                             {"KM", 12 * 6},
                                             {"YR", 12 * 6}};

    for (const auto &c: words) {
        auto t1 = TransformTuples::find_transformation_from_sequences(c.substr(0, 1), c.substr(1, 1));
        auto t1Name = t1.getKleinFourTransformationName(tessCode->get_acid());
        size_t idx = this->fragments.at(t1Name);
        this->fragmentValues[idx] += 1;

        auto t2 = TransformTuples::find_transformation_from_sequences(c.substr(1, 1), c.substr(2, 1));
        auto t2Name = t2.getKleinFourTransformationName(tessCode->get_acid());
        auto idx_2 = this->fragments.at(t2Name);
        if (idx < idx_2) {
            idx_2--;
        }
        this->tableValues[idx * 3 + idx_2] += 1;

        order_map[c.substr(0, 2)] = order_map[c.substr(2, 2)] - counter[t1Name];
        counter[t1Name] /= 2;
    }

    this->generate_classes_order_from_map(order_map);
}

void TesseraTable::setTableStructure(const std::vector<std::vector<std::size_t>> &tableStructure) {
    this->tableValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    this->fragmentValues = {0, 0, 0, 0};

    size_t row_sep = 0;
    for (auto &r1 : tableStructure) {
        for (size_t i = 0; i < 3; ++i) {
            this->tableValues[(row_sep * 3) + i] = r1[i];
            this->fragmentValues[row_sep] += r1[i];
        }

        row_sep++;
    }

    if (!this->testTable()) {
        this->tableValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        this->fragmentValues = {0, 0, 0, 0};
    }
}

void TesseraTable::setFragments(std::vector<std::string> inFragments) {

    if(this->fragments.empty()) {
        this->reset_fragmet_order();
    }

    this->resetDinOrderByFragmentStructure(inFragments);

    for (const auto &w : {"Id", "SW", "KM", "YR"}) {
        auto it = std::find(inFragments.begin(), inFragments.end(), w);
        if (it == inFragments.end()) {
            std::cout << "The function setFragments needs all fragments Id, SW, KM, YR" << std::endl;
            this->reset_fragmet_order();
            return;
        }

        int index = std::distance(inFragments.begin(), it);
        this->fragments[w] = index;
    }
}

std::string TesseraTable::printableTable() const {
    std::stringstream ss;
    ss << "|";
    for (size_t i = 0; i < 3; ++i) {
        if (i == 0)
            ss << this->fragmentValues[0] << "|";
        ss << this->tableValues[i] << "|";
    }

    ss << "\n|";

    for (size_t i = 0; i < 3; ++i) {
        if (i == 1)
            ss << this->fragmentValues[1] << "|";
        ss << this->tableValues[3 + i] << "|";
    }

    ss << "\n|";

    for (size_t i = 0; i < 3; ++i) {
        if (i == 2)
            ss << this->fragmentValues[2] << "|";
        ss << this->tableValues[6 + i] << "|";
    }

    ss << "\n|";

    for (size_t i = 0; i < 3; ++i) {
        ss << this->tableValues[9 + i] << "|";
    }

    ss << this->fragmentValues[3] << "|";

    return ss.str();

}

void TesseraTable::reset_fragmet_order() {
    this->resetDinOrderByFragmentStructure({"ID","SW","KM","YR"});
    this->_reset_fragmet_order();
}


void TesseraTable::resetDinOrderByFragmentStructure(const std::vector<std::string> & inFrag) {
    if(this->din_classes.empty()) {
        return;
    }

    std::vector<bool> done = {true,true,true,true};
    for(size_t i = 0 ; i < inFrag.size(); ++i) {
        done[i] = false;
        if(!done[this->fragments[inFrag[i]]]) {
            auto temp = this->din_classes[this->fragments[inFrag[i]]];
            this->din_classes[this->fragments[inFrag[i]]] = this->din_classes[i];
            this->din_classes[i] = temp;
        }
    }
}

void TesseraTable::_reset_fragmet_order() {
    this->fragments.clear();
    this->fragments.insert(std::pair<std::string, size_t>("Id", 0));
    this->fragments.insert(std::pair<std::string, size_t>("SW", 1));
    this->fragments.insert(std::pair<std::string, size_t>("KM", 2));
    this->fragments.insert(std::pair<std::string, size_t>("YR", 3));
}



void TesseraTable::generate_classes_order_from_map(std::map<std::string, size_t> din_map) {
    std::vector<std::vector<std::string>> classes(4);

    if (this->fragments.empty()) {
        this->reset_fragmet_order();
    }

    std::vector<std::pair<std::string, size_t>> vec;

    // copy key-value pairs from the map to the vector
    std::copy(din_map.begin(),
              din_map.end(),
              std::back_inserter<std::vector<std::pair<std::string, size_t>>>(vec));
    // Comparator function to sort pairs
    // according to second value
    std::sort(vec.begin(), vec.end(), [](std::pair<std::string, size_t> &a, std::pair<std::string, size_t> &b) {
        return a.second < b.second;
    });

    auto alphabet = acid::acid_as_alphabet(acid);

    for (const auto &c : vec) {
        auto t1 = TransformTuples::find_transformation_from_sequences(c.first.substr(0, 1), c.first.substr(1, 1));
        auto t1Name = t1.getKleinFourTransformationName(acid);
        classes[this->fragments[t1Name]].push_back(c.first);
    }

    this->din_classes = classes;
}

std::vector<std::vector<std::string>> TesseraTable::get_dinucleotide_classes() {
    if (this->din_classes.empty()) {
        this->din_classes = this->generate_dinucleotide_classes();
    }

    return this->din_classes;
}

std::vector<std::vector<std::string>> TesseraTable::generate_dinucleotide_classes() {
    std::vector<std::vector<std::string>> classes(4);

    if (this->fragments.empty()) {
        this->reset_fragmet_order();
    }

    auto alphabet = acid::acid_as_alphabet(acid);

    for (const auto &trans : this->fragments) {
        TransformTuples t(trans.first, acid);
        for (std::size_t i = 0; i < alphabet.size(); ++i) {
            std::string letter = alphabet.substr(i, 1);
            std::string new_letter = t.modify_word(letter);
            classes[trans.second].push_back(letter + new_letter);
        }
    }

    return classes;
}

std::map<std::string, size_t> TesseraTable::generate_dinucleotide_order_map() {
    std::map<std::string, size_t> classes;

    if (this->fragments.empty()) {
        this->reset_fragmet_order();
    }

    auto alphabet = acid::acid_as_alphabet(acid);

    for (const auto &trans : this->fragments) {
        TransformTuples t(trans.first, this->acid);
        for (std::size_t i = 0; i < alphabet.size(); ++i) {
            std::string letter = alphabet.substr(i, 1);
            std::string new_letter = t.modify_word(letter);
            classes.insert(std::pair<std::string, size_t>(letter + new_letter, 12 * 16));
        }
    }

    return classes;
}

bool TesseraTable::testTable() {
    for (size_t r_idx = 0; r_idx < 4; r_idx++) {
        for (size_t c_idx = r_idx; c_idx < 3; c_idx++) {

            size_t idx = (r_idx * 3) + c_idx;

            if (this->tableValues[idx] > 2) {
                return false;
            }

            size_t idx_complement = (c_idx + 1) * 3 + r_idx;

            if (this->tableValues[idx_complement] > 2 &&
                this->tableValues[idx_complement] + this->tableValues[idx] > 2) {
                return false;
            }
        }
    }

    return true;
}

std::vector<std::string> TesseraTable::generateCode() const {
    std::vector<std::string> code(
            this->fragmentValues[0] + this->fragmentValues[1] + this->fragmentValues[2] + this->fragmentValues[3]);

    std::vector<std::pair<std::string, size_t>> vec;

    // copy key-value pairs from the map to the vector
    std::copy(this->fragments.begin(),
              this->fragments.end(),
              std::back_inserter<std::vector<std::pair<std::string, size_t>>>(vec));
    // Comparator function to sort pairs
    // according to second value
    std::sort(vec.begin(), vec.end(), [](std::pair<std::string, size_t> &a, std::pair<std::string, size_t> &b) {
        return a.second < b.second;
    });

    size_t word_idx = 0;

    for (size_t idx1 = 0; idx1 < vec.size(); ++idx1) {
        TransformTuples t1(vec[idx1].first, this->acid);
        for (size_t idx2 = idx1; idx2 < vec.size() - 1; ++idx2) {
            TransformTuples t2(vec[idx2 + 1].first, this->acid);

            if (this->tableValues[idx1 * 3 + idx2] >= 1) {
                std::string din1 = "A" + t1.modify_word("A");
                std::string din2 = t2.modify_word(din1);
                // Check if element 22 exists in vector
                if (this->indexOfDin(idx1, din1) > this->indexOfDin(idx1, din2)) {
                    code[word_idx] = din2 + din1;
                } else {
                    code[word_idx] = din1 + din2;
                }

                word_idx++;


            }

            if (this->tableValues[(idx2 + 1) * 3 + idx1] >= 1) {
                TransformTuples t3(TesseraTable::nextTransformation(vec[idx1].first, vec[idx2 + 1].first), this->acid);
                std::string letter = t3.modify_word("A");
                std::string din1 = letter + t2.modify_word(letter);
                std::string din2 = t2.modify_word(t1.modify_word(din1));
                // Check if element 22 exists in vector
                if (this->indexOfDin(idx2 + 1, din1) > this->indexOfDin(idx2 + 1, din2)) {
                    code[word_idx] = din2 + din1;
                } else {
                    code[word_idx] = din1 + din2;
                }

                word_idx++;
            }

            if (this->tableValues[idx1 * 3 + idx2] == 2) {
                TransformTuples t3(TesseraTable::nextTransformation(vec[idx1].first, vec[idx2 + 1].first), this->acid);
                std::string letter = t3.modify_word("A");
                std::string din1 = letter + t1.modify_word(letter);
                std::string din2 = t2.modify_word(din1);
                // Check if element 22 exists in vector
                if (this->indexOfDin(idx1, din1) > this->indexOfDin(idx1, din2)) {
                    code[word_idx] = din2 + din1;
                } else {
                    code[word_idx] = din1 + din2;
                }

                word_idx++;

            }

            if (this->tableValues[(idx2 + 1) * 3 + idx1] == 2) {
                std::string letter = "A";
                std::string din1 = letter + t2.modify_word(letter);
                std::string din2 = t2.modify_word(t1.modify_word(din1));
                // Check if element 22 exists in vector
                if (this->indexOfDin(idx2 + 1, din1) > this->indexOfDin(idx2 + 1, din2)) {
                    code[word_idx] = din2 + din1;
                } else {
                    code[word_idx] = din1 + din2;
                }

                word_idx++;
            }
        }
    }

    return code;
}

std::string TesseraTable::nextTransformation(const std::string &a, const std::string &b) {
    if ("SW" != a && "SW" != b) {
        return "SW";
    }
    if ("KM" != a && "KM" != b) {
        return "KM";
    }

    return "YR";
}

int TesseraTable::indexOfDin(size_t idx, const std::string &obj) const {
    // Check if element 22 exists in vector
    auto it = std::find(this->din_classes[idx].begin(), this->din_classes[idx].end(), obj);
    if (it == this->din_classes[idx].end())
        std::cout << "Element Not Found" << std::endl;

    // Get index of element from iterator
    return std::distance(this->din_classes[idx].begin(), it);
}
