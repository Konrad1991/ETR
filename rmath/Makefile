# Makefile for building the rmath library

# Compiler and flags
CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -pedantic -DMATHLIB_STANDALONE
INCLUDE := -I./include -I./src -I./src/R_ext

# Source files
SRC := $(wildcard src/*.c)

# Object files
OBJ := $(SRC:.c=.o)

# Library name and target
LIB_NAME := librmath.a

# Targets
all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

install:
	# Add installation steps here, if needed

clean:
	rm -f $(LIB_NAME) $(OBJ)

.PHONY: all install clean
