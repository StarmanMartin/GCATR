//
// Created by Martin on 15.09.2018.
//

#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include "CodonTranslTables.h"

using namespace gen_codes;

CodonTranslTables::CodonTranslTables() {
    std::vector<TranslTableData> temp(NUMBER_OF_CODES);
    this->codes = temp;
};

CodonTranslTables &CodonTranslTables::getInstance() {
    static CodonTranslTables _instance;

    return _instance;
}

const std::string CodonTranslTables::getAllCodesText() {

    std::vector<std::string> codeStringList = this->getAllCodes();

    const char *const delim = "\n";

    std::ostringstream imploded;
    std::copy(codeStringList.begin(), codeStringList.end(),
              std::ostream_iterator<std::string>(imploded, delim));


    return imploded.str();
}

const std::vector<std::string> CodonTranslTables::getAllCodes() {
    this->setCodes();
    auto codeStringList = std::vector<std::string>();

    for (auto tempCode : this->codes) {
        std::stringstream ss;
        ss << tempCode.name << "(transl_table=" << tempCode.index << ")";
        codeStringList.push_back(ss.str());
    }


    return codeStringList;
}

void CodonTranslTables::setCodes() {
    if (this->isCodesSet) {
        return;
    }

    this->isCodesSet = true;

    this->codes[0].setData("The Standard Code", 1, {});
    this->codes[1].setData("The Vertebrate Mitochondrial Code", 2,
                           {"AGA", "Ter", "AGG", "Ter", "ATA", "Met", "TGA", "Trp"});
    this->codes[2].setData("The Yeast Mitochondrial Code", 3,
                           {"ATA", "Met", "CTT", "Thr", "CTC", "Thr", "CTA", "Thr", "CTG", "Thr", "TGA", "Trp"});
    this->codes[3].setData(
            "The Mold, Protozoan, and Coelenterate Mitochondrial Code and the Mycoplasma/Spiroplasma Code", 4,
            {"TGA", "Trp"});
    this->codes[4].setData("The Invertebrate Mitochondrial Code", 5,
                           {"AGA", "Ser", "AGG", "Ser", "ATA", "Met", "TGA", "Trp"});
    this->codes[5].setData("The Ciliate, Dasycladacean and Hexamita Nuclear Code", 6, {"TAA", "Gln", "TAG", "Gln"});
    this->codes[6].setData("The Echinoderm and Flatworm Mitochondrial Code", 9,
                           {"AAA", "Asn", "AGA", "Ser", "AGG", "Ser", "TGA", "Trp"});
    this->codes[7].setData("The Euplotid Nuclear Code", 10, {"TGA", "Cys"});
    this->codes[8].setData("The Bacterial, Archaeal and Plant Plastid Code", 11, {});
    this->codes[9].setData("The Alternative Yeast Nuclear Code", 12, {"CTG", "Ser"});
    this->codes[10].setData("The Ascidian Mitochondrial Code", 13,
                            {"AGA", "Gly", "AGG", "Gly", "ATA", "Met", "TGA", "Trp"});
    this->codes[11].setData("The Alternative Flatworm Mitochondrial Code", 14,
                            {"AAA", "Asn", "AGA", "Ser", "AGG", "Ser", "TAA", "Tyr", "TGA", "Trp"});
    this->codes[12].setData("Ter Chlorophycean Mitochondrial Code", 16, {"TAG", "Leu"});
    this->codes[13].setData("Trematode Mitochondrial Code", 21,
                            {"TGA", "Trp", "ATA", "Met", "AGA", "Ser", "AGG", "Ser", "AAA", "Asn"});
    this->codes[14].setData("Scenedesmus obliquus Mitochondrial Code", 22, {"TCA", "STOP", "TAG", "Leu"});
    this->codes[15].setData("Thraustochytrium Mitochondrial Code", 23, {});
    this->codes[16].setData("Pterobranchia Mitochondrial Code", 24, {"AGA", "Ser", "AGG", "Lys", "TGA", "Trp"});
    this->codes[17].setData("Candidate Division SR1 and Gracilibacteria Code", 25, {"TGA", "Gly"});
    this->codes[18].setData("Pachysolen tannophilus Nuclear Code", 26, {"CTG", "Ala"});
    this->codes[19].setData("Karyorelict Nuclear", 27, {"TAG", "Gln", "TAA", "Gln", "TGA", "STOP_Trp"});
    this->codes[20].setData("Condylostoma Nuclear", 28, {"TAA", "Gln_STOP", "TAG", "Gln_STOP", "TGA", "Trp_STOP"});
    this->codes[21].setData("Mesodinium Nuclear", 29, {"TAA", "Tyr", "TAG", "Tyr"});
    this->codes[22].setData("Peritrich Nuclear", 30, {"TAA", "Glu", "TAG", "Glu"});
    this->codes[23].setData("Blastocrithidia Nuclear", 31, {"TGA", "Trp", "TAG", "Glu_STOP", "TAA", "Glu_STOP"});
}

const std::vector<std::string> CodonTranslTables::getCodeByName(const std::string &name, acid::acids ac) {
    this->setCodes();
    for (TranslTableData& code : this->codes) {
        if(code.name == name) {
            return this->prepareCode(code, ac);
        }
    }

    return std::vector<std::string>();
}

const std::vector<std::string> CodonTranslTables::getCodeByIndex(int idx, acid::acids ac) {
    this->setCodes();
    for (int startIdx = std::min(idx, NUMBER_OF_CODES) - 1; startIdx >= 0; --startIdx) {
        if (this->codes[startIdx].index == idx) {
            return this->prepareCode(this->codes[startIdx], ac);
        }
    }

    return std::vector<std::string>();
}

const std::vector<std::string> CodonTranslTables::getStandardCode(acid::acids ac) {
    return this->getCodeByIndex(1, ac);
}

const std::vector<std::string> CodonTranslTables::prepareCode(const TranslTableData &data, acid::acids ac) {
    auto newCode = this->standardCode;
    for(int i = 0; i < newCode.size(); i += 2) {
        for (int deviationIdx = 0; deviationIdx < data.deviation.size(); deviationIdx += 2) {
            if(newCode[i] == data.deviation[deviationIdx]) {
                std::string label = data.deviation[deviationIdx+1];
                newCode[i+1] = CodonTranslTables::replaceAll(label, "_", " or ");
            }
        }

        if(ac == acid::acids::RNA) {
            std::replace( newCode[i].begin(), newCode[i].end(), acid::bases::THYMINE, acid::bases::URACIL);
        }
    }

    return newCode;
}

std::string CodonTranslTables::replaceAll(std::string str, const std::string &from, const std::string &to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

const int CodonTranslTables::getIdxByName(const std::string &name) {
    this->setCodes();
    for (TranslTableData& code : this->codes) {
        if(code.name == name) {
            return code.index;
        }
    }

    return 1;
}
