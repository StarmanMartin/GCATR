//
// Created by martins on 14.03.20.
//

#include "gtest/gtest.h"

#include "../miner/kCircularityMiner.h"
#include "../codes/CodeFactory.h"

TEST(KCircular, minerTests) {
    {
        std::string code = "AA";
        auto c = CodeFactory::factor(code);
        EXPECT_EQ(1, miner::kCircularityMiner::mine_k_value(c.get()));
    }
    {
        std::string code = "ACG CGA";
        auto c = CodeFactory::factor(code);
        EXPECT_EQ(1, miner::kCircularityMiner::mine_k_value(c.get()));
    }
    {
        std::string code = "ACG";
        auto c = CodeFactory::factor(code);
        EXPECT_EQ(-1, miner::kCircularityMiner::mine_k_value(c.get()));
    }
    {
        std::string code = "ACG GTC TCT TAC";
        auto c = CodeFactory::factor(code);
        EXPECT_EQ(2, miner::kCircularityMiner::mine_k_value(c.get()));
    }
    {
        std::string code = "ACGC GCTC TCAC";
        auto c = CodeFactory::factor(code);
        EXPECT_EQ(3, miner::kCircularityMiner::mine_k_value(c.get()));
    }
    {
        std::string code = "ACGC GCTC TCAC CGCT";
        auto c = CodeFactory::factor(code);
        EXPECT_EQ(1, miner::kCircularityMiner::mine_k_value(c.get()));
    }
    {
        std::string code = "ACGC GCTC TCAC AAAA";
        auto c = CodeFactory::factor(code);
        EXPECT_EQ(1, miner::kCircularityMiner::mine_k_value(c.get()));
    }

}

TEST(KCircular, testerTests) {
    {
        std::string code = "AA";
        auto c = CodeFactory::factor(code);
        EXPECT_TRUE(c->is_k_circular(1));
    }
    {
        std::string code = "ACG CGA";
        auto c = CodeFactory::factor(code);
        EXPECT_TRUE(c->is_k_circular(1));
    }
    {
        std::string code = "ACG";
        auto c = CodeFactory::factor(code);
        EXPECT_FALSE(c->is_k_circular(1));
    }
    {
        std::string code = "ACG GTC TCT TAC";
        auto c = CodeFactory::factor(code);
        EXPECT_TRUE(c->is_k_circular(2));
    }
    {
        std::string code = "ACGC GCTC TCAC";
        auto c = CodeFactory::factor(code);
        EXPECT_TRUE(c->is_k_circular(3));
    }
    {
        std::string code = "ACGC GCTC TCAC CGCT";
        auto c = CodeFactory::factor(code);
        EXPECT_TRUE(c->is_k_circular(1));
    }

}
