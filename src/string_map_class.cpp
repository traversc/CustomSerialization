#include <Rcpp.h>
// #include "marshall_dispatch.h"
using namespace Rcpp;

// Rcpp::Environment package_env("package:CustomSerialization");
// Rcpp::Environment package_env = Environment::global_env();
// static Rcpp::Function do_marshall = package_env["marshall"];

// [[Rcpp::export(rng=false)]]
XPtr<std::map<std::string, std::string>> c_make_map(List data) {
  if(data.size() != 2) stop("input should be a list with keys and values as character vectors");
  
  CharacterVector keys = data[0];
  CharacterVector values = data[1];
  
  if(keys.size() != values.size()) stop("key length should match value length");
  size_t size = keys.size();
  std::map<std::string, std::string> * map = new std::map<std::string, std::string>;
  auto & map_ref = *(map);
  
  for(size_t i=0; i<size; ++i) {
    map_ref[as<std::string>(keys[i])] = as<std::string>(values[i]);
  }
  return XPtr<std::map<std::string, std::string>>(map, true);
}

// [[Rcpp::export(rng=false)]]
void c_add_map(XPtr<std::map<std::string, std::string>> map, List data) {
  if(data.size() != 2) stop("input should be a list with keys and values as character vectors");
  
  CharacterVector keys = data[0];
  CharacterVector values = data[1];
  
  if(keys.size() != values.size()) stop("key length should match value length");
  size_t size = keys.size();
  
  auto & map_ref = *(map.get());
  for(size_t i=0; i<size; ++i) {
    map_ref[as<std::string>(keys[i])] = as<std::string>(values[i]);
  }
}

// [[Rcpp::export(rng=false)]]
List c_export_map_data(XPtr<std::map<std::string, std::string>> map) {
  auto & map_ref = *(map.get());
  size_t map_size = map_ref.size();
  
  std::vector<std::string> keys(map_size);
  std::vector<std::string> values(map_size);
  size_t i=0;
  for(auto & pair : map_ref) {
    keys[i] = pair.first;
    values[i] = pair.second;
    ++i;
  }
  return List::create(Rcpp::wrap(keys), Rcpp::wrap(values));
}

// [[Rcpp::export(rng=false)]]
void c_print_map(XPtr<std::map<std::string, std::string>> map) {
  for(auto & pair : *(map.get())) {
    Rcout << pair.first << "\t" << pair.second << std::endl;
  }
}