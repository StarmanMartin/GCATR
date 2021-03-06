% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/CodonTables.R
\name{genetic_codes_as_df_by_index}
\alias{genetic_codes_as_df_by_index}
\title{The Genetic Codes}
\usage{
genetic_codes_as_df_by_index(idx, acid = "RNA")
}
\arguments{
\item{idx}{the index of a Genetic Code table as int. (check \link{print_all_translation_table})}

\item{a@param}{acid a String, is optional: DNA or RNA}
}
\value{
Returns a named List with all codons and the translated amino acids:\cr
}
\description{
\\emph{genetic_codes_as_df_by_index} returns a data.frame table which represents a Genetic Code. The table is 4*16.
This table has row names and column names.
\cr Source:\cr
\emph{Compiled by Andrzej (Anjay) Elzanowski and Jim Ostell at National Center for Biotechnology Information (NCBI), Bethesda, Maryland, U.S.A.}\cr
\emph{Last update of the Genetic Codes: Nov. 18, 2016}
\emph{\link{https:#www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi}}
}
\details{
\emph{codons} all codons as strings.\cr
\emph{amino_acids} the translated aminop acids in same order.\cr
}
\examples{
(code <- genetic_codes_as_df_by_index(1))

}
