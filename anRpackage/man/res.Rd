\name{res}
\alias{res}
\docType{data}
\title{
%%   ~~ data name/kind ... ~~
}
\description{
%%  ~~ A concise (1-5 lines) description of the dataset. ~~
}
\usage{data("res")}
\format{
  The format is:
List of 6
 $ word                  : chr [1:6] "ACG" "TCG" "ACG" "ACG" ...
 $ idx_list              : num [1:6] 0 3 12 15 18 24
 $ rest                  : chr "CGACGTTACATGCAAGATC"
 $ parts                 : chr [1:7] "" "ACGTCG" "CGACGT" "ACGACGTCG" ...
 $ longest_match         : num 9
 $ total_match_in_percent: num 48.6
}
\details{
%%  ~~ If necessary, more details than the __description__ above ~~
}
\source{
%%  ~~ reference to a publication or URL from which the data were obtained ~~
}
\references{
%%  ~~ possibly secondary sources and usages ~~
}
\examples{
data(res)
## maybe str(res) ; plot(res) ...
}
\keyword{datasets}
