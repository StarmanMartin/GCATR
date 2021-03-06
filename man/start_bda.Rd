% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/BdaTools.R
\name{start_bda}
\alias{start_bda}
\title{Start a BDA procedure for all codons}
\usage{
start_bda()
}
\value{
Boolean value. True if the procedure has started
}
\description{
This Function starts a binary dichotomic algorithm (BDA) procedure for all codons (see \link{get_rna_codon_list}).
To run \link{run_bda_as_matrix} the BDA procedure has been started by this (\link{start_bda}) function.
Each added binary BDA results one binary digit for each codon.
You can add multiple BDAs for one procedure. To add a rule, you need to start a BDA procedure first.
To do so you can either call \link{code_start_bda} or to start a procedure
for all RNA codons call \link{start_bda}.
To add a BDA simply Call \link{add_rule}. To execute the BDAs call \link{run_bda}.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:\cr
\emph{M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms}
}
\examples{
bda_obj <- start_bda()
add_rule(bda_obj, 1, 2, "C", "G", "A", "U")
add_rule(bda_obj, 1, 3, "A", "G", "C", "U")
res <- run_bda_as_matrix(bda_obj)

}
\seealso{
[code_start_bda()] for code, [add_rule] add a BDA,
          [run_bda] for executing and run the BDAs
}
