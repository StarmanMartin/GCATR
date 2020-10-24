//
// Created by mstar on 19.10.2020.
//

#ifndef GCATCPP_TESSERATABLE_H
#define GCATCPP_TESSERATABLE_H

#include <cstddef>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include "Acid.h"

class TesseraCode;

class TesseraTable {
public:
    explicit TesseraTable(std::shared_ptr<TesseraCode>);;
    explicit TesseraTable(acid::acids acid);

    TesseraTable(const std::vector<std::vector<std::size_t>>&, acid::acids);

    void setTableStructure(const std::vector<std::vector<std::size_t>> &);

    void setFragments(std::vector<std::string> inFragments);
    std::vector<std::vector<std::string>> generate_dinucleotide_classes();
    std::vector<std::vector<std::string>> get_dinucleotide_classes();

    [[nodiscard]] std::vector<std::string> generateCode() const;
    [[nodiscard]] std::string printableTable() const;

    bool testTable();

private:
    acid::acids acid;
    std::vector<std::size_t> tableValues;
    std::vector<std::size_t> fragmentValues;
    std::map<std::string, std::size_t> fragments;

    std::vector<std::vector<std::string>> din_classes;

    void reset_fragmet_order();

    void generate_classes_order_from_map(std::map<std::string, size_t> din_map);

    std::map<std::string, size_t> generate_dinucleotide_order_map();

    void resetDinOrderByFragmentStructure(const std::vector<std::string> & inFrag);
    void _reset_fragmet_order();

    [[nodiscard]] int indexOfDin(size_t idx, const std::string& obj) const;
    [[nodiscard]] static std::string nextTransformation(const std::string &,const std::string &) ;
};


#endif //GCATCPP_TESSERATABLE_H
