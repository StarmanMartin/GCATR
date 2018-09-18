//
// Created by Martin on 15.09.2018.
//

#include "gtest/gtest.h"
#include "../genericCode/CodonTranslTables.h"
#include "../genericCode/CodonClusteringAlgorithm.h"
#include <sstream>
#include <string>

std::string getCodeAsOneLineByIndex(int idx, acid::acids ac=acid::acids::DNA) {
    auto codes = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(idx, ac);
    std::stringstream ss;
    for(const auto &c : codes) {
        ss << c;
    }

    return ss.str();
}

TEST (GenerticCodeTest, GetNames) {
    auto codes = gen_codes::CodonTranslTables::getInstance().getAllCodesText();
    std::cout << codes;

    EXPECT_EQ(codes, "The Standard Code(transl_table=1)\nThe Vertebrate Mitochondrial Code(transl_table=2)\nThe Yeast Mitochondrial Code(transl_table=3)\nThe Mold, Protozoan, and Coelenterate Mitochondrial Code and the Mycoplasma/Spiroplasma Code(transl_table=4)\nThe Invertebrate Mitochondrial Code(transl_table=5)\nThe Ciliate, Dasycladacean and Hexamita Nuclear Code(transl_table=6)\nThe Echinoderm and Flatworm Mitochondrial Code(transl_table=9)\nThe Euplotid Nuclear Code(transl_table=10)\nThe Bacterial, Archaeal and Plant Plastid Code(transl_table=11)\nThe Alternative Yeast Nuclear Code(transl_table=12)\nThe Ascidian Mitochondrial Code(transl_table=13)\nThe Alternative Flatworm Mitochondrial Code(transl_table=14)\nTer Chlorophycean Mitochondrial Code(transl_table=16)\nTrematode Mitochondrial Code(transl_table=21)\nScenedesmus obliquus Mitochondrial Code(transl_table=22)\nThraustochytrium Mitochondrial Code(transl_table=23)\nPterobranchia Mitochondrial Code(transl_table=24)\nCandidate Division SR1 and Gracilibacteria Code(transl_table=25)\nPachysolen tannophilus Nuclear Code(transl_table=26)\nKaryorelict Nuclear(transl_table=27)\nCondylostoma Nuclear(transl_table=28)\nMesodinium Nuclear(transl_table=29)\nPeritrich Nuclear(transl_table=30)\nBlastocrithidia Nuclear(transl_table=31)\n");
}

TEST (GenerticCodeTest, StandardCode) {
    auto codes = gen_codes::CodonTranslTables::getInstance().getStandardCode();
    std::stringstream ss;
    for(const auto &c : codes) {
        ss << c;
    }

    EXPECT_EQ(ss.str(), "TTTPheTCTSerTATTyrTGTCysTTCPheTCCSerTACTyrTGCCysTTALeuTCASerTAATerTGATerTTGLeuTCGSerTAGTerTGGTrpCTTLeuCCTProCATHisCGTArgCTCLeuCCCProCACHisCGCArgCTALeuCCAProCAAGlnCGAArgCTGLeuCCGProCAGGlnCGGArgATTIleACTThrAATAsnAGTSerATCIleACCThrAACAsnAGCSerATAIleACAThrAAALysAGAArgATGMetACGThrAAGLysAGGArgGTTValGCTAlaGATAspGGTGlyGTCValGCCAlaGACAspGGCGlyGTAValGCAAlaGAAGluGGAGlyGTGValGCGAlaGAGGluGGGGly");

    codes = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(1);
    std::stringstream ss_2;
    for(const auto &c : codes) {
        ss_2 << c;
    }

    EXPECT_EQ(ss_2.str(), "TTTPheTCTSerTATTyrTGTCysTTCPheTCCSerTACTyrTGCCysTTALeuTCASerTAATerTGATerTTGLeuTCGSerTAGTerTGGTrpCTTLeuCCTProCATHisCGTArgCTCLeuCCCProCACHisCGCArgCTALeuCCAProCAAGlnCGAArgCTGLeuCCGProCAGGlnCGGArgATTIleACTThrAATAsnAGTSerATCIleACCThrAACAsnAGCSerATAIleACAThrAAALysAGAArgATGMetACGThrAAGLysAGGArgGTTValGCTAlaGATAspGGTGlyGTCValGCCAlaGACAspGGCGlyGTAValGCAAlaGAAGluGGAGlyGTGValGCGAlaGAGGluGGGGly");

codes = gen_codes::CodonTranslTables::getInstance().getCodeByName("The Standard Code");
    std::stringstream ss_3;
    for(const auto &c : codes) {
        ss_3 << c;
    }

    EXPECT_EQ(ss_3.str(), "TTTPheTCTSerTATTyrTGTCysTTCPheTCCSerTACTyrTGCCysTTALeuTCASerTAATerTGATerTTGLeuTCGSerTAGTerTGGTrpCTTLeuCCTProCATHisCGTArgCTCLeuCCCProCACHisCGCArgCTALeuCCAProCAAGlnCGAArgCTGLeuCCGProCAGGlnCGGArgATTIleACTThrAATAsnAGTSerATCIleACCThrAACAsnAGCSerATAIleACAThrAAALysAGAArgATGMetACGThrAAGLysAGGArgGTTValGCTAlaGATAspGGTGlyGTCValGCCAlaGACAspGGCGlyGTAValGCAAlaGAAGluGGAGlyGTGValGCGAlaGAGGluGGGGly");

}

TEST (GenerticCodeTest, TheVertebrateMitochondrialCode) {
    auto code = getCodeAsOneLineByIndex(2);
    EXPECT_NE(std::string::npos, code.find("AGATer"));
    EXPECT_NE(std::string::npos, code.find("AGGTer"));
    EXPECT_NE(std::string::npos, code.find("ATAMet"));
    EXPECT_NE(std::string::npos, code.find("TGATrp"));
}

TEST (GenerticCodeTest, TheYeastMitochondrialCode) {
    auto code = getCodeAsOneLineByIndex(3);
    EXPECT_NE(std::string::npos, code.find("ATAMet"));
    EXPECT_NE(std::string::npos, code.find("CTTThr"));
    EXPECT_NE(std::string::npos, code.find("CTCThr"));
    EXPECT_NE(std::string::npos, code.find("CTAThr"));
    EXPECT_NE(std::string::npos, code.find("CTGThr"));
    EXPECT_NE(std::string::npos, code.find("TGATrp"));
    EXPECT_EQ(gen_codes::CodonTranslTables::getInstance().getIdxByName("The Yeast Mitochondrial Code"), 3);
}

TEST (GenerticCodeTest, TheYeastMitochondrialCodeRNA) {
    auto code = getCodeAsOneLineByIndex(3, acid::acids::RNA);
    EXPECT_NE(std::string::npos, code.find("AUAMet"));
    EXPECT_EQ(std::string::npos, code.find("ATAMet"));
}

TEST (GenerticCodeTest, ClusterAlgorthem) {
    auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(3);
    gen_codes::CodonClusteringAlgorithm cca(code);

   double average = cca.get_average_conductance();
   double max = cca.get_max_conductance();
   double min = cca.get_min_conductance();

   std::cout << std::endl << "average: " << average << " - max: " << max << " - min: " << min << std::endl << std::endl;
}
