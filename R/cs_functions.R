#' @export
setGeneric("marshall", function(x) x)

#' @export
setGeneric("unmarshall", function(x) x)

#' @export
setMethod("marshall", signature = "string_map_data", function(x) {
  result <- c_export_map_data(x)
  class(result) <- "string_map_data_marshalled"
  result
})

#' @export
setMethod("unmarshall", signature = "string_map_data_marshalled", function(x) {
  result <- c_make_map(x)
  class(result) <- "string_map_data"
  result
})

#' @export
setClass("string_map", slots = c(scaffold = "raw"))

#' @export
make_string_map <- function(keys, values) {
  ptr <- c_make_map(list(keys, values))
  class(ptr) <- "string_map_data"
  scaffold <- make_altrep_scaffold(ptr)
  new("string_map", scaffold = scaffold)
}

#' @export
setMethod("print", signature("string_map"), function(x) {
  c_print_map(altrep_scaffold_data(x@scaffold))
})


#' @export
setGeneric("add", function(x, y) c(x,y))

#' @export
setMethod("add", signature("string_map", "list"), function(x,y) {
  c_add_map(altrep_scaffold_data(x@scaffold), y)
})
