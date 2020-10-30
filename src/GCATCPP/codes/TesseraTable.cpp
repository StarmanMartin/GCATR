//
// Created by mstar on 19.10.2020.
//

#include "TesseraTable.h"
#include "../modification/TransformTuples.h"
#include "TesseraCode.h"

#include <bits/stdc++.h>
#include <algorithm>
#include <sstream>
#include <cmath>

TesseraTable::TesseraTable(const std::vector<std::vector<std::size_t>> &tableStructure, acid::acids acid) {
    this->acid = acid;
    this->reset_fragmet_order();
    this->setTableStructure(tableStructure);
    this->getDinucleotideClasses();
}

TesseraTable::TesseraTable(acid::acids acid) : acid(acid) {
    this->setTableStructure({{0, 0, 0},
                             {0, 0, 0},
                             {0, 0, 0}});
    this->reset_fragmet_order();
    this->getDinucleotideClasses();
}

TesseraTable::TesseraTable(std::shared_ptr<TesseraCode> tessCode) {
    this->acid = tessCode->get_acid();

    this->reset_fragmet_order();

    if (!tessCode->test_code() || !tessCode->is_circular()) {
        this->getDinucleotideClasses();
        return;
    }

    auto order_map = this->generate_dinucleotide_order_map();

    auto words = tessCode->as_unsorted_vector();
    std::map<std::string, size_t> counter = {{"Id", 12 * 6},
                                             {"SW", 12 * 6},
                                             {"KM", 12 * 6},
                                             {"YR", 12 * 6}};

    std::vector<std::vector<std::size_t>> temp_table_values = {{0, 0, 0},
                                                               {0, 0, 0},
                                                               {0, 0, 0},
                                                               {0, 0, 0}};

    for (const auto &c: words) {
        auto t1 = TransformTuples::find_transformation_from_sequences(c.substr(0, 1), c.substr(1, 1));
        auto t1Name = t1.getKleinFourTransformationName(tessCode->get_acid());
        size_t idx = this->fragments_pos.at(t1Name);

        auto t2 = TransformTuples::find_transformation_from_sequences(c.substr(1, 1), c.substr(2, 1));
        auto t2Name = t2.getKleinFourTransformationName(tessCode->get_acid());
        auto idx_2 = this->fragments_pos.at(t2Name);
        if (idx < idx_2) {
            idx_2--;
        }

        temp_table_values[idx][idx_2] += 1;

        order_map[c.substr(0, 2)] = order_map[c.substr(2, 2)] - counter[t1Name];
        counter[t1Name] /= 2;
    }

    this->generate_classes_order_from_map(order_map);
    this->setTableStructure(temp_table_values);


}

void TesseraTable::setTableStructure(const std::vector<std::vector<std::size_t>> &tableStructure) {
    this->table_values = {{0, 0, 0, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}};
    size_t row_sep = 0;

    for (auto &r1 : tableStructure) {
        for (size_t i = 0; i < 3; ++i) {
            this->table_values[row_sep][row_sep] += r1[i];
            if (i < row_sep) {
                this->table_values[row_sep][i] = r1[i];
            } else {
                this->table_values[row_sep][i + 1] = r1[i];
            }
        }

        row_sep++;
    }


    if (!this->testTable()) {
        this->table_values = {{0, 0, 0, 0},
                              {0, 0, 0, 0},
                              {0, 0, 0, 0},
                              {0, 0, 0, 0}};
    }
}

void TesseraTable::setFragments(std::vector<std::string> inFragments) {

    if (this->fragments_pos.empty()) {
        this->reset_fragmet_order();
    }

    this->reset_din_order_by_fragment_pos(inFragments);

    for (const auto &w : {"Id", "SW", "KM", "YR"}) {
        auto it = std::find(inFragments.begin(), inFragments.end(), w);
        if (it == inFragments.end()) {
            std::cout << "The function setFragments needs all fragments_pos Id, SW, KM, YR" << std::endl;
            this->reset_fragmet_order();
            return;
        }

        int index = std::distance(inFragments.begin(), it);
        this->fragments_pos[w] = index;
    }
}

