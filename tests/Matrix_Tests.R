f <- function(arg1, arg2) {
  print(paste(Reduce(paste, arg1), ",", arg2))
  print(matrix(arg1, arg2))
  cat("\n")
}

f(c(1, 2, 3, 4), 4)
f(c(1, 2, 3), 4)
f(c(1, 2, 3), 6)
f(c(1, 2, 3, 4, 5, 6, 7, 8), 4)
f(c(1, 2, 3, 4, 5, 6, 7, 8), 5)
