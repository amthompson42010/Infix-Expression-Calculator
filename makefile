OPTS = -Wall -Wextra -std=c99
TYPE_OBJS = integer.o real.o string.o char.o
UTIL_OBJS = scanner.o
STRUCT_OBJS = da.o cda.o stack.o queue.o bst.o
TESTOBJS = test-bst.o test-matilda.o
TESTEXES = testBST matilda ./a.out

all: $(TYPE_OBJS) $(UTIL_OBJS) $(STRUCT_OBJS) matilda.o

test: $(TYPE_OBJS) $(UTIL_OBJS) $(STRUCT_OBJS) matilda.o $(TESTOBJS)
	./testBST
	./matilda -i -p -b testFileThree

matilda.o: matilda.c $(TYPE_OBJS) $(STRUCT_OBJS) $(UTIL_OBJS)
	gcc $(OPTS) matilda.c -lm $(TYPE_OBJS) $(STRUCT_OBJS) $(UTIL_OBJS) -o matilda

bst.o: bst.c bst.h
	gcc $(OPTS) -c bst.c

scanner.o: scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

char.o: char.c char.h
	gcc $(OPTS) -c char.c

string.o: string.c string.h
	gcc $(OPTS) -c string.c

real.o: real.c real.h
	gcc $(OPTS) -c real.c

integer.o: integer.c integer.h
	gcc $(OPTS) -c integer.c

da.o: da.c da.h
	gcc $(OPTS) -c da.c

cda.o: cda.c cda.h
	gcc $(OPTS) -c cda.c

stack.o: stack.c stack.h
	gcc $(OPTS) -c stack.c

queue.o: queue.c queue.h
	gcc $(OPTS) -c queue.c

clean:
	rm -rf *.o $(TESTEXES) runBSTtest

test-bst.o: bst.o
	gcc $(OPTS) test-bst.c scanner.o real.o string.o bst.o -lm -o testBST

test-matilda.o: matilda.o
	gcc $(OPTS) matilda.c -lm $(TYPE_OBJS) $(STRUCT_OBJS) $(UTIL_OBJS) -o matilda