//
// Created by Martin on 24.06.2019.
//

#include "test_utils.cpp"


#include "../codes/CodeFactory.h"
#include "../modification/TransformTuples.h"


TEST(ShiftTester, differentShifts) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::factorGenCode(code_text);
    code->shift_tuples(1);
    EXPECT_EQ(code->as_string_sequence(), "CGACGTCGCCCC");

    code = CodeFactory::factorGenCode(code_text);
    code->shift_tuples(2);
    EXPECT_EQ(code->as_string_sequence(), "GACGTCGCCCCC");

    code = CodeFactory::factorGenCode(code_text);
    code->shift_tuples(4);
    EXPECT_EQ(code->as_string_sequence(), "CGACGTCGCCCC");

    code = CodeFactory::factorGenCode(code_text);
    code->shift_tuples(-1);
    EXPECT_EQ(code->as_string_sequence(), "ACGTCGCCGCCC");

}


TEST(TransformTester, differentTransforms) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::factorGenCode(code_text);
    code->transform_tuples("A", "T");
    EXPECT_EQ(code->as_string_sequence(), "TCGTCGCCGCCC");

    code = CodeFactory::factorGenCode(code_text);
    code->transform_tuples("AT", "TA");
    EXPECT_EQ(code->as_string_sequence(), "TCGACGCCGCCC");

    code = CodeFactory::factorGenCode(code_text);
    code->transform_tuples("ATCG", "TAGC");
    EXPECT_EQ(code->as_string_sequence(), "TGCAGCGGCGGG");

}

TEST(TransformTester, differentTransformsByName) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::factorGenCode(code_text);
    code->transform_tuples_by_name(AT);
    EXPECT_EQ(code->as_string_sequence(), "TCGACGCCGCCC");

    code = CodeFactory::factorGenCode(code_text);
    code->transform_tuples_by_name(SW);
    EXPECT_EQ(code->as_string_sequence(), "TGCAGCGGCGGG");

    code = CodeFactory::factorGenCode(code_text);
    code->transform_tuples_by_name(AGTC);
    EXPECT_EQ(code->as_string_sequence(), "GATCATAATAAA");

}

TEST(TransformTester, TransformationCompare) {
    {
        TransformTuples t1("ATCG", "GATC");
        TransformTuples t2("CGAT", "TCGA");

        EXPECT_TRUE(t1 == t2);
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