
//
// Created by Martin on 11.10.2018.
//

#include "test_utils.cpp"
#include "../codes/StdGenCode.h"
#include "../generator/BaseValueGenerator.h"

#include <cmath>

TEST(MacimalLength, LengthForDiffAlphabet) {
    double res44 = (pow(4,4)-pow(4,2))/4.0f;
    EXPECT_EQ(AbstractCode::getMaxLength(4,4), static_cast<int>(res44)) ;
    EXPECT_EQ(AbstractCode::getMaxLength(4,3), 20);
    EXPECT_EQ(AbstractCode::getMaxLength(3,6), 116);
    EXPECT_EQ(AbstractCode::getMaxLength(3,1), 3);
    EXPECT_ANY_THROW(AbstractCode::getMaxLength(1,3));
    EXPECT_ANY_THROW(AbstractCode::getMaxLength(-1,3));
    EXPECT_ANY_THROW(AbstractCode::getMaxLength(4,-3));
}

TEST (BaseValueGeneratorTester, SimpleGenerator) {
    auto code = BaseValueGenerator({{"A",0}, {"C",1},{"G",2},{"U",3}}, {16,4,1});
    auto code_list =  code.run();
    std::vector<std::string> a = {"AAC", "AAG", "AAU", "ACC", "ACG", "ACU", "AGC", "AGG", "AGU", "AUC", "AUG", "AUU", "CCG", "CCU", "CGG", "CGU", "CUG", "CUU", "GGU", "GUU"};
    test_help::test_equal_vector(a, code_list);


    BaseValueGenerator codeGenerator({"0", "1"}, 5, true);
    code_list =  codeGenerator.run();
    EXPECT_EQ(code_list.size(), 6);

}

TEST (BaseValueGeneratorTester, SimpleGeneratorSize4) {

    auto code = BaseValueGenerator({{"A",0}, {"C",1},{"G",2},{"U",3}}, {4*4*4,16,4,1});
    auto code_list =  code.run();
    EXPECT_EQ(code_list[0], "AAAC");
}

TEST (BaseValueGeneratorTester, SimpleGeneratorSizeError) {

    auto code = BaseValueGenerator({{"A",0}, {"C",1}}, {64,32,16,8,4,2,1});
    auto code_list =  code.run();
    for(auto x : code_list) {
        std::cout << "\"" << x << "\", ";
    }

    std::cout << std::endl;

    EXPECT_EQ(code_list[0], "AAAAAAC");

    code = BaseValueGenerator({{"A",0}, {"C",1}}, {16,8,4,2,1});
    code_list =  code.run();
    for(auto x : code_list) {
        std::cout << "\"" << x << "\", ";
    }

    std::cout << std::endl;
}

