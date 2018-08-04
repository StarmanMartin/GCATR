cmake_minimum_required(VERSION 3.10)
project(GCATCPP)

set(CMAKE_CXX_STANDARD 11)

enable_testing()


set(gteat_SRC_DIR ${CMAKE_SOURCE_DIR}/libs/googletest-master/googletest)

add_subdirectory(libs/googletest-master/googletest)

include_directories(${gteat_SRC_DIR}/include ${gteat_SRC_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

set(SOURCE_FILES main_test.cpp
        codes/AbstractGenCode.cpp codes/AbstractGenCode.h codes/StdGenCode.cpp codes/StdGenCode.h codes/Acid.cpp codes/Acid.h
        tester/AbstractTester.cpp tester/AbstractTester.h tester/Circular.cpp tester/Circular.h tester/C_n.cpp tester/C_n.h
        tester/SelfComplimentary.cpp tester/SelfComplimentary.h tester/CommaFree.cpp tester/CommaFree.h
        modification/AbstractModifier.cpp modification/AbstractModifier.h modification/ShiftTuples.cpp modification/ShiftTuples.h
        bda/BDATools.cpp bda/BDATools.h
        helper/AbstractErrorManager.cpp helper/AbstractErrorManager.h
        miner/CircleMiner.cpp miner/CircleMiner.h
        graph/Edge.cpp graph/Edge.h graph/Vertex.cpp graph/Vertex.h graph/Graph.cpp graph/Graph.h miner/LongestPathMiner.cpp miner/LongestPathMiner.h graph/C3Graph.cpp graph/C3Graph.h)

set(SOURCE_TEST_FILES unit_tests/test_utils.cpp
        unit_tests/circular.cpp unit_tests/codeTestTest.cpp unit_tests/bdaTest.cpp unit_tests/test_utils.cpp
        unit_tests/cnCircularTest.cpp unit_tests/acidTest.cpp unit_tests/selfComplementaryTest.cpp unit_tests/commaFreeTest.cpp
        unit_tests/minerCircularTest.cpp unit_tests/graphTest.cpp unit_tests/minerPathTest.cpp unit_tests/sequenceTest.cpp unit_tests/c3GraphTest.cpp)

set(CURRENT_TEST_FILES unit_tests/test_utils.cpp unit_tests/c3GraphTest.cpp)


add_executable(MainTest ${SOURCE_FILES} ${SOURCE_TEST_FILES})
add_executable(CurrentTest ${SOURCE_FILES} ${CURRENT_TEST_FILES})

target_link_libraries(MainTest gtest)
target_link_libraries(CurrentTest gtest)