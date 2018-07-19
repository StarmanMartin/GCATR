//
// Created by Martin on 17.07.2018.
//

#include "test_utils.cpp"


#include "../codes/StdGenCode.h"
#include "../miner/CircleMiner.h"

std::vector<std::vector<std::string> > run_miner(std::vector<std::string> c) {
    StdGenCode gc(c);
    auto a = miner::CircleMiner::mine_path_as_vector(&gc);
    return a;
}

TEST(CircularMiner, indentetyCircular) {
    test_help::test_equal_vector(run_miner({"AAA"})[0], {"A", "AA", "A"});

    test_help::test_equal_vector(run_miner({"CCC"})[0], {"C", "CC", "C"});
}

TEST(CircularMiner, oneCircular) {
    test_help::test_equal_vector(run_miner({"ACA", "CAA"})[0], {"A", "CA", "A"});
    test_help::test_equal_vector(run_miner({"ACG", "CGA"})[0], {"CG", "A", "CG"});
    test_help::test_equal_vector(run_miner({"ACG", "ACG"}), {});
}

TEST(CircularMiner, twoCircular) {
    auto a = run_miner({"AAC", "ACC", "CUG", "UGA", "UGC"});
    test_help::test_equal_vector(a[0], {"UG", "A", "AC","C", "UG"});
    test_help::test_equal_vector(a[1], {"UG", "C", "UG"});
}
