//
// Created by Martin on 17.07.2018.
//

//
// Created by Martin on 15.07.2018.
//

#include "gtest/gtest.h"
#include "../codes/StdGenCode.h"

bool run_is_comma_free(std::vector<std::string> c) {
    StdGenCode a(c);
    return a.is_comma_free();
}

TEST (CommaFreeTest, CommaFreeCodes) {
    EXPECT_EQ(run_is_comma_free({"AUA", "CAC", "CUG", "GAG", "GUC"}), true);

    EXPECT_EQ(run_is_comma_free(
            {"AAC","AAG","AUA","AUC","AUG","CAC","CAG","CCG","CUA","CUC","CUG","GAC","GAG","GGC","GUC","GUG","UUC"}), true);
}

TEST (CommaFreeTest, NotCommaFreeCodes) {
    EXPECT_EQ(run_is_comma_free({"AGA", "AAG", "CAA"}), false);

    EXPECT_EQ(run_is_comma_free({"AAA"}), false);

    EXPECT_EQ(run_is_comma_free({"ACA", "CAU", "CUG", "GAC", "UGA"}), false);
    EXPECT_EQ(run_is_comma_free({"ACG", "AUA", "CAC", "CUG", "GAG", "GUC"}), false);
}