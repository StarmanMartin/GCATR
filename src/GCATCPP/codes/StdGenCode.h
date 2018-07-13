//
// Created by Martin on 27.06.2018.
//

#ifndef CPPFOO_STDGENCODE_H
#define CPPFOO_STDGENCODE_H

#include "AbstractGenCode.h"


class StdGenCode : public AbstractGenCode{

public:
    StdGenCode(std::vector<std::string>);

    bool test_code();

    virtual bool is_circular();
    virtual void shift_tuples(int shifts=1);
};

#endif //CPPFOO_STDGENCODE_H