std::string TesseraTable::printableTable() const {
    std::stringstream ss;
    ss << "|";
    for (size_t r_i = 0; r_i < 4; ++r_i) {
        for (size_t c_i = 0; c_i < 4; ++c_i) {
            ss << this->table_values[r_i][c_i] << "|";
        }

        if (r_i < 3) {
            ss << "\n" << "|";
        }
    }

    return ss.str();
}

std::vector<std::string> TesseraTable::printableTableR() const {
    std::vector<std::string> res(4);

    for (size_t r_i = 0; r_i < 4; ++r_i) {
        std::stringstream ss;
        ss << "|";
        for (size_t c_i = 0; c_i < 4; ++c_i) {
            ss << this->table_values[r_i][c_i] << "|";
        }

        res[r_i] = ss.str();
    }

    return res;
}

std::vector<std::vector<std::size_t>> TesseraTable::getTable() const {
    return this->table_values;
}


void TesseraTable::reset_fragmet_order() {
    this->reset_din_order_by_fragment_pos({"ID", "SW", "KM", "YR"});
    this->fragments_pos.clear();
    this->fragments_pos.insert(std::pair<std::string, size_t>("Id", 0));
    this->fragments_pos.insert(std::pair<std::string, size_t>("SW", 1));
    this->fragments_pos.insert(std::pair<std::string, size_t>("KM", 2));
    this->fragments_pos.insert(std::pair<std::string, size_t>("YR", 3));
}


void TesseraTable::reset_din_order_by_fragment_pos(const std::vector<std::string> &inFrag) {
    if (this->din_classes.empty()) {
        return;
    }

    std::vector<bool> done = {true, true, true, true};
    for (size_t i = 0; i < inFrag.size(); ++i) {
        done[i] = false;
        if (!done[this->fragments_pos[inFrag[i]]]) {
            auto temp = this->din_classes[this->fragments_pos[inFrag[i]]];
            this->din_classes[this->fragments_pos[inFrag[i]]] = this->din_classes[i];
            this->din_classes[i] = temp;
        }
    }
}


void TesseraTable::generate_classes_order_from_map(std::map<std::string, size_t> din_map) {
    std::vector<std::vector<std::string>> classes(4);

    if (this->fragments_pos.empty()) {
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
        classes[this->fragments_pos[t1Name]].push_back(c.first);
    }

    this->din_classes = classes;
}

std::vector<std::vector<std::string>> TesseraTable::getDinucleotideClasses() {
    if (this->din_classes.empty()) {
        this->din_classes = this->generateDinucleotideClasses();
    }

    return this->din_classes;
}

std::vector<std::vector<std::string>> TesseraTable::generateDinucleotideClasses() {
    std::vector<std::vector<std::string>> classes(4);

    if (this->fragments_pos.empty()) {
        this->reset_fragmet_order();
    }

    auto alphabet = acid::acid_as_alphabet(acid);

    for (const auto &trans : this->fragments_pos) {
        TransformTuples t(trans.first, this->acid);
        for (std::size_t i = 0; i < alphabet.size(); ++i) {
            std::string letter = alphabet.substr(i, 1);
            std::string new_letter = t.modify_word(letter);
            classes[trans.second].push_back(letter + new_letter);
        }
    }

    return classes;
}

bool TesseraTable::testTable() {
    for (size_t r_idx = 0; r_idx < 4; r_idx++) {
        for (size_t c_idx = r_idx + 1; c_idx < 3; c_idx++) {
            if (this->table_values[r_idx][c_idx] > 2 ||
                this->table_values[r_idx][c_idx] + table_values[c_idx][r_idx] > 2) {
                return false;
            }
        }
    }

    return true;
}

