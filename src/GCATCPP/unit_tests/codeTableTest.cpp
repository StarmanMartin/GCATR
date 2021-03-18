//
// Created by Martin on 15.09.2018.
//

#include "gtest/gtest.h"
#include "../geneticCode/CodonTranslTables.h"
#include "../geneticCode/CodonClusteringAlgorithm.h"
#include "../bda/BDATools.h"
#include "../sequences/Sequence.h"
#include "../codes/CodeFactory.h"
#include <string>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}


std::string get_aps_path(std::string relPath) {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    std::size_t idx = current_working_dir.find("GCATR")+5;
    current_working_dir = current_working_dir.substr(0,idx);


    current_working_dir = current_working_dir + "\\src\\GCATCPP\\" + ReplaceAll(relPath, "/", "\\");
    return current_working_dir;
}
#else
#include <unistd.h>
#include <filesystem>
namespace fs = std::filesystem;
#define GetCurrentDir getcwd

std::string get_aps_path(std::string relPath) {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir( buff, FILENAME_MAX );
    fs::path current_working_dir(buff);

    while(current_working_dir.filename() != "GCATR" && current_working_dir != current_working_dir.root_path()) {
        current_working_dir = current_working_dir.parent_path();
    }


    current_working_dir.append("src/GCATCPP");
    current_working_dir.append(relPath);
    return current_working_dir.string();



}

#endif




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
    //std::cout << codes;

    EXPECT_EQ(codes, "The Standard Code(transl_table=1)\nThe Vertebrate Mitochondrial Code(transl_table=2)\nThe Yeast Mitochondrial Code(transl_table=3)\nThe Mold, Protozoan, and Coelenterate Mitochondrial Code and the Mycoplasma/Spiroplasma Code(transl_table=4)\nThe Invertebrate Mitochondrial Code(transl_table=5)\nThe Ciliate, Dasycladacean and Hexamita Nuclear Code(transl_table=6)\nThe Echinoderm and Flatworm Mitochondrial Code(transl_table=9)\nThe Euplotid Nuclear Code(transl_table=10)\nThe Bacterial, Archaeal and Plant Plastid Code(transl_table=11)\nThe Alternative Yeast Nuclear Code(transl_table=12)\nThe Ascidian Mitochondrial Code(transl_table=13)\nThe Alternative Flatworm Mitochondrial Code(transl_table=14)\nTer Chlorophycean Mitochondrial Code(transl_table=16)\nTrematode Mitochondrial Code(transl_table=21)\nScenedesmus obliquus Mitochondrial Code(transl_table=22)\nThraustochytrium Mitochondrial Code(transl_table=23)\nPterobranchia Mitochondrial Code(transl_table=24)\nCandidate Division SR1 and Gracilibacteria Code(transl_table=25)\nPachysolen tannophilus Nuclear Code(transl_table=26)\nKaryorelict Nuclear(transl_table=27)\nCondylostoma Nuclear(transl_table=28)\nMesodinium Nuclear(transl_table=29)\nPeritrich Nuclear(transl_table=30)\nBlastocrithidia Nuclear(transl_table=31)\n");
}


TEST (GenerticCodeTest, readAndAddNewTable) {
    auto path_a = get_aps_path("unit_tests/asserts/correct_code.txt");
    EXPECT_TRUE(gen_codes::CodonTranslTables::getInstance().read_and_add_new_transl_table( path_a ));
    auto path_b = get_aps_path("unit_tests/asserts/wrong_1_code.txt");
    EXPECT_FALSE(gen_codes::CodonTranslTables::getInstance().read_and_add_new_transl_table( path_b ));
    auto path_c = get_aps_path("unit_tests/asserts/wrong_2_code.txt");
    EXPECT_FALSE(gen_codes::CodonTranslTables::getInstance().read_and_add_new_transl_table( path_c));
    auto path_d = get_aps_path("unit_tests/asserts/wrong_3_code.txt");
    EXPECT_FALSE(gen_codes::CodonTranslTables::getInstance().read_and_add_new_transl_table( path_d ));
    EXPECT_FALSE(gen_codes::CodonTranslTables::getInstance().read_and_add_new_transl_table( "Not A file"));

    EXPECT_EQ(gen_codes::CodonTranslTables::getInstance().getIdxByName("correct_code"), 900);

    auto code = getCodeAsOneLineByIndex(900, acid::acids::RNA);

    EXPECT_NE(std::string::npos, code.find("AUAGly"));
    EXPECT_NE(std::string::npos, code.find("UUUGly_Thr"));
    EXPECT_NE(std::string::npos, code.find("AAAArg"));
}

