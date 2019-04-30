//
// Created by Martin on 15.07.2018.
//

#include "gtest/gtest.h"
#include "../codes/StdGenCode.h"

bool _is_circular(std::vector<std::string> c) {
    StdGenCode a(c);
    return a.is_circular();
}

TEST (CircularTest, CircularCodes) {
    EXPECT_EQ(_is_circular({"AGA", "AUA", "CAA"}), true);

    EXPECT_EQ(_is_circular(
            {"AAC", "AAG", "AAU", "ACC", "ACG", "ACU", "AGC", "AGG", "AGU", "AUU", "CCG", "CCU", "CGG", "CGU", "CUU",
             "GCU", "GGU", "GUU", "UCA", "UGA"}), true);
}

TEST (CircularTest, NotCircularCodes) {
   EXPECT_EQ(_is_circular({"AGA", "AAG", "CAA"}), false);

   EXPECT_EQ(_is_circular({"AAA"}), false);

   EXPECT_EQ(_is_circular({"ACA", "CAU", "CUG", "GAC", "UGA"}), false);
}

TEST (CircularTest, NotCircularCodesLength) {
    EXPECT_EQ(_is_circular({"CCCAAAA", "ACCCAAA"}), false);
    EXPECT_EQ(_is_circular({"ACACCCA", "ACCCAAA", "AAACACC", "CACCCAA", "CCAAACA", "CCCAAAC", "AACACCC", "CAAACAC"}), false);
}