//
// Created by Martin on 27.06.2018.
//

#ifndef CPPFOO_STDGENCODE_H
#define CPPFOO_STDGENCODE_H

#include "AbstractGenCode.h"


class StdGenCode : public AbstractGenCode{

public:
    StdGenCode(std::vector<std::string>);

    bool test();

    bool is_circular();

private:

    bool rec_is_circular(std::vector<unsigned int>, std::string, unsigned int);
};

#endif //CPPFOO_STDGENCODE_H
