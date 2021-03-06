//
// Created by Martin on 17.07.2018.
//

#include "./test_utils.cpp"
#include "../codes/Acid.h"
#include "../codes/StdGenCode.h"
#include "../codes/CodeFactory.h"

TEST(ACIDTest, ComplimentTest) {
    EXPECT_EQ(acid::get_compliment(acid::CYTOSINE, acid::DNA), acid::GUANINE);
    EXPECT_EQ(acid::get_compliment(acid::ADENINE, acid::DNA), acid::THYMINE);
    EXPECT_EQ(acid::get_compliment(acid::ADENINE, acid::RNA), acid::URACIL);

    EXPECT_EQ(acid::get_compliment(acid::ADENINE, acid::NONE), acid::THYMINE);
    EXPECT_EQ(acid::get_compliment(acid::CYTOSINE, acid::NONE), acid::GUANINE);

}

TEST(ACIDTest, AntiCodon) {
    EXPECT_EQ(acid::get_anti_codon("ACG", acid::DNA), "CGT");
    EXPECT_EQ(acid::get_anti_codon("ACG", acid::RNA), "CGU");
    EXPECT_EQ(acid::get_anti_codon("CCC", acid::RNA), "GGG");

    EXPECT_EQ(acid::get_anti_codon("TCG", acid::RNA), "");
    EXPECT_EQ(acid::get_anti_codon("TCG AUG", acid::RNA), "");
    EXPECT_EQ(acid::get_anti_codon("TCG", acid::NONE), "");
    EXPECT_EQ(acid::get_anti_codon("TLG", acid::NONE), "");
    EXPECT_EQ(acid::get_anti_codon("A22", acid::NONE), "");
}

TEST(ACIDTest, AcidTranslation) {
    std::string seq = "CUAUGA";
    StdGenCode a(seq, 3);
    auto acids = a.get_amino_acids();
    std::stringstream ss;
    for(const auto &c : acids) {
        ss << c;
    }

    EXPECT_EQ(ss.str(), "LeuStop");

    ss.clear();
    ss.str("");
    a.setTranslTableByName("The Yeast Mitochondrial Code");
    acids = a.get_amino_acids();
    for(const auto &c : acids) {
        ss << c;
    }

    EXPECT_EQ(ss.str(), "ThrTrp");

    ss.clear();
    ss.str("");
    a.setTranslTableByIdx(10);
    acids = a.get_amino_acids();
    for(const auto &c : acids) {
        ss << c;
    }

    EXPECT_EQ(ss.str(), "LeuCys");
}

TEST(ACIDTest, AcidTranslationSet) {
    {
        std::vector<std::string>  code_vec = {"CUAUCUUCCUCAUGA"};
        auto a = CodeFactory::rFactorTypesCodonCode(code_vec);
        a->setTranslTableByIdx(1);
        auto acids = a->get_a_set_amino_acids();
        std::stringstream ss;
        for (const auto &c : acids) {
            ss << c;
        }
        EXPECT_EQ(ss.str(), "LeuSerStop");
        EXPECT_TRUE(a->is_translatable());

        acids = a->get_amino_acids();
        ss.clear();
        ss.str("");
        for(const auto &cd : acids) {
            ss << cd;
        }

        EXPECT_EQ(ss.str(), "LeuSerSerSerStop");
    }


    std::vector<std::string> code_gen_vec({"ACG CG"});
    std::vector<std::string> code_vec({"110 101 100"});

    auto b = CodeFactory::rFactorGenCode(code_gen_vec);
    auto c = CodeFactory::rFactor(code_vec);

    EXPECT_FALSE(b->is_translatable());
    EXPECT_FALSE(c->is_translatable());


}