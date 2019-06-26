
#include <Rcpp.h>
#include "GCATCPP/codes/CodeFactory.h"
#include "GCATCPP/miner/LongestPathMiner.h"
#include "GCATCPP/miner/CircleMiner.h"
#include "GCATCPP/generator/BaseValueGenerator.h"
#include "GCATCPP/modification/ShiftTuples.h"


#include "RAdapterUtils.h"


using namespace Rcpp;


//' Check if a code is circular.
//' 
//' This function checks if a code is circular. The code can either be a vector of tuples or a sequence. If the code
//' is a sequence an additional word length parameter is needed.
//' Circular codes are a block codes. We will call a set of tuples \emph{X} of same length
//' a code if every concatenation of words \emph{w} in \emph{X} written on a circle has only a single decomposition into words from \emph{X}.
//' It is used as an unproved approach to explain the
//' method used in gens to retrieving the correct reading frames of RNA.\cr
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @return Boolean value. True if the code is circular.
//' @examples
//' code_check_if_circular(c("ACG", "CAG"))
//' code_check_if_circular("ACGCAG", 3)
//' code_check_if_circular("ACG CAG")
//'
//' @export 
// [[Rcpp::export]]
bool code_check_if_circular(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactor(code_vec, length);
    return a->is_circular();
}

//' Returns a code as vector.
//' 
//' Turns a sequence or a single string into a string vector.
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @return StringVector code as vector.
//' @examples
//' code_vec <- code_as_vector(c("ACG", "CAG"))
//' code_vec <- code_as_vector("ACGCAG", 3)
//' code_vec <- code_as_vector("ACG CAG")
//'
//' @export 
// [[Rcpp::export]]
StringVector code_as_vector(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactor(code_vec, length);
    return RAdapterUtils::as_r_string_vector(a->as_vector());
}



//' Returns tuple length.
//' 
//' Returns the tuple length of the code. If the code is a mixed code it returns the longest tuple length.
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @return Number tuple length.
//' @examples
//' code_l <- code_tuple_length(c("ACG", "CAG"))
//' code_l <- code_tuple_length("ACGCAG", 3)
//' code_l <- code_tuple_length("ACG CAG")
//'
//' @export 
// [[Rcpp::export]]
int code_tuple_length(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactor(code_vec, length);
    return a->get_word_length()[0];
}

//' Check if a set is a code.
//'
//' This function checks if a code is a code.\cr
//' Let \emph{Sigma} be a finite alphabet and X a subset of \emph{Sigma}*l for some l in N.\cr
//' - For w in \emph{Sigma}*l , an X-decomposition of w is a tuple (x1 ,... , xt ) in Xt with t in N such that
//' X = x 1 · x 2 · · · x t .
//' - A set X subset of \emph{Sigma}*l  is a code if each word w in X has a single X-decomposition.
//' - For an integer l > 1, an l-letter code is a code contained in .
//' Let X be a subset of \emph{Sigma}*l . X is called a code over Σ ∗ if for all n, m > 0 and x1...xn , x1...xm in X,
//' the condition\cr
//' x1...xn = x1...xm\cr
//' implies\cr
//' n = m and xi = xj for i = 1,..., n\cr
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @return Boolean value. True if the code is circular.
//' @examples
//' code_check_if_circular(c("ACG", "CAG"))
//' code_check_if_circular("ACGCAG", 3)
//' code_check_if_circular("ACG CAG")
//'
//' @export
// [[Rcpp::export]]
bool code_check_if_code(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactor(code_vec, length);
    return a->test_code();
}

