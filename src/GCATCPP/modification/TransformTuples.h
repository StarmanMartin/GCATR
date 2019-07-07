//
// Created by martins on 18.06.19.
//

#ifndef GCATCPP_TRANSFORMTUPLES_H
#define GCATCPP_TRANSFORMTUPLES_H


#include "AbstractModifier.h"
#include "../codes/Acid.h"

#define SW "SW"
#define YR "YR"
#define KM "KM"
#define AT "AT"
#define CG "CG"
#define ACTG "ACTG"
#define AGTC "AGTC"


class TransformTuples : public AbstractModifier {
public:
    explicit TransformTuples(const std::string& from_rule, const std::string& to_rule);
    explicit TransformTuples(const std::string& names, acid::acids acid);


    std::vector<std::string> modify(AbstractCode *code) override;

    std::string modify_word(std::string word) override;

    static std::vector<std::string> transformation_by_name(const std::string &name, const acid::acids &acid) {
        std::string baseTU;
        if (acid == acid::acids::DNA) {
            baseTU = "T";
        } else if (acid == acid::acids::RNA) {
            baseTU = "U";
        } else {
            return {};
        }

        if (name == SW || name == "orc") {
            // (A, T,C,G) -> (T, A, G,C)
            return {"A" + baseTU + "A", "CGC"};
        }
        if (name == YR || name == "orp") {
            // (A, T,C,G) -> (G,C, T,A)
            return {"AGA", "C" + baseTU + "C"};
        }
        if (name == KM || name == "orr") {
            // (A, T,C,G) -> (C, G, A, T)
            return {"ACA", "G" + baseTU + "G"};
        }
        if (name == AT) {
            // (A, T,C,G) -> (T, A,C,G).
            return {"A" + baseTU + "A"};
        }
        if (name == CG) {
            // (A, T,C,G) -> (A, T, G,C).
            return {"CGC"};
        }
        if (name == ACTG) {
            // (A, T,C,G) -> (C, G, T,A).
            return {"AC" + baseTU + "GA"};
        }
        if (name == AGTC) {
            // (A, T,C,G) -> (G,C, A, T).
            return {"AG" + baseTU + "CA"};
        }

        return {};
    }

private:
    std::vector<std::string> rule_set;
    std::map<size_t, char> replacements;

    void transform_word(std::string &word);

    void find_replacements(const std::string &word, const std::string &rule);
};


#endif //GCATCPP_TRANSFORMTUPLES_H
