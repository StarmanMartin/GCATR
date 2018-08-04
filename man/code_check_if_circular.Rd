% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{code_check_if_circular}
\alias{code_check_if_circular}
\title{Check if a code is circular.}
\usage{
code_check_if_circular(code)
}
\arguments{
\item{code}{A vertor with codons.}
}
\value{
Boolean value. True if the code is circular.
}
\description{
This function checks if a genetic code is circular.
Circular codes in gens for retrieving the reading frames of genes.
\emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
}
\examples{
code_check_if_circular(c("ACG", "CAG"))

}