//' Check if a code is k-circular.
//'
//' This function checks if a code is k-circular.
//' The code can either be a vector of tuples or a sequence. If the code
//' is a sequence an additional word length parameter is needed.\cr
//' k-circular means:\cr
//' That for each sequence/concatenation of less than k tuples of a code \emph{X} written on a circle, there is only one partition in tuples from the code \emph{X}.
//' This is an extended property of the circular codes. Circular codes are a block codes. See \link{code_check_if_circular} for more details.\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param k is is integer. k refers to the k-circular property.
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @return Boolean value. True if the code is k-circular.
//' @examples
//' code_check_if_k_circular(2, c("ACG", "CAG"))
//' code_check_if_k_circular(2, "ACGCAG", 3)
//' code_check_if_k_circular(2, "ACG CAG")
//'
//' @export
// [[Rcpp::export]]
bool code_check_if_k_circular(int k, StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactor(code_vec, length);
    return a->is_k_circular(k);
}

//' Check if a code is Cn-circular.
//'
//' This function checks if a code is Cn-circular.
//' The code can either be a vector of tuples or a sequence. If the code
//' is a sequence an additional word length parameter is needed.\cr
//' Cn-circular means:\cr
//' That all circular permutations of the code (all tuples) are circular codes again.\cr
//' This is an extended property of the circular codes. Circular codes are a block codes. See \link{code_check_if_circular} for more details.\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//'
//' @return Boolean value. True if the code is Cn-circular.
//' @examples
//' code_check_if_cn_circular(c("ACG", "CAG"))
//' code_check_if_cn_circular("ACGCAG", 3)
//' code_check_if_cn_circular("ACG CAG")
//'
//' @export
// [[Rcpp::export]]
bool code_check_if_cn_circular(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactor(code_vec, length);
    return a->is_cn_circular();
}

//' Check if a code is comma free.
//'
//' This function checks if a code is comma free.
//' The code can either be a vector of tuples or a sequence. If the code
//' is a sequence an additional word length parameter is needed.\cr
//' Comma free is a more restrictive code of the family of the circular codes:\cr
//' A comma-free code is block code in which no concatenation of two code words contains a valid code word that overlaps both.\cr
//' This is an extended property of the circular codes. Circular codes are a block codes. See \link{code_check_if_circular} for more details.\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @return Boolean value. True if the code is comma free.
//' @examples
//' code_check_if_comma_free(c("ACG", "CAG"))
//' code_check_if_comma_free("ACGCAG", 3)
//' code_check_if_comma_free("ACG CAG")
//'
//' @export
// [[Rcpp::export]]
bool code_check_if_comma_free(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactor(code_vec, length);
    return a->is_comma_free();
}


//' Check if a code is self complementary.
//' 
//' This function checks if a code is self complementary.
//' The code can either be a vector of DNA/RNA tuples or a sequence. If the code
//' is a sequence an additional word length parameter is needed.\cr
//' A code is self complementary if and only if for all tuples in the code the anti-tuple is also in the code.
//' An anti-tuple is te reversed tuple of complementary bases.\cr A <-> T (U) and C <-> G. The anti-tuple of ACG is CGT
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is either a string vector or a string. It has to be a RNA/DNA - code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @return Boolean value. True if the code is self-complementary.
//' @examples
//' code_check_if_self_complementary(c("ACG", "CAG"))
//' code_check_if_self_complementary("ACGCAG", 3)
//' code_check_if_self_complementary("ACG CAG")
//'
//' @export
// [[Rcpp::export]]
bool code_check_if_self_complementary(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactorGenCode(code_vec, length);
    bool res = a->is_self_complementary();
    return res;//a->is_self_complementary();
}

//' Get acid type of a code
//' 
//' Returns either RNA or DNA depending on the codes Bases. If the code contains only CYTOSINE (C), ADENINE (A), GUANINE (G)
//' the functions returns DNA. If the code contains THYMINE (T) it will also return DNA. On the other side, if the
//' the code contains URACIL (U) bases the function returns RNA. If the code contains URACIL (U) and THYMINE (T) or any other letter
//' then CYTOSINE (C), ADENINE (A), GUANINE (G), URACIL (U) or THYMINE (T) it will return NONE
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is either a string vector or a string. It should be a RNA/DNA - code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @return String value. One of NONE, DNA, RNA
//' @examples
//' code_get_acid(c("ACG", "CAG"))
//' code_get_acid("ACGCAG", 3)
//' code_get_acid("ACG CAG")
//' 
//' @export
// [[Rcpp::export]]
StringVector code_get_acid(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactorGenCode(code_vec, length);
    return acid::acid_to_string(a->get_acid());;
}

