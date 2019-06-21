//
// Created by Martin on 24.06.2019.
//

#include "test_utils.cpp"


#include "../codes/CodeFactory.h"



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
    code->transform_tuples({"AT"});
    EXPECT_EQ(code->as_string_sequence(), "TCGTCGCCGCCC");

    code = CodeFactory::factorGenCode(code_text);
    code->transform_tuples({"ATA"});
    EXPECT_EQ(code->as_string_sequence(), "TCGACGCCGCCC");

    code = CodeFactory::factorGenCode(code_text);
    code->transform_tuples({"ATA", "CGC"});
    EXPECT_EQ(code->as_string_sequence(), "TGCAGCGGCGGG");

}