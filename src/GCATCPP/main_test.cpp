#include <iostream>
#include <string>
#include <sstream>

#include "codes/StdGenCode.h"

void testCode(std::vector<std::string> c, bool should_is_circle) {
    StdGenCode a (c);
    auto is_circle = a.is_circular();
    std::stringstream os;
    if(is_circle == should_is_circle) {
        for(auto word : c) {
            os << word << " ";
        }
        std::cout << os.str() << std::endl << "works is: " << is_circle << " and should " << should_is_circle << std::endl << std::endl;
        std::cout.flush();
    } else {
        for(auto word : c) {
            os << word << " ";
        }

        std::cerr << os.str() << std::endl  << "error is: " << is_circle << " and should " << should_is_circle << std::endl << std::endl;
        std::cerr.flush();
    }



}

int main() {
    std::vector<std::string> c = {"AGA", "ACA", "CAA"};
    testCode(c, false);

    c = {"AAA"};
    testCode(c, false);

    c = {"AGA", "ATA", "CAA"};
    testCode(c, true);
}