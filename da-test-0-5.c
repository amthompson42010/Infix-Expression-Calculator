#include <stdio.h>
#include <stdlib.h>
#include "da.h"
#include "integer.h"
#include "real.h"
#include "string.h"
extern long random(void);
extern void srandom(unsigned int seed);

int
main(void)
    {
    printf("DA tester: 0,5\n");
    printf("you can retrieve this test with:\n");
    printf("wget beastie.cs.ua.edu/cs201/testing/0/da-test-0-5.c\n");
    printf("\noutput:\n\n");
    DA *d = newDA(displayINTEGER);
    insertDA(d,newINTEGER(985));
    insertDA(d,newINTEGER(112));
    insertDA(d,newINTEGER(665));
    insertDA(d,newINTEGER(308));
    insertDA(d,newINTEGER(285));
    insertDA(d,newINTEGER(286));
    insertDA(d,newINTEGER(43));
    insertDA(d,newINTEGER(2));
    insertDA(d,newINTEGER(778));
    insertDA(d,newINTEGER(935));
    insertDA(d,newINTEGER(323));
    insertDA(d,newINTEGER(605));
    insertDA(d,newINTEGER(93));
    insertDA(d,newINTEGER(842));
    insertDA(d,newINTEGER(616));
    insertDA(d,newINTEGER(400));
    insertDA(d,newINTEGER(92));
    insertDA(d,newINTEGER(23));
    insertDA(d,newINTEGER(944));
    insertDA(d,newINTEGER(951));
    insertDA(d,newINTEGER(270));
    printf("array d:");
    visualizeDA(stdout,d);
    printf("\n");
    void *x = 0;
    x = getDA(d,sizeDA(d)-1);
    printf("last element is ");
    displayINTEGER(stdout,x);
    printf("\n");
    void *y = 0;
    y = getDA(d,0);
    printf("first element is ");
    displayINTEGER(stdout,y);
    printf("\n");
    printf("swapping first and last elements\n");
    x = setDA(d,0,x);
    y = setDA(d,sizeDA(d)-1,y);
    printf("array d:");
    visualizeDA(stdout,d);
    printf("\n");
    printf("setting the first available slot\n");
    y = setDA(d,sizeDA(d),newINTEGER(540));
    printf("array d:");
    visualizeDA(stdout,d);
    printf("\n");
    return 0;
    }
