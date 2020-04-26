//
// Created by Martin on 24.06.2019.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../codes/CodeFactory.h"


TEST(ShiftTester, differentShifts) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->shift_tuples(1);
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("CGA", "CGT", "CGC", "CCC" ));

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->shift_tuples(2);
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("GAC", "GTC", "GCC", "CCC" ));

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->shift_tuples(4);
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("CGA", "CGT", "CGC", "CCC"));

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->shift_tuples(-1);
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("GAC", "GTC", "GCC", "CCC" ));
    {
        std::vector<std::string> cv = {"ACGACG"};
        auto n_code = CodeFactory::rFactor(cv, 1);
        n_code->shift_tuples(1);
        ASSERT_THAT(n_code->get_tuples(), testing::ElementsAre("A", "C", "G", "A", "C", "G"));
    }
}

TEST(TransformTester, differentTransforms) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples("A", "T");
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("TCG", "TCG", "CCG", "CCC" ));

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples("AT", "TA");
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("TCG", "ACG", "CCG", "CCC" ));

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples("ATCG", "TAGC");
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("TGC", "AGC", "GGC", "GGG" ));


    code = CodeFactory::rFactorTypesCodonCode({code_text});
    ASSERT_ANY_THROW(code->transform_tuples("AA", "TT"));

    std::vector<std::string> code_as_vec = {"ACG", "GAT"};
    auto scode = CodeFactory::rFactor(code_as_vec);
    scode->transform_tuples("ACTG", "CAGT");
    ASSERT_THAT(scode->get_tuples(), testing::ElementsAre("CAT", "TCG" ));
    {
        std::vector<std::string> cv = {"asd"};
        auto n_code = CodeFactory::rFactor(cv, 1);
        EXPECT_ANY_THROW(n_code->transform_tuples("k€.€", "1234"));
        EXPECT_ANY_THROW(n_code->transform_tuples("k€$€", "1234"));
        EXPECT_ANY_THROW(n_code->transform_tuples("k€^€", "1234"));
        EXPECT_ANY_THROW(n_code->transform_tuples("k€(€", "1234"));
        EXPECT_ANY_THROW(n_code->transform_tuples("k€)€", "1234"));
        EXPECT_ANY_THROW(n_code->transform_tuples("k€[€", "1234"));
        EXPECT_ANY_THROW(n_code->transform_tuples("k€]€", "1234"));
        EXPECT_ANY_THROW(n_code->transform_tuples("k€{€", "1234"));
        EXPECT_ANY_THROW(n_code->transform_tuples("k€}€", "1234"));
    }

}

TEST(TransformTester, differentTransformsByName) {
    std::string code_text = "ACG TCG CCG CCC";
    auto code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples_by_name(AT);
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("TCG", "ACG", "CCG", "CCC" ));

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples_by_name(SW);
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("TGC", "AGC", "GGC", "GGG" ));

    code = CodeFactory::rFactorTypesCodonCode({code_text});
    code->transform_tuples_by_name(AGTC);
    ASSERT_THAT(code->get_tuples(), testing::ElementsAre("GAT", "CAT", "AAT", "AAA" ));

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
        EXPECT_ANY_THROW(TransformTuples t1("ATUCC", "GATGT"));
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
        EXPECT_ANY_THROW(TransformTuples t2("ATUCC", "GATGT"));
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
        EXPECT_ANY_THROW(TransformTuples t1("TCG", "GATC"));
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