//
// Created by Martin on 15.07.2018.
//

#include "test_utils.cpp"
#include "../codes/StdGenCode.h"

bool _is_cn_circular(std::vector<std::string> c) {
    StdGenCode a(c);
    return a.is_cn_circular();
}

TEST (CircularCnTest, KeepCode) {
    std::vector<std::string> c = {"AGA", "AUA", "CAA"};
    StdGenCode a(c);
    a.is_cn_circular();
   test_help::test_equal_vector<std::string>(a.as_vector(), {"AGA", "AUA", "CAA"});
}

TEST (CircularCnTest, CircularCodes) {
    EXPECT_EQ(_is_cn_circular({"AGA", "AUA", "CAA"}), true);

    EXPECT_EQ(_is_cn_circular(
           {"AAC","AAG","AAU","ACC","ACG","ACU","AGC","AGG","AGU","AUU","CCG","CCU","CGG","CGU","CUU","GCU","GGU","GUU","UCA","UGA"}), true);
    EXPECT_EQ(_is_cn_circular(
            {"ACA","AGA","AUA","CCA","CGA","CUA","GCA","GGA","GUA","UUA","CGC","CUC","GGC","GUC","UUC","CUG","GUG","UUG","CAU","GAU"}), true);

}

TEST (CircularCnTest, NotCircularCodes) {
    EXPECT_EQ(_is_cn_circular({"AAG","ACC","ACU","AUG","GAG","GCA","GGU","GUU","UAG","UCA","UCC","UCU","UGC"}), false);

    EXPECT_EQ(_is_cn_circular({"AAA"}), false);

    EXPECT_EQ(_is_cn_circular({"ACA", "CAU", "CUG", "GAC", "UGA"}), false);
}