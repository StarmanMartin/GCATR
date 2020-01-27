//
// Created by Martin on 24.06.2019.
//

#include "test_utils.cpp"


#include "../codes/CodeFactory.h"
#include "../modification/TransformTuples.h"


TEST(ShiftTester, differentShifts) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->shift_tuples(1);
    EXPECT_EQ(code->as_string_sequence(), "CCCCGACGCCGT");

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->shift_tuples(2);
    EXPECT_EQ(code->as_string_sequence(), "CCCGACGCCGTC");

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->shift_tuples(4);
    EXPECT_EQ(code->as_string_sequence(), "CCCCGACGCCGT");

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->shift_tuples(-1);
    EXPECT_EQ(code->as_string_sequence(), "ACGCCCCCGTCG");

}

TEST(TransformTester, differentTransforms) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples("A", "T");
    EXPECT_EQ(code->as_string_sequence(), "CCCCCGTCG");

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples("AT", "TA");
    EXPECT_EQ(code->as_string_sequence(), "ACGCCCCCGTCG");

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples("ATCG", "TAGC");
    EXPECT_EQ(code->as_string_sequence(), "AGCGGCGGGTGC");


    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples("AA", "TT");
    EXPECT_EQ(code->as_string_sequence(), "ACGCCCCCGTCG");

    std::vector<std::string> code_as_vec = {"ACG", "GAT"};
    auto scode = CodeFactory::rFactor(code_as_vec, -1);
    scode->transform_tuples("ACTG", "CAGT");
    EXPECT_EQ(scode->as_string_sequence(), "CATTCG");

}

TEST(TransformTester, differentTransformsByName) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples_by_name(AT);
    EXPECT_EQ(code->as_string_sequence(), "ACGCCCCCGTCG");

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples_by_name(SW);
    EXPECT_EQ(code->as_string_sequence(), "AGCGGCGGGTGC");

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples_by_name(AGTC);
    EXPECT_EQ(code->as_string_sequence(), "AAAAATCATGAT");

}

TEST(TransformTester, TransformationLessCompare) {
    {
        TransformTuples t1("ATC", "GAT");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_TRUE(t1 < t2);
    }
    {
        TransformTuples t1("ATU", "GAT");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_FALSE(t1 < t2);
    }
    {
        TransformTuples t1("ATC", "GAC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_FALSE(t1 < t2);
    }
    {
        TransformTuples t1("ATUCC", "GATGT");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_FALSE(t1 < t2);
    }
}

TEST(TransformTester, TransformationGreaterCompare) {
    {
        TransformTuples t2("ATC", "GAT");
        TransformTuples t1("CGAT", "TCGA");

        EXPECT_TRUE(t1 > t2);
    }
    {
        TransformTuples t2("ATU", "GAT");
        TransformTuples t1("CGAT", "TCGA");

        EXPECT_FALSE(t1 > t2);
    }
    {
        TransformTuples t2("ATC", "GAC");
        TransformTuples t1("CGAT", "TCGA");

        EXPECT_FALSE(t1 > t2);
    }
    {
        TransformTuples t2("ATUCC", "GATGT");
        TransformTuples t1("CGAT", "TCGA");

        EXPECT_FALSE(t1 > t2);
    }
}

TEST(TransformTester, TransformationCompare) {
    {
        TransformTuples t1("ATCG", "GATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_TRUE(t1 == t2);
    }
    {
        TransformTuples t1("ATCG", "GATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_TRUE(t1 >= t2);
    }
    {
        TransformTuples t1("ATCG", "GATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_TRUE(t1 <= t2);
    }
    {
        TransformTuples t1("ATCG", "GATC");
        TransformTuples t2("CGAT", "ATCG");

        EXPECT_TRUE(t1 != t2);
    }
    {
        TransformTuples t1("TCG", "GATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_FALSE(t1 == t2);
    }
    {
        TransformTuples t1("ATCG", "GCTC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_FALSE(t1 == t2);
    }
}

TEST(TransformTester, TransformationFind) {
    {
        auto t1 = TransformTuples::find_transformation_from_sequences("ATCG", "GATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_TRUE(t1 == t2);
    }
    {
        auto t1 = TransformTuples::find_transformation_from_sequences("ATCG", "GATC");
        TransformTuples t2("CGAT", "ATCG");

        EXPECT_TRUE(t1 != t2);
    }
    {
        auto t1 = TransformTuples::find_transformation_from_sequences("TCG", "GATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_FALSE(t1 == t2);
    }
    {
        auto t1 = TransformTuples::find_transformation_from_sequences("ATCG", "GCTC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_FALSE(t1 == t2);
    }
    {
        auto t1 = TransformTuples::find_transformation_from_sequences("ATATCGATCGCGATCG", "GAGATCGATCTCGATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_TRUE(t1 == t2);
    }
    {
        auto t1 = TransformTuples::find_transformation_from_sequences("TTATCGATCGCGATCG", "GAGATCGATCTCGATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_FALSE(t1 == t2);
    }
}