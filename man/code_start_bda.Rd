% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/BdaTools.R
\name{code_start_bda}
\alias{code_start_bda}
\title{Start a BDA procedure for a code.}
\usage{
code_start_bda(code, tuple_length = -55555)
}
\arguments{
\item{code}{is either a string vector or a string. It can be a DNA or RNA sequence.}

\item{tuple_length}{if code is a sequence, length is the tuple length of the code.}
}
\value{
Boolean value. True if the procedure has started
}
\description{
Each added binary dichotomic algorithm (BDA) results one binary digit for each codon.
You can add multiple BDAs for one procedure. To add a rule, you need to start a BDA procedure first.
To do so you can either call \link{code_start_bda} or to start a procedure
for all RNA codons call \link{start_bda}.
To add a BDA simply Call \link{add_rule}. To execute the BDAs call \link{run_bda}.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:\cr
\emph{M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms}
}
\examples{
bda_obj <- code_start_bda(c("ACG", "CAG")) # or
bda_obj <- code_start_bda("ACG CAG")       # or
bda_obj <- code_start_bda("ACGCAG", tuple_length=3)
add_rule(bda_obj, 1, 2, "C", "G", "A", "T")
res.binary <- run_bda(bda_obj)

}
\seealso{
[start_bda()] for all codons, [add_rule] add a BDA,
          [run_bda()] for executing and run the BDAs
}
