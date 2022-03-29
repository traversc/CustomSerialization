#include <Rcpp.h>
// #include "marshall_dispatch.h"
using namespace Rcpp;

// Rcpp::Environment package_env("package:CustomSerialization");
// Rcpp::Environment package_env = Environment::global_env();
// static Rcpp::Function do_marshall = package_env["marshall"];

// needs to be initialized after install? 
static Rcpp::Environment package_env;
static Rcpp::Function do_marshall = Rcpp::Environment::base_env()["c"]; // Rcpp::Function needs to be assigned to something, no default initialization
static Rcpp::Function do_unmarshall = Rcpp::Environment::base_env()["c"];
static bool initialized = false;

// [[Rcpp::export(rng=false)]]
SEXP marshall_dispatch(SEXP x) {
  if(!initialized) {
    package_env = Rcpp::Environment("package:CustomSerialization");
    do_marshall = package_env["marshall"];
    do_unmarshall = package_env["unmarshall"];
    initialized = true;
  }
  return do_marshall(x);
}

// [[Rcpp::export(rng=false)]]
SEXP unmarshall_dispatch(SEXP x) {
  if(!initialized) {
    package_env = Rcpp::Environment("package:CustomSerialization");
    do_marshall = package_env["marshall"];
    do_unmarshall = package_env["unmarshall"];
    initialized = true;
  }
  return do_unmarshall(x);
}

