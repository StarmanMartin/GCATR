#' @export
test_pdf_reder <- function(code) {
  dirname <- "CircularCodeReport";
  idx <- 0;
  while (dir.exists(dirname)) {
    idx <- idx + 1;
    dirname <- paste0("CircularCodeReport_", idx, collapse = NULL)
  }
  
  startwd <- getwd();
  dir.create(dirname);
  setwd(dirname);
  
  template_file <- system.file("data", "CircularCodeReport.Rnw", package = "GCATR")
  
  file.copy(template_file , "CircularCodeReport.Rnw")
  
  output_t <- "CircularCodeReport.pdf"
  
  params <- list(
    code = code
  )
  
  knitr::knit2pdf(template_file);
  #rmarkdown::render(template_file, params = params, envir = new.env())
  
  setwd(startwd)
  

  

}