#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "integer.h"
#include "string.h"
extern long random(void);
extern void srandom(unsigned int seed);

int
main(void)
    {
    printf("QUEUE tester: 0,0\n");
    printf("you can retrieve this test with:\n");
    printf("wget beastie.cs.ua.edu/cs201/testing/0/queue-test-0-0.c\n");
    printf("\noutput:\n\n");
    QUEUE *d = newQUEUE(displayINTEGER);
    enqueue(d,newINTEGER(886));
    enqueue(d,newINTEGER(777));
    enqueue(d,newINTEGER(915));
    enqueue(d,newINTEGER(793));
    enqueue(d,newINTEGER(335));
    enqueue(d,newINTEGER(386));
    enqueue(d,newINTEGER(492));
    enqueue(d,newINTEGER(649));
    displayQUEUE(stdout,d);
    printf("\n");
    return 0;
    }
