//
// Created by Martin on 17.07.2018.
//

#include "test_utils.cpp"


#include "../codes/StdGenCode.h"
#include "../miner/LongestPathMiner.h"

std::vector<std::vector<std::string> > run_longest_path_miner(std::vector<std::string> c) {
    StdGenCode gc(c);

    return miner::LongestPathMiner::mine_path_as_vector(&gc);
}

TEST(LongestPathMiner, simplePath) {
    test_help::test_equal_vector(run_longest_path_miner({"ACG"})[0], {"A", "CG"});
    test_help::test_equal_vector(run_longest_path_miner({"ACG"})[1], {"AC", "G"});
    test_help::test_equal_vector(run_longest_path_miner({"ACA"})[0], {"AC", "A", "CA"});
    test_help::test_equal_vector(run_longest_path_miner({"CCC"}), {});
}

TEST(LongestPathMiner, complexPaths) {
    //##1 ##2 ###3 ##4 ##5 ##6 ##7 ##8 ##9 #10 #11 #12 #13 #14 #15 #16 #17 #18 #19 #20
    //AAC AAG AAU ACC ACG ACU AGC AGG AGU AUU CCG CCU CGG CGU CUU GCU GGU GUU UCA UGA
    auto longest_path_collection = run_longest_path_miner(
            {"AAC", "AAG", "AAU", "ACC", "ACG", "ACU", "AGC", "AGG", "AGU", "AUU", "CCG", "CCU", "CGG", "CGU", "CUU",
             "GCU", "GGU", "GUU", "UCA", "UGA"});
    test_help::test_equal_vector(longest_path_collection[0], {"UC", "A", "AC", "C", "CG", "G", "CU", "U", "CA"});
    test_help::test_equal_vector(longest_path_collection[1], {"UG", "A", "AC", "C", "CG", "G", "CU", "U", "CA"});
}
