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
#define I "Id"

#define TransformationNameList {SW,YR,KM,AT,CG,ACTG,AGTC,I}
#define KleinFourTransformationNameList {SW,YR,KM,I}

#define COMPARE_E 0b001u
#define COMPARE_LE 0b011u
#define COMPARE_L 0b010u
#define COMPARE_GE 0b101u
#define COMPARE_G 0b100u


class TransformTuples : public AbstractModifier {
public:
    explicit TransformTuples(const std::string& from_rule, const std::string& to_rule);
    explicit TransformTuples(const std::string& names, acid::acids acid);


    std::vector<std::string> modify(AbstractCode *code) override;

    std::string modify_word(std::string word) override;
    std::string getTransformationName(acid::acids acid);
    std::string getKleinFourTransformationName(acid::acids acid);

    friend bool operator== (const TransformTuples &c1, const TransformTuples &c2);
    friend bool operator!= (const TransformTuples &c1, const TransformTuples &c2);
    friend bool operator> (const TransformTuples &c1, const TransformTuples &c2);
    friend bool operator>= (const TransformTuples &c1, const TransformTuples &c2);
    friend bool operator< (const TransformTuples &c1, const TransformTuples &c2);
    friend bool operator<= (const TransformTuples &c1, const TransformTuples &c2);

    static TransformTuples find_transformation_from_sequences(const std::string &seq_1, const std::string &seq_2);

private:
    bool has_error = false;
    std::vector<std::string> rule_set;
    std::map<size_t, char> replacements;

    bool compare_to(const TransformTuples &c2, size_t compare_type) const;

    void transform_word(std::string &word);

    void find_replacements(const std::string &word, char from, char to);

    static std::vector<std::string> transformation_by_name(const std::string &name, const acid::acids &acid=acid::acids::RNA) {
        std::string baseTU;
        if (acid == acid::acids::DNA) {
            baseTU = "T";
        } else if (acid == acid::acids::RNA) {
            baseTU = "U";
        } else {
            return {"",""};
        }

        if (name == I) {
            // (A, T,C,G) -> (T, A, G,C)
            return {"A" + baseTU + "CG",    "A" + baseTU + "CG"};
        }
        if (name == SW || name == "orc") {
            // (A, T,C,G) -> (T, A, G,C)
            return {"A" + baseTU + "CG",     baseTU + "AGC"};
        }
        if (name == YR || name == "orp") {
            // (A, T,C,G) -> (G,C, T,A)
            return {"A" + baseTU + "CG",    "GC" + baseTU + "A"};
        }
        if (name == KM || name == "orr") {
            // (A, T,C,G) -> (C, G, A, T)
            return {"A" + baseTU + "CG",    "CGA" + baseTU};
        }
        if (name == AT) {
            // (A, T,C,G) -> (T, A,C,G).
            return {"A" + baseTU + "CG",    baseTU + "ACG"};
        }
        if (name == CG) {
            // (A, T,C,G) -> (A, T, G,C).
            return {"A" + baseTU + "CG",    "A" + baseTU + "GC"};
        }
        if (name == ACTG) {
            // (A, T,C,G) -> (C, G, T,A).
            return {"A" + baseTU + "CG",    "CG" + baseTU + "A"};
        }
        if (name == AGTC) {
            // (A, T,C,G) -> (G,C, A, T).
            return {"A" + baseTU + "CG",    "GCA" + baseTU};
        }

        return {"", ""};
    }
};


#endif //GCATCPP_TRANSFORMTUPLES_H
