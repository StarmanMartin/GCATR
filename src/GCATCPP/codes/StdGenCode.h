//
// Created by Martin on 27.06.2018.
//

#ifndef CPPFOO_STDGENCODE_H
#define CPPFOO_STDGENCODE_H

#include "AbstractGenCode.h"


class StdGenCode : public AbstractGenCode{

public:
    StdGenCode(std::vector<std::string>);
    StdGenCode(const StdGenCode &agc);

    bool test_code();

    bool is_circular();
    bool is_cn_circular();
    bool is_self_complementary();
    bool is_comma_free();
    void shift_tuples(int shifts=1);

protected:
};

#endif //CPPFOO_STDGENCODE_H
