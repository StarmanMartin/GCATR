//
// Created by Martin on 17.07.2018.
//

#include "gtest/gtest.h"
#include "../codes/Acid.h"

TEST(ACIDTest, ComplimentTest) {
    EXPECT_EQ(acid::get_compliment(acid::CYTOSINE, acid::DNA), acid::GUANINE);
    EXPECT_EQ(acid::get_compliment(acid::ADENINE, acid::DNA), acid::THYMINE);
    EXPECT_EQ(acid::get_compliment(acid::ADENINE, acid::RNA), acid::URACIL);

    EXPECT_EQ(acid::get_compliment(acid::ADENINE, acid::NONE), acid::THYMINE);
    EXPECT_EQ(acid::get_compliment(acid::CYTOSINE, acid::NONE), acid::GUANINE);

}

TEST(ACIDTest, AntiCodon) {
    EXPECT_EQ(acid::get_anti_codon("ACG", acid::DNA), "CGT");
    EXPECT_EQ(acid::get_anti_codon("ACG", acid::RNA), "CGU");
    EXPECT_EQ(acid::get_anti_codon("CCC", acid::RNA), "GGG");

    EXPECT_EQ(acid::get_anti_codon("TCG", acid::RNA), "");
    EXPECT_EQ(acid::get_anti_codon("TCG AUG", acid::RNA), "");
    EXPECT_EQ(acid::get_anti_codon("TCG", acid::NONE), "");
    EXPECT_EQ(acid::get_anti_codon("TLG", acid::NONE), "");
}