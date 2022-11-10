#
# Simple Makefile for compiling programs for initio robot car 
#
SHELL	= bash
GCC	= gcc
CFLAGS	= -Wall -Werror -mfloat-abi=hard
LFLAGS	= -linitio -lcurses -lwiringPi -lpthread

PROG 	= testIR

.PHONY: all run help

all: $(PROG)

run: $(PROG)
	./$<

% : %.c
	$(GCC) -o $@ $(CFLAGS) $(LFLAGS) $<

clean:
	rm -f $(PROG)

help:
	@echo
	@echo "Possible commands:"
	@echo " > make run"
	@echo " > make clean"
	@echo

