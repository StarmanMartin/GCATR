#include <Rcpp.h>
using namespace Rcpp;

#include "GCATCPP/geneticCode/CodonClusteringAlgorithm.h"
#include "GCATCPP/geneticCode/CodonTranslTables.h"

#include "RAdapterUtils.h"

//' To calculate the average conductance of a translation table
//'
//' This function calculates the average conductance for a selected genetic translation table.
//' The conductance is a number which reflects the robustness of a genetic translation table.
//' The conductance the ration of the codons translating one amino acid which differ in only one position and the
//' codons translating the same amino acid but differ in more then one position.
//'
//' @param codeName a String, the name of the genetic translation table. (see \link{print_all_translation_tables})
//' @param acid a String, is optional: DNA or RNA
//'
//' @return A Number, the average conductance of a genetic translation table
//'
//' @examples
//' ac = get_average_conductance_of_code("The Standard Code")
//' ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
//' @export 
// [[Rcpp::export]]
double get_average_conductance_of_code(std::string codeName, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByName(codeName, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_average_conductance();
}

//' To calculate the max conductance of a translation table
//'
//' This function calculates the max conductance for a selected genetic translation table.
//' The conductance is a number which reflects the robustness of a genetic translation table.
//' The conductance the ration of the codons translating one amino acid which differ in only one position and the
//' codons translating the same amino acid but differ in more then one position.
//'
//' @param codeName a String, the name of the genetic translation table. (see \link{print_all_translation_tables})
//' @param acid a String, is optional: DNA or RNA
//'
//' @return A Number, the max conductance of a genetic translation table
//'
//' @examples
//' ac = get_average_conductance_of_code("The Standard Code")
//' ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
//' @export
// [[Rcpp::export]]
double get_max_conductance_of_code(std::string codeName, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByName(codeName, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_max_conductance();
}

//' To calculate the min conductance of a translation table
//'
//' This function calculates the min conductance for a selected genetic translation table.
//' The conductance is a number which reflects the robustness of a genetic translation table.
//' The conductance the ration of the codons translating one amino acid which differ in only one position and the
//' codons translating the same amino acid but differ in more then one position.
//'
//' @param codeName a String, the name of the genetic translation table. (see \link{print_all_translation_tables})
//' @param acid a String, is optional: DNA or RNA
//'
//' @return A Number, the min conductance of a genetic translation table
//'
//' @examples
//' ac = get_average_conductance_of_code("The Standard Code")
//' ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
//' @export
// [[Rcpp::export]]
double get_min_conductance_of_code(std::string codeName, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByName(codeName, RAdapterUtils::string_to_acid(acid));
  
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_min_conductance();
}

//' To calculate the average conductance of a translation table
//'
//' This function calculates the average conductance for a selected genetic translation table.
//' The conductance is a number which reflects the robustness of a genetic translation table.
//' The conductance the ration of the codons translating one amino acid which differ in only one position and the
//' codons translating the same amino acid but differ in more then one position.
//'
//' @param codeIdx a Number, the index of the genetic translation table. (see \link{print_all_translation_tables})
//' @param acid a String, is optional: DNA or RNA
//'
//' @return A Number, the average conductance of a genetic translation table
//'
//' @examples
//' ac = get_average_conductance_of_code("The Standard Code")
//' ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
//' @export
// [[Rcpp::export]]
double get_average_conductance_of_codeidx(int codeIdx, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(codeIdx, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_average_conductance();
}

//' To calculate the max conductance of a translation table
//'
//' This function calculates the max conductance for a selected genetic translation table.
//' The conductance is a number which reflects the robustness of a genetic translation table.
//' The conductance the ration of the codons translating one amino acid which differ in only one position and the
//' codons translating the same amino acid but differ in more then one position.
//'
//' @param codeIdx a Number, the index of the genetic translation table. (see \link{print_all_translation_tables})
//' @param acid a String, is optional: DNA or RNA
//'
//' @return A Number, the max conductance of a genetic translation table
//'
//' @examples
//' ac = get_average_conductance_of_code("The Standard Code")
//' ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
//' @export
// [[Rcpp::export]]
double get_max_conductance_of_codeidx(int codeIdx, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(codeIdx, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_max_conductance();
}

//' To calculate the min conductance of a translation table
//'
//' This function calculates the min conductance for a selected genetic translation table.
//' The conductance is a number which reflects the robustness of a genetic translation table.
//' The conductance the ration of the codons translating one amino acid which differ in only one position and the
//' codons translating the same amino acid but differ in more then one position.
//'
//' @param codeIdx a Number, the index of the genetic translation table. (see \link{print_all_translation_tables})
//' @param acid a String, is optional: DNA or RNA
//'
//' @return A Number, the min conductance of a genetic translation table
//'
//' @examples
//' ac = get_average_conductance_of_code("The Standard Code")
//' ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
//' @export
// [[Rcpp::export]]
double get_min_conductance_of_codeidx(int codeIdx, std::string acid="DNA") {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(codeIdx, RAdapterUtils::string_to_acid(acid));
  gen_codes::CodonClusteringAlgorithm cca(code);
  
  return cca.get_min_conductance();
}


//' The Genetic Codes
//' 
//' \emph{print_all_translation_tables} prints a list of the genetic codes contained by this project. The list includes names and indexes of the codes.
//' 
//' The Standard Code(transl_table=1)\cr
//' The Vertebrate Mitochondrial Code(transl_table=2)\cr
//' The Yeast Mitochondrial Code(transl_table=3)\cr
//' The Mold, Protozoan, and Coelenterate Mitochondrial Code and the Mycoplasma/Spiroplasma Code(transl_table=4)\cr
//' The Invertebrate Mitochondrial Code(transl_table=5)\cr
//' The Ciliate, Dasycladacean and Hexamita Nuclear Code(transl_table=6)\cr
//' The Echinoderm and Flatworm Mitochondrial Code(transl_table=9)\cr
//' The Euplotid Nuclear Code(transl_table=10)\cr
//' The Bacterial, Archaeal and Plant Plastid Code(transl_table=11)\cr
//' The Alternative Yeast Nuclear Code(transl_table=12)\cr
//' The Ascidian Mitochondrial Code(transl_table=13)\cr
//' The Alternative Flatworm Mitochondrial Code(transl_table=14)\cr
//' Ter Chlorophycean Mitochondrial Code(transl_table=16)\cr
//' Trematode Mitochondrial Code(transl_table=21)\cr
//' Scenedesmus obliquus Mitochondrial Code(transl_table=22)\cr
//' Thraustochytrium Mitochondrial Code(transl_table=23)\cr
//' Pterobranchia Mitochondrial Code(transl_table=24)\cr
//' Candidate Division SR1 and Gracilibacteria Code(transl_table=25)\cr
//' Pachysolen tannophilus Nuclear Code(transl_table=26)\cr
//' Karyorelict Nuclear(transl_table=27)\cr
//' Condylostoma Nuclear(transl_table=28)\cr
//' Mesodinium Nuclear(transl_table=29)\cr
//' Peritrich Nuclear(transl_table=30)\cr
//' Blastocrithidia Nuclear(transl_table=31)\cr
//' \cr Source:\cr
//' \emph{Compiled by Andrzej (Anjay) Elzanowski and Jim Ostell at National Center for Biotechnology Information (NCBI), Bethesda, Maryland, U.S.A.}\cr
//' \emph{Last update of the Genetic Codes: Nov. 18, 2016}
//' \emph{\link{https://www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi}}
//' 
//' @seealso \link{genetic_codes_by_index}, \link{genetic_codes_by_name}
//'
//' @examples
//' print_all_translation_tables()
//' 
//' @export 
// [[Rcpp::export]]
void print_all_translation_tables() {
  auto code = gen_codes::CodonTranslTables::getInstance().getAllCodesText();
  Rcpp::Rcout << code;
}

//' The Genetic Codes
//' 
//' \emph{genetic_codes_by_index} returns a list representing a Genetic Code. The list contains two arrays, one array of the codons and one array of the translated amino acids in the same order.
//' \cr Source:\cr
//' \emph{Compiled by Andrzej (Anjay) Elzanowski and Jim Ostell at National Center for Biotechnology Information (NCBI), Bethesda, Maryland, U.S.A.}\cr
//' \emph{Last update of the Genetic Codes: Nov. 18, 2016}
//' \emph{\link{https://www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi}}
//'
//' \emph{codons} all codons as strings.\cr
//' \emph{amino_acids} the translated aminop acids in same order.\cr
//' 
//' @param idx the index of a Genetic Code table as int. (check \link{print_all_translation_table})
//'
//' @return Returns a named List with all codons and the translated amino acids:\cr
//' @examples
//' (code <- genetic_codes_by_index(1))
//' 
//' @export 
// [[Rcpp::export]]
List genetic_codes_by_index(int idx) {
  auto code = gen_codes::CodonTranslTables::getInstance().getCodeByIndex(idx);
  std::vector<std::string> codons(code.size() / 2);
  std::vector<std::string> amino_acids(code.size() / 2);
  gen_codes::CodonTranslTables::getInstance().print_errors();
  
  int i = 0;
  for(const auto& words: code) {
    if(i % 2 == 0) {
      codons[i/2] = words;
    } else {
      amino_acids[i/2] = words;
    }
    ++i;
  }
  
  return Rcpp::List::create(Rcpp::Named("codons") = codons,
                            Rcpp::Named("amino_acids") = amino_acids);
}

//' The Genetic Codes
//' 
//' \emph{genetic_codes_by_name} returns a list representing a Genetic Code. The list contains two arrays, one array of the codons and one array of the translated amino acids in the same order.
////' \cr Source:\cr
//' \emph{Compiled by Andrzej (Anjay) Elzanowski and Jim Ostell at National Center for Biotechnology Information (NCBI), Bethesda, Maryland, U.S.A.}\cr
//' \emph{Last update of the Genetic Codes: Nov. 18, 2016}
//' \emph{\link{https://www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi}}
//'
//' \emph{codons} all codons as strings.\cr
//' \emph{amino_acids} the translated aminop acids in same order.\cr
//' 
//' @param name the name of a Genetic Code as string. (check \link{print_all_translation_table})
//'
//' @return Returns a named List with all codons and the translated amino acids:\cr
//' @examples
//' (code <- genetic_codes_by_name("The Yeast Mitochondrial Code"))
//' 
//' @export 
// [[Rcpp::export]]
List genetic_codes_by_name(std::string name) {
  auto idx = gen_codes::CodonTranslTables::getInstance().getIdxByName(name);
  return genetic_codes_by_index(idx);
}