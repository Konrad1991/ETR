f <- function(arg1, arg2) {
  print(paste(Reduce(paste, arg1), ",", arg2))
  print(matrix(arg1, arg2))
  cat("\n")
}

# f(c(1, 2, 3, 4), 4)
# f(c(1, 2, 3), 4)
# f(c(1, 2, 3), 6)
# f(c(1, 2, 3, 4, 5, 6, 7, 8), 4)
# f(c(1, 2, 3, 4, 5, 6, 7, 8), 5)

matrix(data = 1, ncol = 3) |> print()
cat("\n")
matrix(data = c(1, 2, 3, 4), ncol = 3) |> print()

expr <- quote(matrix(nrow = 2, data = c(1, 2, 3, 4), ncol = 3))

# lc <- ast2ast:::LC$new(expr, TRUE)
# print(lc$ast)
# print(lc$ast2call())

expr <- quote(vector(length = 3))
as.list(expr)

expr <- quote(vector(3))
as.list(expr)


formals(vector)
