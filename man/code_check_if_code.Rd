% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{code_check_if_code}
\alias{code_check_if_code}
\title{Check if a set is a code.}
\usage{
code_check_if_code(code, tuple_length = -55555L)
}
\arguments{
\item{code}{is either a string vector or a string. It can either be a code or a sequence.}

\item{tuple_length}{if code is a sequence, length is the tuple length of the code.}
}
\value{
Boolean value. True if the code is circular.
}
\description{
This function checks if a code is a code.\cr
Let \emph{Sigma} be a finite alphabet and X a subset of \emph{Sigma}*l for some l in N.\cr
- For w in \emph{Sigma}*l , an X-decomposition of w is a tuple (x1 ,... , xt ) in Xt with t in N such that
X = x 1 · x 2 · · · x t .
- A set X subset of \emph{Sigma}*l  is a code if each word w in X has a single X-decomposition.
- For an integer l > 1, an l-letter code is a code contained in .
Let X be a subset of \emph{Sigma}*l . X is called a code over Σ ∗ if for all n, m > 0 and x1...xn , x1...xm in X,
the condition\cr
x1...xn = x1...xm\cr
implies\cr
n = m and xi = xj for i = 1,..., n\cr
For more info on this subject read:\cr
\link{https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/},\cr
\link{http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf},\cr
\emph{2007 Christian MICHEL. CIRCULAR CODES IN GENES}
}
\examples{
code_check_if_circular(c("ACG", "CAG"))
code_check_if_circular("ACGCAG", 3)
code_check_if_circular("ACG CAG")

}
