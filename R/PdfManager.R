#' Generate a PDF/latex report
#' 
#' The function makes a dir called: "GCATR_Report" in your current working dir. In the following steps it cops a .Rnw template file
#' into the new dir. Afterwords it executes knitr with parameters based on the your input. All the generated files are in the new dir.
#' 
#' @param code is either a string vector or a string. It can either be a code or a sequence.
#' @param length if code is a sequence, length is the tuple length of the code.
#' 
#' @examples
#' code_pdf_report(c("ACG", "CAG"))
#' code_pdf_report("ACGCAG", 3)
#' code_pdf_report("ACG CAG")
#' 
#' 
#' @export
code_pdf_report <- function(code, tuple_length = -55555) {
  dirname <- "GCATR_Report"
  idx <- 0;
  while (dir.exists(dirname)) {
    idx <- idx + 1;
    dirname <- paste0("GCATR_Report_", idx, collapse = NULL)
  }
  if(tuple_length == - 55555) {
    code <- code_as_vector(code)
  } else {
    code <- code_as_vector(code, length)
  }
  
  startwd <- getwd()
  dir.create(dirname)
  setwd(dirname)
  
  template_file <- system.file("data", "GCATR_Report.Rnw", package = "GCATR")
  
  file.copy(template_file , "GCATR_Report.Rnw")
  
  code_table <- GCATR::genetic_codes_as_df_by_index(1)
  
  params <- list(
    code = code,
    code_table = code_table
  )
  
  knitr::knit2pdf(template_file);
  #rmarkdown::render(template_file, params = params, envir = new.env())
  
  setwd(startwd)
}