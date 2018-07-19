//
// Created by Martin on 15.07.2018.
//

#include "test_utils.cpp"

#include "../codes/StdGenCode.h"
#include "../bda/BDATools.h"

std::vector<std::string> test_BDA_of_code(std::vector<std::string> c, std::vector<BDA::BDA_Rule> rules) {
    std::shared_ptr<StdGenCode> code = std::make_shared<StdGenCode>(c);

    BDA::BDATools b(code);

    for (auto rule : rules) {
        b.add_rule(rule);
    }

    return b.run_bda_for_code();

}

TEST(BDAAddRule, WrongRule) {
    std::vector<std::string> c = {"ATT"};
    std::shared_ptr<StdGenCode> code = std::make_shared<StdGenCode>(c);
    BDA::BDATools b(code);

    EXPECT_FALSE(b.add_rule(-1, 2, 'G', 'A', 'C', 'A'));
    EXPECT_FALSE(b.add_rule(0, 2, 'G', 'A', 'C', 'A'));
    EXPECT_FALSE(b.add_rule(4, 2, 'G', 'A', 'C', 'A'));
    EXPECT_FALSE(b.add_rule(1, 2, 'U', 'A', 'C', 'A'));
    EXPECT_FALSE(b.add_rule(1, 2, 'Z', 'A', 'C', 'A'));
    EXPECT_FALSE(b.add_rule(2, 2, 'G', 'A', 'C', 'A'));
}

TEST(BDAAddRule, CorrectRule) {
    std::vector<std::string> c = {"ATT"};
    std::shared_ptr<StdGenCode> code = std::make_shared<StdGenCode>(c);
    BDA::BDATools b(code);

    EXPECT_TRUE(b.add_rule(1, 2, 'G', 'A', 'C', 'A'));
    EXPECT_TRUE(b.add_rule(3, 2, 'G', 'A', 'C', 'A'));
    EXPECT_TRUE(b.add_rule(1, 2, 'T', 'A', 'C', 'A'));
}

TEST (BDATest, TwoRuleTest) {
    std::vector<BDA::BDA_Rule> rules = {};
    BDA::BDA_Rule r_1(2, 1, 'C', 'A', 'G', 'C');
    rules.push_back(r_1);
    BDA::BDA_Rule r_2(3, 2, 'G', 'A', 'C', 'A');
    rules.push_back(r_2);


    std::vector<std::string> res = {"11", "11", "11"};

    test_help::test_equal_vector<std::string>(test_BDA_of_code({"AGA", "AUA", "CAA"}, rules), res);

    res = {"00", "10", "11", "11", "11", "11", "01", "01"};
    test_help::test_equal_vector<std::string>(test_BDA_of_code({"ACC", "AAG", "AGU", "UUU", "AGU", "UUU", "GGU", "CUU"}, rules), res);
}