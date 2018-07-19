//
// Created by Martin on 13.07.2018.
//

#ifndef GCATCPP_BDATOOLS_H
#define GCATCPP_BDATOOLS_H

class AbstractGenCode;


#define BDA_WORD_LENGTH 3

#include <string>
#include <vector>
#include <memory>

namespace BDA {

    struct BDA_Rules {
        unsigned int i_1;
        unsigned int i_2;
        char Q_11;
        char Q_12;
        char Q_21;
        char Q_22;

        std::string name;

        BDA_Rules(unsigned int i_1, unsigned int i_2, char Q_11, char Q_12, char Q_21, char Q_22) :
                i_1(i_1-1), i_2(i_2-1), Q_11(Q_11), Q_12(Q_12), Q_21(Q_21), Q_22(Q_22) {}
    };

    typedef struct BDA_Rules BDA_Rule;

    class BDATools {
    private:
        std::vector <BDA_Rule> rules;
        std::shared_ptr <AbstractGenCode> code;

        bool validate_rule(BDA_Rule);

    public:

        BDATools(std::shared_ptr <AbstractGenCode>);

        bool add_rule(unsigned int i_1, unsigned int i_2, char Q_11, char Q_12, char Q_21, char Q_22);

        bool add_rule(BDA_Rule rule);

        std::vector <std::string> run_bda_for_code();
    };
}


#endif //GCATCPP_BDATOOLS_H
