//
// Created by Martin on 07.02.2019.
//

#include "test_utils.cpp"

#include "../codes/CodeFactory.h"
#include <memory>


TEST(BinaryCodesTest, WrongRule) {
    std::string c_str = "11011 11000";
    std::shared_ptr<AbstractCode> code = CodeFactory::factor(c_str);
    EXPECT_TRUE(code->is_circular());

    std::vector<std::string> c = {"11011", "11000"};
    code = CodeFactory::factor(c);
    EXPECT_TRUE(code->is_circular());

    c = {"110101", "11000"};
    code = CodeFactory::factor(c);
    EXPECT_TRUE(code == nullptr);

    c_str = "1101011000";
    code = CodeFactory::factor(c_str, (unsigned)5);
    EXPECT_TRUE(code == nullptr);

}