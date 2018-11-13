#!/usr/bin/make

# Fortran
# FC     = gfortran
# FFLAGS = -O3 -fopenmp -lm

# C
CC     = gcc
CFLAGS = -fopenmp

# From all .c files in direcrtory
# generate the executable name without .c
EXE = $(patsubst %.c,%,$(wildcard *.c))

# Main rule
all: $(EXE)
	@echo ""

# Compile each .c file
$(EXE):%:%.c
	@echo "\n$(BOLD_RED)Compiling$(RESET): $(BOLD_BLACK)$<$(RESET)"
	$(CC) $(CFLAGS) $< -o $@ -lm

# Clean
.PHONY: clean
clean:
	rm -f $(EXE)

BOLD_BLACK = \033[1m
BOLD_RED   = \033[1;31m
RESET      = \033[0m
