#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

/*
 attribute_hidden SEXP do_setseed (SEXP call, SEXP op, SEXP args, SEXP env)
 {
 SEXP skind, nkind, sampkind;
 int seed;
 
 checkArity(op, args);
 if(!isNull(CAR(args))) {
 seed = asInteger(CAR(args));
 if (seed == NA_INTEGER)
 error(_("supplied seed is not a valid integer"));
 } else seed = TimeToSeed();
 skind = CADR(args);
 nkind = CADDR(args);
 sampkind = CADDDR(args);
 GetRNGkind(R_NilValue); // pull RNG_kind, N01_kind from .Random.seed if present 
if (!isNull(skind)) RNGkind((RNGtype) asInteger(skind));
if (!isNull(nkind)) Norm_kind((N01type) asInteger(nkind));
if(!isNull(sampkind)) Samp_kind((Sampletype) asInteger(sampkind));
RNG_Init(RNG_kind, (Int32) seed); // zaps BM history 
PutRNGstate();
return R_NilValue;
}
*/

// [[Rcpp::export]]
void own_do_setseed(SEXP call, SEXP op, SEXP args, SEXP env) {
  int seed = 0;
  if ( TYPEOF(args) != NILSXP ) {
    seed = Rf_asInteger(args);
  }
  
  RNG_Init(1, 1234);

}

/*** R
# set.seed(1234, "Super-Duper", "Inversion", "Rejection") # 1234, 2, 4, 1
.Internal(set.seed(1234, 2, 4, 1))
own_do_setseed(1234, 2, 4L, 1)
*/
