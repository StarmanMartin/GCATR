//
// Created by martins on 19.07.19.
//

#include "test_utils.cpp"
#include "../codes/TesseraCode.h"
#include "../codes/CodeFactory.h"

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