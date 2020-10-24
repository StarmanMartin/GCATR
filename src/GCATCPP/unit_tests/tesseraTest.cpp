//
// Created by martins on 19.07.19.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../codes/TesseraCode.h"
#include "../codes/CodeFactory.h"
#include "../codes/TesseraTable.h"


int indexOf(std::vector<std::string> vec, const std::string& obj) {
    // Check if element 22 exists in vector
    auto it = std::find(vec.begin(), vec.end(), obj);
    if (it == vec.end())
        std::cout << "Element Not Found" << std::endl;

    // Get index of element from iterator
    return std::distance(vec.begin(), it);
}

TEST(TESSERA_TEST, CORRECT_TESSEREA) {
    std::vector<std::string> code_vec = {"AAUU", "ACCA"};
    TesseraCode t(code_vec);
    EXPECT_TRUE(t.test_code());
}

TEST(TESSERA_TEST, WRONG_TESSEREA) {
    std::vector<std::string> code_vec = {"AAUC", "ACCA"};
    TesseraCode t(code_vec);
    EXPECT_FALSE(t.test_code());
}

TEST(TESSERA_TEST, FACTORY_TESSEREA) {
    {
        std::vector<std::string> code_vec = {"AAUC", "ACCA"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        EXPECT_FALSE(t->test_code());
    }
    {
        std::vector<std::string> code_vec = {"AAUU", "ACCA"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        EXPECT_TRUE(t->test_code());
    }
}

TEST(TESSERA_TEST, FACTORY_TESSEREA_FROM_CODONS) {
    std::vector<std::string> code_vec = {"AAU", "ACC"};
    auto t = CodeFactory::rFactorTypesTesseraCodeFromCodons(code_vec);
    auto a = t->as_unsorted_vector();
    EXPECT_TRUE(t->test_code());
}



TEST(TESSERA_TEST, FACTORY_CODONS_FROM_TESSEREA) {
    std::vector<std::string> code_vec = {"AAUU", "ACCA"};
    auto t = CodeFactory::rFactorTypesCodonsCodeFromTessera(code_vec);
    auto a = t->as_unsorted_vector();

    EXPECT_TRUE(t->test_code());
}

TEST(TESSERA_TEST, FACTORY_TESSEREA_TABLE) {
    {
        std::vector<std::string> code_vec = {"GGTT", "AACC", "TTCC", "GGAA"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);
        auto dc = a.get_dinucleotide_classes();
        EXPECT_TRUE(indexOf(dc[0], "GG") < indexOf(dc[0], "TT"));
        EXPECT_TRUE(indexOf(dc[0], "GG") < indexOf(dc[0], "AA"));
        EXPECT_TRUE(indexOf(dc[0], "AA") < indexOf(dc[0], "CC"));
        EXPECT_TRUE(indexOf(dc[0], "TT") < indexOf(dc[0], "CC"));
    }
    {
        std::vector<std::string> code_vec = {"AACC", "AAGG", "AATT", "GGCC", "GGTT", "CCTT", "TAGC", "TACG", "CGAT",
                                             "ATGC", "TGAC", "GTCA"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);
        auto dc = a.get_dinucleotide_classes();
        EXPECT_TRUE(indexOf(dc[0], "AA") < indexOf(dc[0], "GG"));
        EXPECT_TRUE(indexOf(dc[0], "GG") < indexOf(dc[0], "CC"));
        EXPECT_TRUE(indexOf(dc[0], "CC") < indexOf(dc[0], "TT"));
        auto str_table = a.printableTable();
        EXPECT_EQ(str_table, "|6|2|2|2|\n|0|4|2|2|\n|0|0|2|2|\n|0|0|0|0|");

        EXPECT_TRUE(a.testTable());
    }
    {
        std::vector<std::string> code_vec = {"AACC", "CCGG", "CCTT"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);
        auto dc = a.get_dinucleotide_classes();
        EXPECT_TRUE(indexOf(dc[0], "CC") < indexOf(dc[0], "GG"));
        EXPECT_TRUE(indexOf(dc[0], "CC") < indexOf(dc[0], "TT"));
        EXPECT_TRUE(indexOf(dc[0], "AA") < indexOf(dc[0], "CC"));
    }
    {
        std::vector<std::string> code_vec = {"CCGG", "CCTT", "AACC"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);
        auto dc = a.get_dinucleotide_classes();
        EXPECT_TRUE(indexOf(dc[0], "CC") < indexOf(dc[0], "GG"));
        EXPECT_TRUE(indexOf(dc[0], "CC") < indexOf(dc[0], "TT"));
        EXPECT_TRUE(indexOf(dc[0], "AA") < indexOf(dc[0], "CC"));
    }
    {
        std::vector<std::string> code_vec = {"GGCC", "TTCC", "CCAA"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);
        auto dc = a.get_dinucleotide_classes();
        EXPECT_TRUE(indexOf(dc[0], "GG") < indexOf(dc[0], "CC"));
        EXPECT_TRUE(indexOf(dc[0], "TT") < indexOf(dc[0], "CC"));
        EXPECT_TRUE(indexOf(dc[0], "CC") < indexOf(dc[0], "AA"));
    }
    {
        std::vector<std::string> code_vec = {"CCAA", "GGCC", "TTCC"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);
        auto dc = a.get_dinucleotide_classes();
        EXPECT_TRUE(indexOf(dc[0], "GG") < indexOf(dc[0], "CC"));
        EXPECT_TRUE(indexOf(dc[0], "TT") < indexOf(dc[0], "CC"));
        EXPECT_TRUE(indexOf(dc[0], "CC") < indexOf(dc[0], "AA"));
    }
    {
        std::vector<std::string> code_vec = {"CCAA", "GTTG"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);

        ASSERT_THAT(a.generateCode(), testing::ElementsAre("CCAA", "GTTG" ));
    }
    {
        std::vector<std::string> code_vec = {"CAAC" , "GTTG"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);

        ASSERT_THAT(a.generateCode(), testing::ElementsAre("GTTG", "CAAC"));
    }
    {
        std::vector<std::string> code_vec = {"CCAA", "GGTT"};
        auto t = CodeFactory::rFactorTypesTesseraCode(code_vec);
        TesseraTable a(t);

        ASSERT_THAT(a.generateCode(), testing::ElementsAre("CCAA", "GGTT" ));

        a.setFragments({"YR","KM","SW","Id"});
        ASSERT_THAT(a.generateCode(), testing::ElementsAre("AGTC", "CTGA" ));

        a.setTableStructure({{0,0,0},{0,0,0},{0,0,0},{0,0,2}});
        ASSERT_THAT(a.generateCode(), testing::ElementsAre("CCGG", "AATT" ));

        a.setTableStructure({{0,0,0},{0,0,0},{0,0,0},{0,2,0}});
        ASSERT_THAT(a.generateCode(), testing::ElementsAre("GGTT", "CCAA"));

        a.setTableStructure({{0,0,0},{0,0,0},{0,0,0},{2,0,0}});
        ASSERT_THAT(a.generateCode(), testing::ElementsAre("CCTT", "GGAA"));
    }
}