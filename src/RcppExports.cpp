// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// get_average_conductance_of_code
double get_average_conductance_of_code(std::string codeName, std::string acid);
RcppExport SEXP _GCATR_get_average_conductance_of_code(SEXP codeNameSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type codeName(codeNameSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(get_average_conductance_of_code(codeName, acid));
    return rcpp_result_gen;
END_RCPP
}
// get_max_conductance_of_code
double get_max_conductance_of_code(std::string codeName, std::string acid);
RcppExport SEXP _GCATR_get_max_conductance_of_code(SEXP codeNameSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type codeName(codeNameSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(get_max_conductance_of_code(codeName, acid));
    return rcpp_result_gen;
END_RCPP
}
// get_min_conductance_of_code
double get_min_conductance_of_code(std::string codeName, std::string acid);
RcppExport SEXP _GCATR_get_min_conductance_of_code(SEXP codeNameSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type codeName(codeNameSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(get_min_conductance_of_code(codeName, acid));
    return rcpp_result_gen;
END_RCPP
}
// get_average_conductance_of_codeidx
double get_average_conductance_of_codeidx(int codeIdx, std::string acid);
RcppExport SEXP _GCATR_get_average_conductance_of_codeidx(SEXP codeIdxSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type codeIdx(codeIdxSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(get_average_conductance_of_codeidx(codeIdx, acid));
    return rcpp_result_gen;
END_RCPP
}
// get_max_conductance_of_codeidx
double get_max_conductance_of_codeidx(int codeIdx, std::string acid);
RcppExport SEXP _GCATR_get_max_conductance_of_codeidx(SEXP codeIdxSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type codeIdx(codeIdxSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(get_max_conductance_of_codeidx(codeIdx, acid));
    return rcpp_result_gen;
END_RCPP
}
// get_min_conductance_of_codeidx
double get_min_conductance_of_codeidx(int codeIdx, std::string acid);
RcppExport SEXP _GCATR_get_min_conductance_of_codeidx(SEXP codeIdxSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type codeIdx(codeIdxSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(get_min_conductance_of_codeidx(codeIdx, acid));
    return rcpp_result_gen;
END_RCPP
}
// print_all_translation_tables
void print_all_translation_tables();
RcppExport SEXP _GCATR_print_all_translation_tables() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    print_all_translation_tables();
    return R_NilValue;
END_RCPP
}
// genetic_codes_by_index
List genetic_codes_by_index(int idx, std::string acid);
RcppExport SEXP _GCATR_genetic_codes_by_index(SEXP idxSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type idx(idxSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(genetic_codes_by_index(idx, acid));
    return rcpp_result_gen;
END_RCPP
}
// code_is_translatable
bool code_is_translatable(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_is_translatable(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_is_translatable(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// cpp_genetic_codes_as_df_by_index
DataFrame cpp_genetic_codes_as_df_by_index(int idx, std::string acid);
RcppExport SEXP _GCATR_cpp_genetic_codes_as_df_by_index(SEXP idxSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type idx(idxSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_genetic_codes_as_df_by_index(idx, acid));
    return rcpp_result_gen;
END_RCPP
}
// genetic_codes_by_name
List genetic_codes_by_name(std::string name, std::string acid);
RcppExport SEXP _GCATR_genetic_codes_by_name(SEXP nameSEXP, SEXP acidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type name(nameSEXP);
    Rcpp::traits::input_parameter< std::string >::type acid(acidSEXP);
    rcpp_result_gen = Rcpp::wrap(genetic_codes_by_name(name, acid));
    return rcpp_result_gen;
END_RCPP
}
// seq_get_tuple_count
std::map<std::string, int> seq_get_tuple_count(std::string seq, int tuple_length);
RcppExport SEXP _GCATR_seq_get_tuple_count(SEXP seqSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type seq(seqSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(seq_get_tuple_count(seq, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// seq_get_info
List seq_get_info(std::string seq, int tuple_length);
RcppExport SEXP _GCATR_seq_get_info(SEXP seqSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type seq(seqSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(seq_get_info(seq, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_prepare_factor_gen_c3graph
Rcpp::List code_prepare_factor_gen_c3graph(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_prepare_factor_gen_c3graph(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_prepare_factor_gen_c3graph(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_prepare_factor_graph
Rcpp::List code_prepare_factor_graph(StringVector code, bool show_cycles, bool show_longest_path, int tuple_length);
RcppExport SEXP _GCATR_code_prepare_factor_graph(SEXP codeSEXP, SEXP show_cyclesSEXP, SEXP show_longest_pathSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< bool >::type show_cycles(show_cyclesSEXP);
    Rcpp::traits::input_parameter< bool >::type show_longest_path(show_longest_pathSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_prepare_factor_graph(code, show_cycles, show_longest_path, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_prepare_factor_all_cycle
Rcpp::List code_prepare_factor_all_cycle(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_prepare_factor_all_cycle(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_prepare_factor_all_cycle(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_prepare_factor_longest_path
Rcpp::List code_prepare_factor_longest_path(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_prepare_factor_longest_path(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_prepare_factor_longest_path(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_check_if_circular
bool code_check_if_circular(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_check_if_circular(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_check_if_circular(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_as_vector
StringVector code_as_vector(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_as_vector(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_as_vector(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_as_unique_vector
StringVector code_as_unique_vector(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_as_unique_vector(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_as_unique_vector(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_check_if_code
bool code_check_if_code(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_check_if_code(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_check_if_code(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_check_if_k_circular
bool code_check_if_k_circular(int k, StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_check_if_k_circular(SEXP kSEXP, SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_check_if_k_circular(k, code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_k_value
int code_k_value(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_k_value(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_k_value(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_check_if_cn_circular
bool code_check_if_cn_circular(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_check_if_cn_circular(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_check_if_cn_circular(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_check_if_comma_free
bool code_check_if_comma_free(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_check_if_comma_free(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_check_if_comma_free(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_strip_complements
StringVector code_strip_complements(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_strip_complements(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_strip_complements(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_check_if_self_complementary
bool code_check_if_self_complementary(StringVector code, int tuple_length, bool mute);
RcppExport SEXP _GCATR_code_check_if_self_complementary(SEXP codeSEXP, SEXP tuple_lengthSEXP, SEXP muteSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    Rcpp::traits::input_parameter< bool >::type mute(muteSEXP);
    rcpp_result_gen = Rcpp::wrap(code_check_if_self_complementary(code, tuple_length, mute));
    return rcpp_result_gen;
END_RCPP
}
// code_get_acid
StringVector code_get_acid(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_get_acid(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_get_acid(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_get_all_amino_acids
StringVector code_get_all_amino_acids(StringVector code, int idx_trans_table);
RcppExport SEXP _GCATR_code_get_all_amino_acids(SEXP codeSEXP, SEXP idx_trans_tableSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type idx_trans_table(idx_trans_tableSEXP);
    rcpp_result_gen = Rcpp::wrap(code_get_all_amino_acids(code, idx_trans_table));
    return rcpp_result_gen;
END_RCPP
}
// code_get_amino_acids
StringVector code_get_amino_acids(StringVector code, int idx_trans_table);
RcppExport SEXP _GCATR_code_get_amino_acids(SEXP codeSEXP, SEXP idx_trans_tableSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type idx_trans_table(idx_trans_tableSEXP);
    rcpp_result_gen = Rcpp::wrap(code_get_amino_acids(code, idx_trans_table));
    return rcpp_result_gen;
END_RCPP
}
// code_get_one_longest_path_as_vector
StringVector code_get_one_longest_path_as_vector(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_get_one_longest_path_as_vector(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_get_one_longest_path_as_vector(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_get_all_longest_path_as_vector
Rcpp::List code_get_all_longest_path_as_vector(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_get_all_longest_path_as_vector(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_get_all_longest_path_as_vector(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_get_one_cycles_as_vector
StringVector code_get_one_cycles_as_vector(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_get_one_cycles_as_vector(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_get_one_cycles_as_vector(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_get_all_cycles_as_vector
Rcpp::List code_get_all_cycles_as_vector(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_get_all_cycles_as_vector(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_get_all_cycles_as_vector(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// get_dna_bases
Rcpp::StringVector get_dna_bases();
RcppExport SEXP _GCATR_get_dna_bases() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(get_dna_bases());
    return rcpp_result_gen;
END_RCPP
}
// get_rna_bases
Rcpp::StringVector get_rna_bases();
RcppExport SEXP _GCATR_get_rna_bases() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(get_rna_bases());
    return rcpp_result_gen;
END_RCPP
}
// find_and_analysis_code_in_sequence
Rcpp::List find_and_analysis_code_in_sequence(std::string seq, StringVector code, int tuple_length, int frame);
RcppExport SEXP _GCATR_find_and_analysis_code_in_sequence(SEXP seqSEXP, SEXP codeSEXP, SEXP tuple_lengthSEXP, SEXP frameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type seq(seqSEXP);
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    Rcpp::traits::input_parameter< int >::type frame(frameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_and_analysis_code_in_sequence(seq, code, tuple_length, frame));
    return rcpp_result_gen;
END_RCPP
}
// generate_code_by_min_value
StringVector generate_code_by_min_value(StringVector alphabet, int tuple_length);
RcppExport SEXP _GCATR_generate_code_by_min_value(SEXP alphabetSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(generate_code_by_min_value(alphabet, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// shift_tuples
StringVector shift_tuples(int shifts, StringVector code, int tuple_length);
RcppExport SEXP _GCATR_shift_tuples(SEXP shiftsSEXP, SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type shifts(shiftsSEXP);
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(shift_tuples(shifts, code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_transform_tuples
StringVector code_transform_tuples(std::string from, std::string to, StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_transform_tuples(SEXP fromSEXP, SEXP toSEXP, SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type from(fromSEXP);
    Rcpp::traits::input_parameter< std::string >::type to(toSEXP);
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_transform_tuples(from, to, code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_named_transform_tuples
StringVector code_named_transform_tuples(std::string trans_name, StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_named_transform_tuples(SEXP trans_nameSEXP, SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type trans_name(trans_nameSEXP);
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_named_transform_tuples(trans_name, code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_check_if_tessera
bool code_check_if_tessera(StringVector code);
RcppExport SEXP _GCATR_code_check_if_tessera(SEXP codeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    rcpp_result_gen = Rcpp::wrap(code_check_if_tessera(code));
    return rcpp_result_gen;
END_RCPP
}
// codons_to_tessera
StringVector codons_to_tessera(StringVector code);
RcppExport SEXP _GCATR_codons_to_tessera(SEXP codeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    rcpp_result_gen = Rcpp::wrap(codons_to_tessera(code));
    return rcpp_result_gen;
END_RCPP
}
// tessera_to_codons
StringVector tessera_to_codons(StringVector code);
RcppExport SEXP _GCATR_tessera_to_codons(SEXP codeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    rcpp_result_gen = Rcpp::wrap(tessera_to_codons(code));
    return rcpp_result_gen;
END_RCPP
}
// code_path_end_vertices_miner
StringVector code_path_end_vertices_miner(StringVector code, int tuple_length);
RcppExport SEXP _GCATR_code_path_end_vertices_miner(SEXP codeSEXP, SEXP tuple_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    Rcpp::traits::input_parameter< int >::type tuple_length(tuple_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(code_path_end_vertices_miner(code, tuple_length));
    return rcpp_result_gen;
END_RCPP
}
// code_block_length
int code_block_length(StringVector code);
RcppExport SEXP _GCATR_code_block_length(SEXP codeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    rcpp_result_gen = Rcpp::wrap(code_block_length(code));
    return rcpp_result_gen;
END_RCPP
}
// tessera_to_table
Rcpp::List tessera_to_table(StringVector code);
RcppExport SEXP _GCATR_tessera_to_table(SEXP codeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    rcpp_result_gen = Rcpp::wrap(tessera_to_table(code));
    return rcpp_result_gen;
END_RCPP
}
// tessera_to_table_str
StringVector tessera_to_table_str(StringVector code);
RcppExport SEXP _GCATR_tessera_to_table_str(SEXP codeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< StringVector >::type code(codeSEXP);
    rcpp_result_gen = Rcpp::wrap(tessera_to_table_str(code));
    return rcpp_result_gen;
END_RCPP
}

RcppExport SEXP _rcpp_module_boot_BDATools();

static const R_CallMethodDef CallEntries[] = {
    {"_GCATR_get_average_conductance_of_code", (DL_FUNC) &_GCATR_get_average_conductance_of_code, 2},
    {"_GCATR_get_max_conductance_of_code", (DL_FUNC) &_GCATR_get_max_conductance_of_code, 2},
    {"_GCATR_get_min_conductance_of_code", (DL_FUNC) &_GCATR_get_min_conductance_of_code, 2},
    {"_GCATR_get_average_conductance_of_codeidx", (DL_FUNC) &_GCATR_get_average_conductance_of_codeidx, 2},
    {"_GCATR_get_max_conductance_of_codeidx", (DL_FUNC) &_GCATR_get_max_conductance_of_codeidx, 2},
    {"_GCATR_get_min_conductance_of_codeidx", (DL_FUNC) &_GCATR_get_min_conductance_of_codeidx, 2},
    {"_GCATR_print_all_translation_tables", (DL_FUNC) &_GCATR_print_all_translation_tables, 0},
    {"_GCATR_genetic_codes_by_index", (DL_FUNC) &_GCATR_genetic_codes_by_index, 2},
    {"_GCATR_code_is_translatable", (DL_FUNC) &_GCATR_code_is_translatable, 2},
    {"_GCATR_cpp_genetic_codes_as_df_by_index", (DL_FUNC) &_GCATR_cpp_genetic_codes_as_df_by_index, 2},
    {"_GCATR_genetic_codes_by_name", (DL_FUNC) &_GCATR_genetic_codes_by_name, 2},
    {"_GCATR_seq_get_tuple_count", (DL_FUNC) &_GCATR_seq_get_tuple_count, 2},
    {"_GCATR_seq_get_info", (DL_FUNC) &_GCATR_seq_get_info, 2},
    {"_GCATR_code_prepare_factor_gen_c3graph", (DL_FUNC) &_GCATR_code_prepare_factor_gen_c3graph, 2},
    {"_GCATR_code_prepare_factor_graph", (DL_FUNC) &_GCATR_code_prepare_factor_graph, 4},
    {"_GCATR_code_prepare_factor_all_cycle", (DL_FUNC) &_GCATR_code_prepare_factor_all_cycle, 2},
    {"_GCATR_code_prepare_factor_longest_path", (DL_FUNC) &_GCATR_code_prepare_factor_longest_path, 2},
    {"_GCATR_code_check_if_circular", (DL_FUNC) &_GCATR_code_check_if_circular, 2},
    {"_GCATR_code_as_vector", (DL_FUNC) &_GCATR_code_as_vector, 2},
    {"_GCATR_code_as_unique_vector", (DL_FUNC) &_GCATR_code_as_unique_vector, 2},
    {"_GCATR_code_check_if_code", (DL_FUNC) &_GCATR_code_check_if_code, 2},
    {"_GCATR_code_check_if_k_circular", (DL_FUNC) &_GCATR_code_check_if_k_circular, 3},
    {"_GCATR_code_k_value", (DL_FUNC) &_GCATR_code_k_value, 2},
    {"_GCATR_code_check_if_cn_circular", (DL_FUNC) &_GCATR_code_check_if_cn_circular, 2},
    {"_GCATR_code_check_if_comma_free", (DL_FUNC) &_GCATR_code_check_if_comma_free, 2},
    {"_GCATR_code_strip_complements", (DL_FUNC) &_GCATR_code_strip_complements, 2},
    {"_GCATR_code_check_if_self_complementary", (DL_FUNC) &_GCATR_code_check_if_self_complementary, 3},
    {"_GCATR_code_get_acid", (DL_FUNC) &_GCATR_code_get_acid, 2},
    {"_GCATR_code_get_all_amino_acids", (DL_FUNC) &_GCATR_code_get_all_amino_acids, 2},
    {"_GCATR_code_get_amino_acids", (DL_FUNC) &_GCATR_code_get_amino_acids, 2},
    {"_GCATR_code_get_one_longest_path_as_vector", (DL_FUNC) &_GCATR_code_get_one_longest_path_as_vector, 2},
    {"_GCATR_code_get_all_longest_path_as_vector", (DL_FUNC) &_GCATR_code_get_all_longest_path_as_vector, 2},
    {"_GCATR_code_get_one_cycles_as_vector", (DL_FUNC) &_GCATR_code_get_one_cycles_as_vector, 2},
    {"_GCATR_code_get_all_cycles_as_vector", (DL_FUNC) &_GCATR_code_get_all_cycles_as_vector, 2},
    {"_GCATR_get_dna_bases", (DL_FUNC) &_GCATR_get_dna_bases, 0},
    {"_GCATR_get_rna_bases", (DL_FUNC) &_GCATR_get_rna_bases, 0},
    {"_GCATR_find_and_analysis_code_in_sequence", (DL_FUNC) &_GCATR_find_and_analysis_code_in_sequence, 4},
    {"_GCATR_generate_code_by_min_value", (DL_FUNC) &_GCATR_generate_code_by_min_value, 2},
    {"_GCATR_shift_tuples", (DL_FUNC) &_GCATR_shift_tuples, 3},
    {"_GCATR_code_transform_tuples", (DL_FUNC) &_GCATR_code_transform_tuples, 4},
    {"_GCATR_code_named_transform_tuples", (DL_FUNC) &_GCATR_code_named_transform_tuples, 3},
    {"_GCATR_code_check_if_tessera", (DL_FUNC) &_GCATR_code_check_if_tessera, 1},
    {"_GCATR_codons_to_tessera", (DL_FUNC) &_GCATR_codons_to_tessera, 1},
    {"_GCATR_tessera_to_codons", (DL_FUNC) &_GCATR_tessera_to_codons, 1},
    {"_GCATR_code_path_end_vertices_miner", (DL_FUNC) &_GCATR_code_path_end_vertices_miner, 2},
    {"_GCATR_code_block_length", (DL_FUNC) &_GCATR_code_block_length, 1},
    {"_GCATR_tessera_to_table", (DL_FUNC) &_GCATR_tessera_to_table, 1},
    {"_GCATR_tessera_to_table_str", (DL_FUNC) &_GCATR_tessera_to_table_str, 1},
    {"_rcpp_module_boot_BDATools", (DL_FUNC) &_rcpp_module_boot_BDATools, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_GCATR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
