library(dfdr)

f <- function(a) sin(a)
a <- c(3.141593, 6.283185, 9.424778, 12.566371)
f(a)
fd <- d(f, a)
fd(a)


f <- function(a) sin(a*a)
a <- c(3.141593, 6.283185, 9.424778, 12.566371)
f(a)
fd <- d(f, a)
fd(a)
