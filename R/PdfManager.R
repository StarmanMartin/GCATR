#' @export
test_pdf_reder <- function() {
  require(knitr);
  require(rmarkdown);

  dirname <- "CircularCodeReport";
  idx <- 0;
  while (dir.exists(dirname)) {
    idx <- idx + 1;
    dirname <- paste0("CircularCodeReport_", idx, collapse = NULL)
  }

  startwd <- getwd();
  dir.create(dirname);
  setwd(dirname);

  (template_file <- system.file("data", "CircularCodeReport.Rmd", package = "GCATR"))
  output_t="CircularCodeReport.md"
  params <- list(
    code = c("ACG", "CGA")
  )

  knit(template_file, output = output_t);
  render(template_file, output_format = "pdf_document", params = list(
    code = c("ACG", "CGA")
  ))

  setwd(startwd);
}