TEST (GenerticCodeTest, StandardCode) {
    auto codes = gen_codes::CodonTranslTables::getInstance().getStandardCode();
    std::stringstream ss;
    for(const auto &c : codes) {
        ss << c;
    }

    EXPECT_EQ(ss.str(), "TTTPheTCTSerTATTyrTGTCysTTCPheTCCSerTACTyrTGCCysTTALeuTCASerTAAStopTGAStopTTGLeuTCGSerTAGStopTGGTrpCTTLeuCCTProCATHisCGTArgCTCLeuCCCProCACHisCGCArgCTALeuCCAProCAAGlnCGAArgCTGLeuCCGProCAGGlnCGGArgATTIleACTThrAATAsnAGTSerATCIleACCThrAACAsnAGCSerATAIleACAThrAAALysAGAArgATGMetACGThrAAGLysAGGArgGTTValGCTAlaGATAspGGTGlyGTCValGCCAlaGACAspGGCGlyGTAValGCAAlaGAAGluGGAGlyGTGValGCGAlaGAGGluGGGGly");

    codes = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(1);
    std::stringstream ss_2;
    for(const auto &c : codes) {
        ss_2 << c;
    }

    EXPECT_EQ(ss_2.str(), "TTTPheTCTSerTATTyrTGTCysTTCPheTCCSerTACTyrTGCCysTTALeuTCASerTAAStopTGAStopTTGLeuTCGSerTAGStopTGGTrpCTTLeuCCTProCATHisCGTArgCTCLeuCCCProCACHisCGCArgCTALeuCCAProCAAGlnCGAArgCTGLeuCCGProCAGGlnCGGArgATTIleACTThrAATAsnAGTSerATCIleACCThrAACAsnAGCSerATAIleACAThrAAALysAGAArgATGMetACGThrAAGLysAGGArgGTTValGCTAlaGATAspGGTGlyGTCValGCCAlaGACAspGGCGlyGTAValGCAAlaGAAGluGGAGlyGTGValGCGAlaGAGGluGGGGly");

    codes = gen_codes::CodonTranslTables::getInstance().getCodeByName("The Standard Code");
    std::stringstream ss_3;
    for(const auto &c : codes) {
        ss_3 << c;
    }

    EXPECT_EQ(ss_3.str(), "TTTPheTCTSerTATTyrTGTCysTTCPheTCCSerTACTyrTGCCysTTALeuTCASerTAAStopTGAStopTTGLeuTCGSerTAGStopTGGTrpCTTLeuCCTProCATHisCGTArgCTCLeuCCCProCACHisCGCArgCTALeuCCAProCAAGlnCGAArgCTGLeuCCGProCAGGlnCGGArgATTIleACTThrAATAsnAGTSerATCIleACCThrAACAsnAGCSerATAIleACAThrAAALysAGAArgATGMetACGThrAAGLysAGGArgGTTValGCTAlaGATAspGGTGlyGTCValGCCAlaGACAspGGCGlyGTAValGCAAlaGAAGluGGAGlyGTGValGCGAlaGAGGluGGGGly");

}

