CFLAGS=-m32 -g -O0

all:	func-example func-example.s

func-example.s: func-example.c
	gcc -o func-example.o -c $(CFLAGS) func-example.c
	objdump --disassemble func-example.o > func-example.s
	-rm func-example.o

func-example: func-example.c
	gcc -o func-example $(CFLAGS) func-example.c

clean:
	-rm func-example
	-rm func-example.s func-example.o
	-rm func-example2
