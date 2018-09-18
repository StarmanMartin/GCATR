//
// Created by Martin on 15.09.2018.
//

#ifndef GCATCPP_KNOWNCODES_H
#define GCATCPP_KNOWNCODES_H

#define NUMBER_OF_CODES 24

#include <utility>
#include <vector>
#include <string>

#include "../codes/Acid.h"

namespace gen_codes {

    class TranslTableData {
    public:
        TranslTableData():index(-1) {};

        TranslTableData(TranslTableData const &a) {
            this->deviation = a.deviation;
            this->name = a.name;
            this->index = a.index;
        }

        std::vector<std::string> deviation;
        std::string name;
        int index;

        void setData(std::string name, int index, std::vector<std::string> deviation) {
            this->deviation = std::move(deviation);
            this->name = std::move(name);
            this->index = index;
        }
    };

    class CodonTranslTables {
    public:
        static CodonTranslTables &getInstance();

        const std::string getAllCodesText();

        const std::vector<std::string> getAllCodes();

        const std::vector<std::string> getCodeByName(const std::string& name, acid::acids ac=acid::acids::DNA);
        const std::vector<std::string> getCodeByIndex(int idx, acid::acids ac=acid::acids::DNA);

        const std::vector<std::string> getStandardCode(acid::acids ac=acid::acids::DNA);

        const int getIdxByName(const std::string& name);

    private:
        static std::string replaceAll(std::string str, const std::string &from, const std::string &to);

        explicit CodonTranslTables();

        bool isCodesSet = false;

        void setCodes();
        const std::vector<std::string> prepareCode(const TranslTableData &data, acid::acids ac);

        std::vector<TranslTableData> codes;
        const std::vector<std::string> standardCode = {"TTT", "Phe", "TCT", "Ser", "TAT", "Tyr", "TGT", "Cys", "TTC",
                                                       "Phe",
                                                       "TCC", "Ser", "TAC", "Tyr", "TGC", "Cys", "TTA", "Leu", "TCA",
                                                       "Ser",
                                                       "TAA", "Ter", "TGA", "Ter", "TTG", "Leu", "TCG", "Ser", "TAG",
                                                       "Ter",
                                                       "TGG", "Trp", "CTT", "Leu", "CCT", "Pro", "CAT", "His", "CGT",
                                                       "Arg",
                                                       "CTC", "Leu", "CCC", "Pro", "CAC", "His", "CGC", "Arg", "CTA",
                                                       "Leu",
                                                       "CCA", "Pro", "CAA", "Gln", "CGA", "Arg", "CTG", "Leu", "CCG",
                                                       "Pro",
                                                       "CAG", "Gln", "CGG", "Arg", "ATT", "Ile", "ACT", "Thr", "AAT",
                                                       "Asn",
                                                       "AGT", "Ser", "ATC", "Ile", "ACC", "Thr", "AAC", "Asn", "AGC",
                                                       "Ser",
                                                       "ATA", "Ile", "ACA", "Thr", "AAA", "Lys", "AGA", "Arg", "ATG",
                                                       "Met",
                                                       "ACG", "Thr", "AAG", "Lys", "AGG", "Arg", "GTT", "Val", "GCT",
                                                       "Ala",
                                                       "GAT", "Asp", "GGT", "Gly", "GTC", "Val", "GCC", "Ala", "GAC",
                                                       "Asp",
                                                       "GGC", "Gly", "GTA", "Val", "GCA", "Ala", "GAA", "Glu", "GGA",
                                                       "Gly",
                                                       "GTG", "Val", "GCG", "Ala", "GAG", "Glu", "GGG", "Gly"};

    public:
        CodonTranslTables(CodonTranslTables const &) = delete;

        void operator=(CodonTranslTables const &)  = delete;
    };
}
#endif //GCATCPP_KNOWNCODES_H
