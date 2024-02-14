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
    GetRNGkind(R_NilValue); /* pull RNG_kind, N01_kind from
			       .Random.seed if present */
    if (!isNull(skind)) RNGkind((RNGtype) asInteger(skind));
    if (!isNull(nkind)) Norm_kind((N01type) asInteger(nkind));
    if(!isNull(sampkind)) Samp_kind((Sampletype) asInteger(sampkind));
    RNG_Init(RNG_kind, (Int32) seed); /* zaps BM history */
    PutRNGstate();
    return R_NilValue;
}


