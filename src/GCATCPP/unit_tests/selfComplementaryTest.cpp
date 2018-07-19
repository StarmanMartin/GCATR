//
// Created by Martin on 17.07.2018.
//

#include "gtest/gtest.h"
#include "../codes/StdGenCode.h"

bool run_self_complementary_for_code(std::vector<std::string> code) {
    StdGenCode sc(code);
    return sc.is_self_complementary();
}

TEST(SelfComplementary, CodeIsSelfComplementary) {
    EXPECT_TRUE(run_self_complementary_for_code({"ACG", "CGT"}));
    EXPECT_TRUE(run_self_complementary_for_code(
            {"AAC", "AAG", "AAU", "ACC", "ACG", "ACU", "AGC", "AGG", "AGU", "AUU", "CCG", "CCU", "CGG", "CGU", "CUU",
             "GCU", "GGU", "GUU", "UCA", "UGA"}));
}

TEST(SelfComplementary, CodeIsNotSelfComplementary) {
    EXPECT_FALSE(run_self_complementary_for_code({"ACG", "CGG"}));
    EXPECT_FALSE(run_self_complementary_for_code({"ACG", "CG"}));
    EXPECT_FALSE(run_self_complementary_for_code({"ACA", "UGT"}));
    EXPECT_FALSE(run_self_complementary_for_code(
            {"AAC", "AAG", "AAU", "ACC", "ACG", "ACU", "AGC", "AGG", "AGU", "AUU", "CCG", "CCU", "CGG", "CGU", "CUU",
             "GCU", "GGU", "GUU", "UCA"}));
}