std::vector<std::string> TesseraTable::generateCode() const {
    std::vector<std::string> code(
            this->table_values[0][0] + this->table_values[1][1] + this->table_values[2][2] + this->table_values[3][3]);

    std::vector<std::pair<std::string, size_t>> vec;

    // copy key-value pairs from the map to the vector
    std::copy(this->fragments_pos.begin(),
              this->fragments_pos.end(),
              std::back_inserter<std::vector<std::pair<std::string, size_t>>>(vec));
    // Comparator function to sort pairs
    // according to second value
    std::sort(vec.begin(), vec.end(), [](std::pair<std::string, size_t> &a, std::pair<std::string, size_t> &b) {
        return a.second < b.second;
    });

    size_t word_idx = 0;

    for (size_t idx1 = 0; idx1 < vec.size(); ++idx1) {
        TransformTuples t1(vec[idx1].first, this->acid);
        for (size_t idx2 = idx1 + 1; idx2 < vec.size(); ++idx2) {
            TransformTuples t2(vec[idx2].first, this->acid);

            if (this->table_values[idx1][idx2] >= 1) {
                std::string din1 = "A" + t1.modify_word("A");
                std::string din2 = t2.modify_word(din1);
                // Check if element 22 exists in vector
                if (this->index_of_din(idx1, din1) > this->index_of_din(idx1, din2)) {
                    code[word_idx] = din2 + din1;
                } else {
                    code[word_idx] = din1 + din2;
                }

                word_idx++;


            }

            if (this->table_values[idx2][idx1] >= 1) {
                TransformTuples t3(TesseraTable::next_transformation(vec[idx1].first, vec[idx2].first), this->acid);
                std::string letter = t3.modify_word("A");
                std::string din1 = letter + t2.modify_word(letter);
                std::string din2 = t2.modify_word(t1.modify_word(din1));
                // Check if element 22 exists in vector
                if (this->index_of_din(idx2, din1) > this->index_of_din(idx2, din2)) {
                    code[word_idx] = din2 + din1;
                } else {
                    code[word_idx] = din1 + din2;
                }

                word_idx++;
            }

            if (this->table_values[idx1][idx2] == 2) {
                TransformTuples t3(TesseraTable::next_transformation(vec[idx1].first, vec[idx2].first), this->acid);
                std::string letter = t3.modify_word("A");
                std::string din1 = letter + t1.modify_word(letter);
                std::string din2 = t2.modify_word(din1);
                // Check if element 22 exists in vector
                if (this->index_of_din(idx1, din1) > this->index_of_din(idx1, din2)) {
                    code[word_idx] = din2 + din1;
                } else {
                    code[word_idx] = din1 + din2;
                }

                word_idx++;

            }

            if (this->table_values[idx2][idx1] == 2) {
                std::string letter = "A";
                std::string din1 = letter + t2.modify_word(letter);
                std::string din2 = t2.modify_word(t1.modify_word(din1));
                // Check if element 22 exists in vector
                if (this->index_of_din(idx2, din1) > this->index_of_din(idx2, din2)) {
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

std::map<std::string, size_t> TesseraTable::generate_dinucleotide_order_map() {
    std::map<std::string, size_t> classes;

    if (this->fragments_pos.empty()) {
        this->reset_fragmet_order();
    }

    auto alphabet = acid::acid_as_alphabet(acid);

    for (const auto &trans : this->fragments_pos) {
        TransformTuples t(trans.first, this->acid);
        for (std::size_t i = 0; i < alphabet.size(); ++i) {
            std::string letter = alphabet.substr(i, 1);
            std::string new_letter = t.modify_word(letter);
            classes.insert(std::pair<std::string, size_t>(letter + new_letter, 12 * 16));
        }
    }

    return classes;
}

std::string TesseraTable::next_transformation(const std::string &a, const std::string &b) {
    if ("SW" != a && "SW" != b) {
        return "SW";
    }
    if ("KM" != a && "KM" != b) {
        return "KM";
    }

    return "YR";
}

int TesseraTable::index_of_din(size_t idx, const std::string &obj) const {
    // Check if element 22 exists in vector
    auto it = std::find(this->din_classes[idx].begin(), this->din_classes[idx].end(), obj);
    if (it == this->din_classes[idx].end())
        std::cout << "Element Not Found" << std::endl;

    // Get index of element from iterator
    return std::distance(this->din_classes[idx].begin(), it);
}

bool TesseraTable::compare_tables(const TesseraTable &table_1, const TesseraTable &table_2) {
    return table_2.equal(table_1);
}

bool TesseraTable::equal(const TesseraTable &table_2) const {
    return this->printableTable() == table_2.printableTable();
}

size_t TesseraTable::get_value_of_single_row(size_t r_idx) const {
    size_t values = 0;
    size_t factor = 1;
    for (size_t c_idx = 0; c_idx < 4; c_idx++) {
        if (c_idx != r_idx) {
            values += this->table_values[r_idx][c_idx] * factor;
            factor *= 3;
        }
    }

    return values;
}

size_t TesseraTable::get_value_of_table_rows(size_t idx_range, ...) const {
    std::vector<size_t> intpar(idx_range); // Parameterinhalt
    if (idx_range == 0) {
        intpar = {0, 1, 2, 3};
    } else {

        va_list params; // Zugriffshandle für Parameter
        va_start(params, idx_range); // Zugriff vorbereiten
        for (int i = 0; i < idx_range; i++) {
            intpar[i] = va_arg(params, int); // hole den Paramete
        }

        va_end(params); // Zugriff abschließen
    }

    size_t value = 0;

    for (const auto &r_idx : intpar) {
        value += this->get_value_of_single_row(r_idx) * pow(27, 3 - r_idx);
    }

    return value;
}

void TesseraTable::row_swap(size_t a, size_t b) {
    std::vector<size_t> y = {a, b};
    if (a > b) {
        y = {b, a};
    }
    std::vector<size_t> y_e = {0, 1, 2, 3};
    y_e.erase(y_e.begin() + y[1]);
    y_e.erase(y_e.begin() + y[0]);

    iter_swap(this->table_values.begin() + y[1], this->table_values.begin() + y[0]);
    iter_swap(this->table_values[y[1]].begin() + y[1], this->table_values[y[1]].begin() + y[0]);
    iter_swap(this->table_values[y[0]].begin() + y[1], this->table_values[y[0]].begin() + y[0]);

    for (const size_t &idx: y_e) {
        iter_swap(this->table_values[idx].begin() + y[1], this->table_values[idx].begin() + y[0]);
    }
}


void TesseraTable::permutateTableByIdxList(std::vector<std::size_t> perm) {
    std::vector<std::size_t> idx_list = {0, 1, 2, 3};
    for (size_t idx = 0; idx < idx_list.size(); idx++) {
        auto it = std::find(idx_list.begin(), idx_list.end(), idx);
        size_t perm_idx = std::distance(idx_list.begin(), it);
        if (perm_idx != perm[idx]) {
            this->row_swap(perm_idx, perm[idx]);
            iter_swap(idx_list.begin() + perm_idx, idx_list.begin() + perm[idx]);
        }
    }
}

void TesseraTable::permutateTableByIdxList(size_t a, size_t b, size_t c, size_t d) {
    this->permutateTableByIdxList({a, b, c, d});
}

size_t TesseraTable::checkSum() const {
    return this->get_value_of_table_rows(0, 1, 2, 3);
}


void TesseraTable::minValueOrderTable() {
    size_t val = this->checkSum();

    size_t perm_res[4] = {0, 1, 2, 3};
    size_t dest[4];
    std::copy(std::begin(perm_res), std::end(perm_res), std::begin(dest));
    do {
        TesseraTable t_new(*this);
        t_new.permutateTableByIdxList(perm_res[0], perm_res[1], perm_res[2], perm_res[3]);
        size_t new_val = t_new.checkSum();
        if (new_val < val) {
            val = new_val;
            std::copy(std::begin(perm_res), std::end(perm_res), std::begin(dest));
        }
    } while (std::next_permutation(perm_res, perm_res + 4));

    this->permutateTableByIdxList(dest[0], dest[1], dest[2], dest[3]);
}

/*****************************************/
/***    Generate all Tessera Tables    ***/
/*****************************************/

std::vector<std::vector<std::size_t>> TesseraTable::generateFragmentDistribution(size_t codeSize) {
    std::vector<std::vector<std::size_t>> table_of_all_separations;
    codeSize = std::min(std::max(codeSize, (size_t) 1), (size_t) 12);

    size_t first_upper_bound = std::min((size_t) 10, codeSize);

    for (size_t a = 1; a < 1 + std::min((size_t) 6, codeSize); ++a) {
        for (size_t b = std::ceil((float) (codeSize - a) / 3.0); b < 1 + std::min(first_upper_bound - a, a); ++b) {
            for (size_t c = std::ceil((float) (codeSize - a - b) / 2.0); c < 1 + std::min(codeSize - (a + b), b); ++c) {
                table_of_all_separations.push_back({a, b, c, codeSize - a - b - c});
            }
        }
    }


    std::reverse(table_of_all_separations.begin(), table_of_all_separations.end());

    return table_of_all_separations;
}

std::vector<TesseraTable> TesseraTable::generateCDSForFragmentDistribution(std::vector<std::size_t> fd) {
    auto values = TesseraTable::get_all_possible_inner_separations(fd);
    return TesseraTable::assemble_valid_separations(values, fd);
}

std::vector<std::vector<std::vector<std::size_t>>> TesseraTable::get_all_possible_inner_separations(const std::vector<std::size_t> &fd) {
    std::vector<std::vector<std::vector<std::size_t>>> vals;
    for (const auto &m_sep_val: fd) {
        std::vector<std::vector<std::size_t>> inner_vals;
        for (size_t one = 0; one < 3; one++) {
            size_t rest = m_sep_val - one;
            if (rest < 0 || rest > 4) {
                continue;
            }
            for (size_t two = 0; two < 3; two++) {
                size_t three = rest - two;
                if (three < 0 || three > 2) {
                    continue;
                }
                std::vector<size_t> rp = {one, two, three};
                inner_vals.push_back(rp);
            }
        }

        vals.push_back(inner_vals);
    }

    return vals;
}

std::vector<TesseraTable> TesseraTable::assemble_valid_separations(const std::vector<std::vector<std::vector<std::size_t>>> &inner_seps, const std::vector<std::size_t> &main_separations) {
    std::vector<TesseraTable> all_tables;
    for (const auto &first_inner : inner_seps[0]) {
        std::vector<size_t> values = {main_separations[0], main_separations[1], main_separations[2], main_separations[3]};
        values[1] += first_inner[0];
        values[2] += first_inner[1];
        values[3] += first_inner[2];
        if (not check_vals(values)) {
            continue;
        }
        for (const auto &second_inner : inner_seps[1]) {
            std::vector<size_t>  vals_1 = values;
            vals_1[0] += second_inner[0];
            vals_1[2] += second_inner[1];
            vals_1[3] += second_inner[2];
            if (not check_vals(vals_1)) {
                continue;
            }
            for (const auto &third_inner : inner_seps[2]) {
                std::vector<size_t>  vals_2 = vals_1;
                vals_2[0] += third_inner[0];
                vals_2[1] += third_inner[1];
                vals_2[3] += third_inner[2];
                if (not check_vals(vals_2)) {
                    continue;
                }
                for (const auto &fourth_inner : inner_seps[3]) {
                    std::vector<size_t>  vals_3 = vals_2;
                    vals_3[0] += fourth_inner[0];
                    vals_3[1] += fourth_inner[1];
                    vals_3[2] += fourth_inner[2];
                    if (check_vals(vals_3)) {
                        std::vector<std::vector<size_t>> a = {first_inner,second_inner,third_inner,fourth_inner};
                        TesseraTable table(a, acid::DNA);
                        if (table.check_structure(all_tables)) {
                            all_tables.push_back(table);
                        }
                    }
                }
            }
        }
    }

    return all_tables;
}

bool TesseraTable::check_vals(const std::vector<std::size_t> &vals) {
    for (const auto &val: vals) {
        if (val > 6) {
            return false;
        }
    }

    return true;
}

bool TesseraTable::check_structure(const std::vector<TesseraTable> &tables) {

    if (!this->testTable()) {
        return false;
    }

    this->minValueOrderTable();

    for(const auto &old_table: tables) {
        if(this->equal(old_table)) {
            return false;
        }
    }

    return true;
}