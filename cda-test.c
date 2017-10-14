#include <stdio.h>
#include <stdlib.h>
#include "cda.h"
#include "integer.h"
#include "real.h"
#include "string.h"
extern long random(void);
extern void srandom(unsigned int seed);

int
main(void)
    {
    printf("CDA tester: 1,10\n");
    printf("you can retrieve this test with:\n");
    printf("wget beastie.cs.ua.edu/cs201/testing/0/cda-test-1-10.c\n");
    printf("\noutput:\n\n");
    int count = 0;
    srandom(1011);
    CDA *d = newCDA(displayINTEGER);
    printf("doing a bunch of inserts\n");
    int i;
    for (i = 0; i < 15861; ++i)
        {
        insertCDAfront(d,newINTEGER(random()%1000));
        ++count;
        }
    for (i = 0; i < 15861; ++i)
        {
        insertCDAback(d,newINTEGER(random()%1000));
        ++count;
        }
    printf("randomly doing a bunch of inserts and deletes\n");
    void *p = 0;
    for (i = 0; i < 15861; ++i)
        {
        int mode = random() % 4 == 0;
        if (mode == 0)
            {
            insertCDAfront(d,newINTEGER(random()%1000));
            ++count;
            }
        else if (mode == 1)
            {
            insertCDAback(d,newINTEGER(random()%1000));
            ++count;
            }
        else if (mode == 2 && count > 0)
            {
            p = removeCDAfront(d);
            --count;
            }
        else if (count > 0)
            {
            p = removeCDAback(d);
            --count;
            }
        }
    printf("doing a bunch of removes\n");
    while (count > 10)
        {
        p = removeCDAback(d);
        --count;
        }
    printf("array d:");
    visualizeCDA(stdout,d);
    printf("\n");
    printf("the last element removed: ");
    displayINTEGER(stdout,p);
    printf("\n");
    return 0;
    }