//' Get amino acids encoded by a code
//' 
//' Returns the amino acids encoded by a codes. The code can contain only CYTOSINE (C), ADENINE (A), GUANINE (G)
//' and THYMINE (T) or URACIL (U) bases. If no other translation table is selecte the function will use the 
//' \emph{standard genetic code}. A different tranlastion table has to be added by index. Therefore, (see \link{print_all_translation_tables})\cr
//' For more info on this subject read:\cr
//' \link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
//' \link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
//' \emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
//'
//' @param code is either a string vector or a string. It should be a RNA/DNA - code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//' @param idx the index of a Genetic Code table as int. (check \link{print_all_translation_table})
//' @return String vector. list of amino acids
//' @examples
//' code_get_amino_acids(c("ACG", "CAG"), idx_trans_table=2)
//' code_get_amino_acids("ACGCAG", 3, idx_trans_table=2)
//' code_get_amino_acids("ACG CAG", idx_trans_table=2)
//' 
//' @export
// [[Rcpp::export]]
StringVector code_get_amino_acids(StringVector code, int length = -1, int idx_trans_table = 1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto a = CodeFactory::rFactorGenCode(code_vec, length);
    a->setTranslTableByIdx(idx_trans_table);
    return RAdapterUtils::as_r_string_vector(a->get_amino_acids());
}

//' Finds one longest path in the graph of the code.
//'
//' Prepares a R path string vector. Extracts all longest paths of the Graph G(X) and returns the tuples of the first found one.
//' If the graph shows a cycle the vector will be empty. Otherwise it returns a vector with one longest path.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @seealso \link{code_factor_longest_path} for a graph of the longest path. \link{code_get_all_longest_path_as_vector} for the results as list
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//'
//' @return A String vector. Nodes of the longest path
//' @examples
//' l_path <- code_get_one_circle_as_vector(c("ACG", "CGA"))
//' l_path <- code_get_one_circle_as_vector("ACGCGA", 3)
//' l_path <- code_get_one_circle_as_vector("ACG CGA")
//'
//' @export
// [[Rcpp::export]]
StringVector code_get_one_longest_path_as_vector(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactor(code_vec, length);
    auto longest_path_collection = miner::LongestPathMiner::mine_path_as_vector(&*gc);
    if (longest_path_collection.size() == 0) {
        gc->print_errors();
        return {};
    }
    return RAdapterUtils::as_r_string_vector(longest_path_collection[0]);
}

//' Finds all longest paths in the graph of the code.
//'
//' Prepares a list of R path string vector. Extracts all longest paths of the Graph G(X) and returns a list.
//' If the graph shows a cycle the vector will be empty. Otherwise it returns a list of vector with all longest paths.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @seealso \link{code_factor_longest_path} for a graph of the longest path. \link{code_get_all_longest_path_as_vector} for only one result
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param length if code is a sequence, length is the tuple length of the code.
//'
//' @return A list of String vectors. Nodes of the longest path
//' @examples
//' l_path <- code_get_all_longest_path_as_vector(c("ACG", "CGA"))
//' l_path <- code_get_all_longest_path_as_vector("ACGCGA", 3)
//' l_path <- code_get_all_longest_path_as_vector("ACG CGA")
//'
//' @export
// [[Rcpp::export]]
Rcpp::List code_get_all_longest_path_as_vector(StringVector code, int length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactor(code_vec, length);
    auto longest_path_collection = miner::LongestPathMiner::mine_path_as_vector(&*gc);
    if (longest_path_collection.size() == 0) {
        gc->print_errors();
        return {};
    }
    return RAdapterUtils::as_R_matrix(longest_path_collection);
}

