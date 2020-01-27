//
// Created by martins on 05.10.19.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../sequences/Sequence.h"


TEST (SequenceObjTest, CorrectSeq) {
    std::string code_seq = "ATGCGAATG";
    Sequence a(code_seq, 3);
    EXPECT_TRUE(a.test_seq());
    EXPECT_EQ(a.get_alphabet(), "TCAG");
    EXPECT_EQ(a.get_number_tuples(), 2);
    EXPECT_EQ(a.get_tuple_count()["ATG"], 2);
    EXPECT_EQ(a.get_tuple_count()["CGA"], 1);
}

TEST (SequenceObjTest, WrongSeq) {
    {
        std::string code_seq = "ATGCGAA GT";
        Sequence a(code_seq, 3);
        EXPECT_FALSE(a.test_seq());
    }
    {
        std::string code_seq = "GT";
        Sequence a(code_seq, 3);
        EXPECT_FALSE(a.test_seq());
    }
}

TEST (SequenceObjTest, checkAcids) {
    {
        std::string code_seq = "ATGCGAAGT";
        Sequence a(code_seq, 3);
        EXPECT_TRUE(a.get_acid()==acid::acids::DNA);
    }
    {
        std::string code_seq = "GUACCGCAG";
        Sequence a(code_seq, 3);
        EXPECT_TRUE(a.test_seq());
    }
    {
        std::string code_seq = "GUACCGCAG";
        Sequence a(code_seq, 3);
        ASSERT_THAT(a.get_amino_acids(), testing::ElementsAre("Val", "Pro", "Gln" ));
    }
}