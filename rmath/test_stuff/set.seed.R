set.seed <- function (seed, kind = NULL, normal.kind = NULL, sample.kind = NULL){
    kinds <- c("Wichmann-Hill", "Marsaglia-Multicarry", "Super-Duper", 
        "Mersenne-Twister", "Knuth-TAOCP", "user-supplied", "Knuth-TAOCP-2002", 
        "L'Ecuyer-CMRG", "default")
    n.kinds <- c("Buggy Kinderman-Ramage", "Ahrens-Dieter", "Box-Muller", 
        "user-supplied", "Inversion", "Kinderman-Ramage", "default")
    s.kinds <- c("Rounding", "Rejection", "default")
    if (length(kind)) {
        if (!is.character(kind) || length(kind) > 1L) 
            stop("'kind' must be a character string of length 1 (RNG to be used).")
        if (is.na(i.knd <- pmatch(kind, kinds) - 1L)) 
            stop(gettextf("'%s' is not a valid abbreviation of an RNG", 
                kind), domain = NA)
        if (i.knd == length(kinds) - 1L) 
            i.knd <- -1L
    }
    else i.knd <- NULL
    if (!is.null(normal.kind)) {
        if (!is.character(normal.kind) || length(normal.kind) != 
            1L) 
            stop("'normal.kind' must be a character string of length 1")
        normal.kind <- pmatch(normal.kind, n.kinds) - 1L
        if (is.na(normal.kind)) 
            stop(gettextf("'%s' is not a valid choice", normal.kind), 
                domain = NA)
        if (normal.kind == 0L) 
            stop("buggy version of Kinderman-Ramage generator is not allowed", 
                domain = NA)
        if (normal.kind == length(n.kinds) - 1L) 
            normal.kind <- -1L
    }
    if (!is.null(sample.kind)) {
        if (!is.character(sample.kind) || length(sample.kind) != 
            1L) 
            stop("'sample.kind' must be a character string of length 1")
        sample.kind <- pmatch(sample.kind, s.kinds) - 1L
        if (is.na(sample.kind)) 
            stop(gettextf("'%s' is not a valid choice", sample.kind), 
                domain = NA)
        if (sample.kind == 0L) 
            warning("non-uniform 'Rounding' sampler used", domain = NA)
        if (sample.kind == length(s.kinds) - 1L) 
            sample.kind <- -1L
    }
    print(seed)
    print(i.knd)
    print(normal.kind)
    print(sample.kind)
    .Internal(set.seed(seed, i.knd, normal.kind, sample.kind)) # this is in main/names.c --> do_setseed
}

set.seed(1234)
set.seed(1234, "Super-Duper", "Inversion", "Rejection")
