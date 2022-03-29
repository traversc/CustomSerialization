#include "altrepisode.h"
#include "marshall_dispatch.h"

// instead of defining a set of free functions, we structure them
// together in a struct
struct altrep_scaffold {

  // The altrep class that wraps a pointer to a std::vector<double>
  static R_altrep_class_t class_t;

  // Make an altrep object of class `altrep_scaffold::class_t`
  // owner parameter doesn't matter
  static SEXP Make(SEXP xp, bool owner) {
    
    // make a new altrep object of class `altrep_scaffold::class_t`
    // in the usual case, data1 is a EXTPTRSXP, but there's nowhere that says it needs to be
    // here it's literally any object
    SEXP res = R_new_altrep(class_t, xp, Rf_allocVector(RAWSXP, 0));

    return res;
  }

  // finalizer for the external pointer
  static void Finalize(SEXP xp){
    // nothing, data is protected as it's an SEXP and part of the ALTREP object structure
  }

  // Convienence
  static SEXP Get(SEXP x) {
    return R_altrep_data1(x);
  }

  // ALTREP methods -------------------

  // The length of the object
  static R_xlen_t Length(SEXP vec){
    return 0;
  }

  // What gets printed when .Internal(inspect()) is used
  static Rboolean Inspect(SEXP x, int pre, int deep, int pvec, void (*inspect_subtree)(SEXP, int, int, int)){
    Rprintf("ALTREP scaffold\n");
    return TRUE;
  }

  // ALTVEC methods ------------------

  // The start of the data, i.e. the underlying double* array from the std::vector<double>
  //
  // This is guaranteed to never allocate (in the R sense)
  static const void* Dataptr_or_null(SEXP vec){
    return R_altrep_data2(vec);
  }

  // same in this case, writeable is ignored
  static void* Dataptr(SEXP vec, Rboolean writeable){
    return R_altrep_data2(vec);
  }

  

  // ALTREAL methods -----------------
  
  static SEXP altrep_UnserializeEX(SEXP info, // info (altrep info)
                            SEXP state, // state (marshalled state)
                            SEXP attributes, // attributes
                            int flags,  // object flags
                            int levels)  // levels (i.e. more flags)
  {
    return Make(unmarshall_dispatch(state), false);
  }
  static SEXP serialized_state(SEXP x) {
    return marshall_dispatch(R_altrep_data1(x));
  }

  static void Init(DllInfo* dll){
    class_t = R_make_altraw_class("altrep_scaffold", "CustomSerialization", dll);

    // altrep
    R_set_altrep_Length_method(class_t, Length);
    R_set_altrep_Inspect_method(class_t, Inspect);

    // altvec
    R_set_altvec_Dataptr_method(class_t, Dataptr);
    R_set_altvec_Dataptr_or_null_method(class_t, Dataptr_or_null);
    
    // serialization
    R_set_altrep_UnserializeEX_method(class_t, altrep_UnserializeEX);
    R_set_altrep_Serialized_state_method(class_t, serialized_state);
    
    // altraw
    // R_set_altraw_Elt_method(class_t, raw_Elt);
    // R_set_altreal_Get_region_method(class_t, Get_region);
  }

};

// static initialization of altrep_scaffold::class_t
R_altrep_class_t altrep_scaffold::class_t;

// [[Rcpp::init]]
void init_CustomSerialization(DllInfo* dll){
  altrep_scaffold::Init(dll);
}

// [[Rcpp::export(rng=false)]]
SEXP make_altrep_scaffold(SEXP x) {
  return altrep_scaffold::Make(x, false);
}

// [[Rcpp::export(rng=false)]]
SEXP altrep_scaffold_data(SEXP x) {
  return R_altrep_data1(x);
}


