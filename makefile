CCFLAGS ?= -std=c99 -Werror -Wall 

all: prog

test: all
	./prog

prog_prepro.c: fun_macros.c test.def fun_macros.h
	$(CC) $(CCFLAGS) fun_macros.c -o prog_prepro.c -E

prog: prog_prepro.c
	$(CC) $(CCFLAGS) prog_prepro.c -o prog -lpthread

