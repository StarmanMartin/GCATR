//
// Created by Martin on 2/15/2019.
//


#include "test_utils.cpp"

#include "../codes/CodeFactory.h"
#include "../graph/Graph.h"
#include <memory>


TEST(CodeFactoryTester, WrongRule) {
    std::vector<std::string> c_str = {"11011 11000"};
    std::shared_ptr<AbstractCode> code = CodeFactory::rFactor(c_str, -1);
    auto seq_str = code->as_vector();
    test_help::test_equal_vector(seq_str, {"11011", "11000"});

    c_str = {"123 213"};
    code = CodeFactory::rFactor(c_str, -1);
    EXPECT_TRUE(code->is_circular());

    c_str = {"123 213"};
    code = CodeFactory::rFactor(c_str, -1);
    graph::Graph g(*code);
    auto edges = g.get_edges();
    EXPECT_EQ(edges.size(), 4);

    c_str = {
            "000000010000000 000000110000010 000001010000100 000001100000110 000010010001000 000010100001010 000011000001100 000011100001110 000100010010000 000100110010010 000101000010100 000101100010110 000110010011000 000110100011010 000111000011100 000111100011110 001000010100000 001000110100010 001001010100100 001001110100110 001010000101000 001010100101010 001011000101100 001011100101110 001100010110000 001100110110010 001101000110100 001101100110110 001110010111000 001110110111010 001111000111100 001111100111110 010000011000000 010000111000010 010001011000100 010001111000110 010010011001000 010010111001010 010011011001100 010011111001110 010100011010000 010100111010010 010101001010100 010101101010110 010110011011000 010110111011010 010111001011100 010111101011110 011000011100000 011000111100010 011001011100100 011001111100110 011010011101000 011010111101010 011011011101100 011011111101110 011100011110000 011100111110010 011101011110100 011101111110110 011110011111000 011110111111010 011111001111100 011111101111110 100000000000001 100000100000011 100001000000101 100001110000111 100010000001001 100010110001011 100011000001101 100011110001111 100100000010001 100100100010011 100101010010101 100101110010111 100110000011001 100110110011011 100111000011101 100111110011111 101000000100001 101000100100011 101001000100101 101001100100111 101010000101001 101010110101011 101011000101101 101011110101111 101100000110001 101100100110011 101101000110101 101101100110111 101110000111001 101110100111011 101111000111101 101111110111111 110000001000001 110000101000011 110001001000101 110001101000111 110010001001001 110010101001011 110011001001101 110011101001111 110100001010001 110100101010011 110101001010101 110101101010111 110110001011001 110110101011011 110111001011101 110111101011111 111000001100001 111000101100011 111001001100101 111001101100111 111010001101001 111010101101011 111011001101101 111011101101111 111100001110001 111100101110011 111101001110101 111101101110111 111110001111001 111110101111011 111111001111101 111111101111111"};

    code = CodeFactory::rFactor(c_str, -1);
    EXPECT_FALSE(code->is_circular());
/*
    std::vector<std::string> c = {"11011", "11000"};
    code = CodeFactory::factor(c);
    EXPECT_TRUE(code->is_circular());

    c = {"110101", "11000"};
    code = CodeFactory::factor(c);
    EXPECT_FALSE(code->test_code());

    c_str = "1101011000";
    code = CodeFactory::factor(c_str, (unsigned)5);
    EXPECT_TRUE(code->is_circular());

*/
}