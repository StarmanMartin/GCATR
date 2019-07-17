//
// Created by Martin on 15.07.2018.
//

#include "gtest/gtest.h"
#include "../codes/StdGenCode.h"

bool _is_code_test(std::vector<std::string> c) {
    StdGenCode a(c);
    return a.test_code();
}

TEST (CodeTest, IsCode) {
    EXPECT_EQ(_is_code_test({"AGA", "AUA", "CAA"}), true);

    EXPECT_EQ(_is_code_test(
            {"AAC", "AAG", "AAU", "ACC", "ACG", "ACU", "AGC", "AGG", "AGU", "AUU", "CCG", "CCU", "CGG", "CGU", "CUU",
             "GCU", "GGU", "GUU", "UCA", "UGA"}), true);
}

TEST (CodeTest, IsNoGenCode) {
    EXPECT_EQ(_is_code_test({"AGA", "AUG", "CTA"}), false);
    StdGenCode b({"AGGA", "AGUG", "CGUA"});
    StdGenCode c(b);
    EXPECT_EQ(c.test_code(), false);
    EXPECT_EQ(_is_code_test({"AGGA", "AGUG", "CGUA"}), false);

    EXPECT_EQ(_is_code_test({"ALA"}), false);

    EXPECT_EQ(_is_code_test({"ACA", "CU", "CUG", "GAC", "UGA"}), false);
}