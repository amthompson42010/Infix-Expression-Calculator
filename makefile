OBJSDA = integer.o da.o test-da.o
OBJSCDA = integer.o cda.o test-cda.o
OBJSQ = integer.o queue.o test-queue.o cda.o
OBJSSK = integer.o stack.o test-stack.o da.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g
OBJSQB = integer.o queue.o queue-test.o cda.o

test-da: $(OBJSDA)
	gcc $(LOPTS) -o test-da $(OBJSDA)

test-cda: $(OBJSCDA)
	gcc $(LOPTS) -o test-cda $(OBJSCDA)

test-queue: $(OBJSQ)
	gcc $(LOPTS) -o test-queue $(OBJSQ)

test-stack: $(OBJSSK)
	gcc $(LOPTS) -o test-stack $(OBJSSK)

queue-test: $(OBJSQB)
	gcc $(LOPTS) -o queue-test $(OBJSQB)

da.o: da.c da.h
	gcc $(OOPTS) da.c

cda.o: cda.c cda.h
	gcc $(OOPTS) cda.c

queue.o: queue.c queue.h cda.c
	gcc $(OOPTS) queue.c

stack.o: stack.c stack.h da.c
	gcc $(OOPTS) stack.c

integer.o: integer.c integer.h
	gcc $(OOPTS) integer.c

test-da.o: test-da.c integer.h da.c
	gcc $(OOPTS) test-da.c

test-cda.o: test-cda.c integer.h cda.c
	gcc $(OOPTS) test-cda.c

test-queue.o: test-queue.c integer.h cda.c queue.h
	gcc $(OOPTS) test-queue.c

test-stack.o: test-stack.c integer.h da.c stack.h
	gcc $(OOPTS) test-stack.c

queue-test.o: queue-test.c integer.h cda.c queue.h
	gcc $(OOPTS) queue-test.c

clean:
	rm -f *.o test-da test-cda test-queue test-stack

test:
	echo
	echo "Testing dynamic array"
	make test-da
	./test-da
	echo
	echo "Testing circular dynamic array"
	make test-cda
	./test-cda
	echo
	echo "Testing queue"
	make test-queue
	./test-queue
	echo
	echo "Testing stack"
	make test-stack
	./test-stack
	echo
	echo "Previous Test"
	make queue-test
	./queue-test
	echo
