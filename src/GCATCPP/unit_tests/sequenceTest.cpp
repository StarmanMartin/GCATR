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


TEST(SequenceTest, SequenceCodeTest) {
    std::string code_seq = "ACGTCG";
    std::string seq = "ACGTCGCGACGTACGACGTCGTACTCGATGCAAGATC";
    // ACG TCG CGA CGT ACG ACG TCG TAC TCG ATG CAA GAT C";
    StdGenCode a(code_seq, 3);
    auto res = a.find_code_in_sequence(seq);
    EXPECT_EQ((int)(res.total_match_in_percent * 100), 4864);
    EXPECT_EQ(res.longest_match, 9);
    EXPECT_EQ(res.rest, "CGACGTTACATGCAAGATC");
    test_help::test_equal_vector(res.words, {"ACG", "TCG", "ACG", "ACG", "TCG", "TCG"});
    test_help::test_equal_vector(res.idx_list, {0,3,12,15,18,24});
}