
//
// Created by Martin on 11.10.2018.
//

#include "test_utils.cpp"
#include "../codes/StdGenCode.h"
#include "../generator/BaseValueGenerator.h"


TEST (BaseValueGeneratorTester, SimpleGenerator) {
    auto code = BaseValueGenerator({{"A",0}, {"C",1},{"G",2},{"U",3}}, {16,4,1});
    auto code_list =  code.run();
    std::vector<std::string> a = {"AAC", "AAG", "AAU", "ACC", "ACG", "ACU", "AGC", "AGG", "AGU", "AUC", "AUG", "AUU", "CCG", "CCU", "CGG", "CGU", "CUG", "CUU", "GGU", "GUU"};
    test_help::test_equal_vector(a, code_list);
}

TEST (BaseValueGeneratorTester, SimpleGeneratorSize4) {

    auto code = BaseValueGenerator({{"A",0}, {"C",1},{"G",2},{"U",3}}, {4*4*4,16,4,1});
    auto code_list =  code.run();
    EXPECT_EQ(code_list[0], "AAAC");
}

TEST (BaseValueGeneratorTester, SimpleGeneratorSizeError) {

    auto code = BaseValueGenerator({{"A",0}, {"C",0}}, {16,4,1});
    auto code_list =  code.run();
    EXPECT_EQ(code_list[0], "CAA");
}
