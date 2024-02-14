# Makefile for building the rmath library

CC := gcc
CXX := g++
CFLAGS := -std=c11 -Wall -Wextra -pedantic -DMATHLIB_STANDALONE
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -DMATHLIB_STANDALONE
INCLUDE := -I./include -I./src -I./src/R_ext

# Source files
SRC := $(wildcard src/*.c) $(filter-out src/%.c, $(wildcard src/*.cpp))

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

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

install:
	# Add installation steps here, if needed

clean:
	rm -f $(LIB_NAME) $(OBJ)

.PHONY: all install clean