//' Finds one circular sequences constructable in a code.
//'
//' Prepares a R path string vector. Extracts all cycles in the Graph G(X).
//' If the graph has no cycles the vector will be empty. Otherwise it returns a vector with the nodes of
//' a circular path.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @seealso \link{code_factor_cycles} for a graph of the cycles, \link{code_get_all_cycles_as_vector} for the results as list
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param tuple_length if code is a sequence, length is the tuple length of the code.
//'
//' @return List of nodes representing a circular path in G(X).
//'
//' @examples
//' l_graph <- code_get_one_cycles_as_vector(c("ACG", "CGA"))
//' l_graph <- code_get_one_cycles_as_vector("ACGCGA", 3)
//' l_graph <- code_get_one_cycles_as_vector("ACG CGA")
//'
//' @export
// [[Rcpp::export]]
StringVector code_get_one_cycles_as_vector(StringVector code, int tuple_length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactor(code_vec, tuple_length);
    auto circle_path_collection = miner::CircleMiner::mine_path_as_vector(&*gc);
    if (circle_path_collection.size() == 0) {
        gc->print_errors();
        return {};
    }
    return RAdapterUtils::as_r_string_vector(circle_path_collection[0]);
}

//' Finds all circular sequences constructable in a code.
//'
//' Prepares a list of R path string vector. Extracts all cycles in the Graph G(X).
//' If the graph has no cycles the vector will be empty. Otherwise it returns a list of vectors with the nodes of
//' the circular paths.\cr
//' \emph{2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory}
//'
//' @seealso \link{code_factor_cycles} for a graph of the cycles, \link{code_get_one_cycles_as_vector} for the one result
//'
//' @param  code is either a string vector or a string. It can either be a code or a sequence.
//' @param tuple_length if code is a sequence, length is the tuple length of the code.
//'
//' @return List of nodes representing a circular path in G(X).
//'
//' @examples
//' l_graph <- code_get_one_cycles_as_vector(c("ACG", "CGA"))
//' l_graph <- code_get_one_cycles_as_vector("ACGCGA", 3)
//' l_graph <- code_get_one_cycles_as_vector("ACG CGA")
//'
//' @export
// [[Rcpp::export]]
Rcpp::List code_get_all_cycles_as_vector(StringVector code, int tuple_length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactor(code_vec, tuple_length);
    auto circle_path_collection = miner::CircleMiner::mine_path_as_vector(&*gc);
    if (circle_path_collection.size() == 0) {
        gc->print_errors();
        return {};
    }
    return RAdapterUtils::as_R_matrix(circle_path_collection);
}

//' Returns all DNA bases
//'
//' @return {"T", "C", "A", "G"}
//'
//' @examples
//' res <- get_dna_bases ()
//'
//' @export 
// [[Rcpp::export]]
Rcpp::StringVector get_dna_bases() {
    std::vector<std::string> result(acid::acid_base_length);
    for (int i = 0; i < acid::acid_base_length; ++i) {
        result[i] = acid::dna[i];
    }

    return RAdapterUtils::as_r_string_vector(result);
}

//' Returns all RNA bases
//'
//' @return {"U", "C", "A", "G"}
//'
//' @examples
//' res <- get_rna_bases()
//'
//' @export
// [[Rcpp::export]]
Rcpp::StringVector get_rna_bases() {
    std::vector<std::string> result(acid::acid_base_length);
    for (int i = 0; i < acid::acid_base_length; ++i) {
        result[i] = acid::rna[i];
    }

    return RAdapterUtils::as_r_string_vector(result);
}

