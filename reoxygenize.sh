Rscript -e "library(Rcpp); compileAttributes('.');"
Rscript -e "devtools::load_all(); roxygen2::roxygenise('.');"
