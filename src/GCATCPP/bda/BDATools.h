//
// Created by Martin on 13.07.2018.
//

#ifndef GCATCPP_BDATOOLS_H
#define GCATCPP_BDATOOLS_H


class AbstractTupleContainer;


#define BDA_WORD_LENGTH 3

#include <string>
#include <vector>
#include <memory>
#include "../helper/AbstractErrorManager.h"

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
                i_1(i_1 - 1), i_2(i_2 - 1), Q_11(Q_11), Q_12(Q_12), Q_21(Q_21), Q_22(Q_22) {}
    };

    typedef struct BDA_Rules BDA_Rule;

    class BDATools : public err::AbstractErrorManager {
    private:
        std::vector<BDA_Rule> rules;
        std::shared_ptr<AbstractTupleContainer> code;

        bool validate_rule(const BDA_Rule&);

    public:

        explicit BDATools(std::shared_ptr<AbstractTupleContainer>);

        bool add_rule(unsigned int i_1, unsigned int i_2, char Q_11, char Q_12, char Q_21, char Q_22);

        bool add_rule(const BDA_Rule& rule);

        std::shared_ptr<AbstractTupleContainer> get_code();

        std::vector<std::string> run_bda_for_code();

        std::vector<std::string> run_bda_for_all_rna_codons();

        std::vector<std::string> get_all_rna_codons();
    private:
        std::vector<std::string> run_bda_for_code(std::vector<std::string> code_vec);

    };
}


#endif //GCATCPP_BDATOOLS_H
