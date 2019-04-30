//
// Created by Martin on 2/14/2019.
//

#include "KCircular.h"

#include "Circular.h"
#include <string>
#include <iostream>
#include <regex>
#include <climits>

bool KCircular::test(AbstractCode *code, int k) {
    Circular cTester;

    auto circles = cTester.get_circles(code);

    for(const auto &circle_graph : circles) {
        if(circle_graph.get_edges().size() < (k + 1)) {
            return false;
        }
    }

    return true;
}

bool KCircular::test(AbstractCode *code) {
    Circular cTester;
    return cTester.test(code);
}