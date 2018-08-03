//
// Created by Martin on 21.07.2018.
//


#include "test_utils.cpp"

#include "../codes/StdGenCode.h"

TEST(SequenceTest, SequenceToVector) {
    std::string seq = "ACGTCG";
    StdGenCode a(seq, 3);

    test_help::test_equal_vector<std::string>(a.as_vector(), {"ACG", "TCG"});
}

TEST(SequenceTest, CopyConstructor) {
    std::string seq = "ACGTCG";
    StdGenCode a(seq, 3);
    StdGenCode b(a);
    EXPECT_EQ(a.get_word_length()[0], b.get_word_length()[0]);
    EXPECT_EQ(a.as_string_sequence(), b.as_string_sequence());
}
