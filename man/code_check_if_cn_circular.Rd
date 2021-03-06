% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{code_check_if_cn_circular}
\alias{code_check_if_cn_circular}
\title{Check if a code is Cn-circular.}
\usage{
code_check_if_cn_circular(code, tuple_length = -55555L)
}
\arguments{
\item{code}{is either a string vector or a string. It can either be a code or a sequence.}

\item{tuple_length}{if code is a sequence, length is the tuple length of the code.}
}
\value{
Boolean value. True if the code is Cn-circular.
}
\description{
This function checks if a code is Cn-circular.
The code can either be a vector of tuples or a sequence. If the code
is a sequence an additional word length parameter is needed.\cr
Cn-circular means:\cr
That all circular permutations of the code (all tuples) are circular codes again.\cr
This is an extended property of the circular codes. Circular codes are a block codes. See \link{code_check_if_circular} for more details.\cr
\link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
\link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
\emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
}
\examples{
code_check_if_cn_circular(c("ACG", "CAG"))
code_check_if_cn_circular("ACGCAG", 3)
code_check_if_cn_circular("ACG CAG")

}
