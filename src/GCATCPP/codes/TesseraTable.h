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
    TesseraTable( const TesseraTable & ) = default;


    void setTableStructure(const std::vector<std::vector<std::size_t>> &);

    void setFragments(std::vector<std::string> inFragments);
    std::vector<std::vector<std::string>> generateDinucleotideClasses();
    std::vector<std::vector<std::string>> getDinucleotideClasses();

    [[nodiscard]] std::vector<std::string> generateCode() const;
    [[nodiscard]] std::string printableTable() const;
    [[nodiscard]] size_t checkSum() const;

    bool testTable();

    void permutateTableByIdxList(std::vector<std::size_t> perm);

    void permutateTableByIdxList(size_t,size_t,size_t,size_t);

    void minValueOrderTable();

    static std::vector<std::vector<std::size_t>> generateFragmentDistribution(size_t codeSize);
    static std::vector<TesseraTable> generateCDSForFragmentDistribution(std::vector<std::size_t>);

private:
    acid::acids acid;
    //std::vector<std::size_t> row_values;
    std::vector<std::vector<std::size_t>> table_values;
    //std::vector<std::size_t> fragment_values;
    std::map<std::string, std::size_t> fragments_pos;

    std::vector<std::vector<std::string>> din_classes;

    void reset_fragmet_order();

    void generate_classes_order_from_map(std::map<std::string, size_t> din_map);

    std::map<std::string, size_t> generate_dinucleotide_order_map();

    void reset_din_order_by_fragment_pos(const std::vector<std::string> & inFrag);

    [[nodiscard]] int index_of_din(size_t idx, const std::string& obj) const;
    [[nodiscard]] static std::string next_transformation(const std::string &, const std::string &) ;

    size_t get_value_of_table_rows(size_t idx_range, ...) const;

    static bool compare_tables(const TesseraTable& table_1, const TesseraTable& table_2);
    [[nodiscard]] bool equal(const TesseraTable& table_2) const;

    [[nodiscard]] size_t get_value_of_single_row(size_t r_idx) const;

    void row_swap(size_t a, size_t b);

    [[nodiscard]] static std::vector<std::vector<std::vector<std::size_t>>> get_all_possible_inner_separations(const std::vector<std::size_t> &);

    [[nodiscard]] static std::vector<TesseraTable> assemble_valid_separations(const std::vector<std::vector<std::vector<std::size_t>>> &inner_seps,
                                                         const std::vector<std::size_t> &main_separations);

    bool static check_vals(const std::vector<std::size_t> &vals);

    bool check_structure(const std::vector<TesseraTable> &tables);
};


#endif //GCATCPP_TESSERATABLE_H