TEST (GenerticCodeTest, NotExistingCodes) {
    auto codes = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(-2);
    EXPECT_EQ(0, codes.size());
    codes = gen_codes::CodonTranslTables::getInstance().getCodeByName("Martin");
    EXPECT_EQ(0, codes.size());
    int idx = gen_codes::CodonTranslTables::getInstance().getIdxByName("Martin");
    EXPECT_EQ(1, idx);
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

TEST (GenerticCodeTest, TheMoldProtozoanAndCoelenterateMitochondrialCodeAndTheMycoplasma_SpiroplasmaCode) {
    auto code = getCodeAsOneLineByIndex(4, acid::acids::RNA);
    EXPECT_NE(std::string::npos, code.find("UGATrp"));
    EXPECT_EQ(gen_codes::CodonTranslTables::getInstance().getIdxByName("The Mold, Protozoan, and Coelenterate Mitochondrial Code and the Mycoplasma/Spiroplasma Code"), 4);
}

TEST (GenerticCodeTest, TheInvertebrateMitochondrialCode) {
    auto code = getCodeAsOneLineByIndex(5, acid::acids::RNA);
    EXPECT_NE(std::string::npos, code.find("AGASer"));
    EXPECT_NE(std::string::npos, code.find("AGGSer"));
    EXPECT_NE(std::string::npos, code.find("AUAMet"));
    EXPECT_NE(std::string::npos, code.find("UGATrp"));
    EXPECT_EQ(gen_codes::CodonTranslTables::getInstance().getIdxByName("The Invertebrate Mitochondrial Code"), 5);
}

TEST (GenerticCodeTest, BlastocrithidiaNuclear) {
    auto code = getCodeAsOneLineByIndex(31, acid::acids::RNA);
    EXPECT_NE(std::string::npos, code.find("UGATrp"));
    EXPECT_NE(std::string::npos, code.find("UAGGlu_STOP"));
    EXPECT_NE(std::string::npos, code.find("UAAGlu_STOP"));
    EXPECT_EQ(gen_codes::CodonTranslTables::getInstance().getIdxByName("Blastocrithidia Nuclear"), 31);
}

TEST (GenerticCodeTest, ClusterAlgorthemNotUniqueTrransl) {
    auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(900);
    gen_codes::CodonClusteringAlgorithm cca(code);

    double average = cca.get_average_conductance();
    double max = cca.get_max_conductance();
    double min = cca.get_min_conductance();

    EXPECT_NEAR(1, min, 0.000001);
    EXPECT_NEAR(0.675675675, max, 0.000001);
    EXPECT_NEAR(0.8412048, average, 0.000001);
}

TEST (GenerticCodeTest, ClusterAlgorthem) {
    auto code = gen_codes::CodonTranslTables::getInstance().getStandardCode();
    gen_codes::CodonClusteringAlgorithm cca(code);

   double average = cca.get_average_conductance();
   double max = cca.get_max_conductance();
   double min = cca.get_min_conductance();

    EXPECT_NEAR(1, min, 0.000001);
    EXPECT_NEAR(0.666667, max, 0.000001);
    EXPECT_NEAR(0.811287, average, 0.000001);
}

TEST (GenerticCodeTest, ClusterAlgorthemBDA) {
    auto code_vec = BDA::BDATools::get_all_rna_tuples(2);
    auto code = CodeFactory::rFactorGenCode(code_vec);
    auto bda_obj = BDA::BDATools(code);

    bda_obj.add_rule(1,2,'C', 'G', 'A', 'U');
    bda_obj.add_rule(1,2,'G', 'C', 'A', 'U');

    auto bda_res = bda_obj.run_bda_for_code();

    gen_codes::CodonClusteringAlgorithm cca(bda_res);

   double average = cca.get_average_conductance();
   double max = cca.get_max_conductance();
   double min = cca.get_min_conductance();

    EXPECT_NEAR(.66, min, 0.01);
    EXPECT_NEAR(0.5, max, 0.000001);
    EXPECT_NEAR(0.583, average, 0.001);
}

TEST (GenerticCodeTest, ClusterAlgorthemCsvTable) {
    auto code = gen_codes::CodonTranslTables::getInstance().getStandardCode();
    gen_codes::CodonClusteringAlgorithm cca(code);

   std::string csv_string = cca.generate_value_table_csv_string();



    std::string file_path = __FILE__;
    std::string dir_path = file_path.substr(0, file_path.rfind("unit_tests"));


   std::string fileName = cca.generate_value_table_file_csv_string(dir_path + "/unit_tests/asserts", "TEST");

   EXPECT_EQ(";Ala;Arg;Asn;Asp;Cys;Gln;Glu;Gly;His;Ile;Leu;Lys;Met;Phe;Pro;Ser;Stop;Thr;Trp;Tyr;Val;\nAla;12;0;0;2;0;0;2;4;0;0;0;0;0;0;4;4;0;4;0;0;4;\nArg;0;18;0;0;2;2;0;6;2;1;4;2;1;0;4;6;2;2;2;0;0;\nAsn;0;0;2;2;0;0;0;0;2;2;0;4;0;0;0;2;0;2;0;2;0;\nAsp;2;0;2;2;0;0;4;2;2;0;0;0;0;0;0;0;0;0;0;2;2;\nCys;0;2;0;0;2;0;0;2;0;0;0;0;0;2;0;4;2;0;2;2;0;\nGln;0;2;0;0;0;2;2;0;4;0;2;2;0;0;2;0;2;0;0;0;0;\nGlu;2;0;0;4;0;2;2;2;0;0;0;2;0;0;0;0;2;0;0;0;2;\nGly;4;6;0;2;2;0;2;12;0;0;0;0;0;0;0;2;1;0;1;0;4;\nHis;0;2;2;2;0;4;0;0;2;0;2;0;0;0;2;0;0;0;0;2;0;\nIle;0;1;2;0;0;0;0;0;0;6;4;1;3;2;0;2;0;3;0;0;3;\nLeu;0;4;0;0;0;2;0;0;2;4;18;0;2;6;4;2;3;0;1;0;6;\nLys;0;2;4;0;0;2;2;0;0;1;0;2;1;0;0;0;2;2;0;0;0;\nMet;0;1;0;0;0;0;0;0;0;3;2;1;0;0;0;0;0;1;0;0;1;\nPhe;0;0;0;0;2;0;0;0;0;2;6;0;0;2;0;2;0;0;0;2;2;\nPro;4;4;0;0;0;2;0;0;2;0;4;0;0;0;12;4;0;4;0;0;0;\nSer;4;6;2;0;4;0;0;2;0;2;2;0;0;2;4;14;3;6;1;2;0;\nStop;0;2;0;0;2;2;2;1;0;0;3;2;0;0;0;3;4;0;2;4;0;\nThr;4;2;2;0;0;0;0;0;0;3;0;2;1;0;4;6;0;12;0;0;0;\nTrp;0;2;0;0;2;0;0;1;0;0;1;0;0;0;0;1;2;0;0;0;0;\nTyr;0;0;2;2;2;0;0;0;2;0;0;0;0;2;0;2;4;0;0;2;0;\nVal;4;0;0;2;0;0;2;4;0;3;6;0;1;2;0;0;0;0;0;0;12;", csv_string);

    std::remove(fileName.c_str());
}