//' Analysis a sequence based on a generic code.
//'
//' Finds all appearances of a code in a sequence. Finds the longest connected motive of words of the code in the sequence.
//' The function also calculates the matching bases of the found words in the sequence.
//'
//' @return Returns a List with all analysing results. The list contains the following:\cr
//' \emph{words} (String vector) all found words of the code in the sequence in the correct order.\cr
//' \emph{idx_list} (Number vector) the first-letter index of all found words of the code in the sequence in the correct order.\cr
//' \emph{rest} (String) all parts of the sequence which are not matching the code.\cr
//' \emph{parts} (String vector) the sequence separated in matching and non matching parts. Odd indexes are matching, even indexes are not matching.\cr
//' \emph{longest_match} (Number) the longest connected matching sequence.\cr
//' \emph{total_match_in_percent} (Number) the percentage of the matching parts.
//'
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param tuple_length if code is a sequence, length is the tuple length of the code.
//'
//' @examples
//' seq <- "ACGTCGCGACGTACGACGTCGTACTCGATGCAAGATC"
//' res <- find_and_analysis_code_in_sequence(seq, c("ACG", "TCG"))
//' res <- find_and_analysis_code_in_sequence(seq, "ACGCG", tuple_length=3)
//' res <- find_and_analysis_code_in_sequence(seq, "ACG TCG")
//'
//' @export
// [[Rcpp::export]]
Rcpp::List find_and_analysis_code_in_sequence(std::string seq, StringVector code, int tuple_length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactor(code_vec, tuple_length);
    auto res = gc->find_code_in_sequence(seq);

    return Rcpp::List::create(
            Rcpp::Named("word") = Rcpp::wrap(res.words),
            Rcpp::Named("idx_list") = Rcpp::wrap(res.idx_list),
            Rcpp::Named("rest") = Rcpp::wrap(res.rest),
            Rcpp::Named("parts") = Rcpp::wrap(res.parts),
            Rcpp::Named("longest_match") = res.longest_match,
            Rcpp::Named("total_match_in_percent") = res.total_match_in_percent);
}

//' This function generates a maximal circular code.
//'
//' Based on a value function each word can be assigned to a value. The code is a set of the words with the
//' lowest value of each permutation class. This code has be proven to be circular and maximal. This can be done for any alphabet.
//'
//' @param alphabet is a vector of letters.
//' @param tuple_length is the tuple length of the resulting code.
//'
//' @return A maximal circular code as String vector.
//'
//' @examples
//' code <- generate_code_by_min_value(c("A", "C", "G", "T"), 3)
//'
//' @export
// [[Rcpp::export]]
StringVector generate_code_by_min_value(StringVector alphabet, int tuple_length) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(alphabet);
    BaseValueGenerator codeGenerator(code_vec, tuple_length, true);
    auto code_list =  codeGenerator.run();
    return RAdapterUtils::as_r_string_vector(code_list);
}

//' Circular shift of all tuples
//'
//' This functions shifts all tuples in code anticlockwise. In other words, the first character of each tuples gets removed and
//' added to the end of the same tuple. Depending on the parameter \emph{shift} this process is repeated multiple times.
//'
//' @param shifts number of shifts
//' @param code is either a string vector or a string. It can either be a code or a sequence.
//' @param tuple_length if code is a sequence, length is the tuple length of the code.
//'
//' @return shifted code as String vector
//'
//' @examples
//' shifted_code <- shift_tuples(2, c("ACG", "GAT"))
//' shifted_code <- shift_tuples(2, "ACGGAT", tuple_length=3)
//' shifted_code <- shift_tuples(2, "ACG GAT")
//'
//' @export
// [[Rcpp::export]]
StringVector shift_tuples(int shifts, StringVector code, int tuple_length = -1) {
    auto code_vec = RAdapterUtils::as_cpp_string_vector(code);
    auto gc = CodeFactory::rFactor(code_vec, tuple_length);
    gc->shift_tuples(shifts);
    return RAdapterUtils::as_r_string_vector(gc->as_vector());
}