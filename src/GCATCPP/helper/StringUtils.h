//
// Created by Martin on 2/12/2019.
//

#ifndef GCATCPP_STRINGUTILS_H
#define GCATCPP_STRINGUTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace utils {
    class StringUtils {
    public:
        static std::vector<std::string> split(const std::string &strToSplit, const char &delimeter) {
            std::stringstream ss(strToSplit);
            std::string item;
            std::vector<std::string> splitedStrings;
            while (std::getline(ss, item, delimeter)) {
                splitedStrings.push_back(item);
            }
            return splitedStrings;
        }
    };
}


#endif //GCATCPP_STRINGUTILS_H
