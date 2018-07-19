//
// Created by Martin on 15.07.2018.
//

#include "gtest/gtest.h"

namespace test_help {

    template<typename T>
    void test_equal_vector(std::vector<T> a, std::vector<T> b) {
        EXPECT_EQ(a.size(), b.size());
        if (a.size() == b.size()) {
            for (int i = 0; i < a.size(); ++i) {
                EXPECT_EQ(a[i], b[i]);
            }
        }
    }

}
