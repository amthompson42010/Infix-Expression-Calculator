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
    printf("DA tester: 1,6\n");
    printf("you can retrieve this test with:\n");
    printf("wget beastie.cs.ua.edu/cs201/testing/0/da-test-1-6.c\n");
    printf("\noutput:\n\n");
    DA *d = newDA(displayINTEGER);
    insertDA(d,newINTEGER(189));
    insertDA(d,newINTEGER(468));
    insertDA(d,newINTEGER(583));
    insertDA(d,newINTEGER(868));
    insertDA(d,newINTEGER(885));
    insertDA(d,newINTEGER(35));
    insertDA(d,newINTEGER(592));
    insertDA(d,newINTEGER(686));
    insertDA(d,newINTEGER(32));
    insertDA(d,newINTEGER(874));
    insertDA(d,newINTEGER(222));
    insertDA(d,newINTEGER(631));
    insertDA(d,newINTEGER(281));
    insertDA(d,newINTEGER(719));
    insertDA(d,newINTEGER(909));
    insertDA(d,newINTEGER(828));
    insertDA(d,newINTEGER(395));
    insertDA(d,newINTEGER(481));
    insertDA(d,newINTEGER(674));
    insertDA(d,newINTEGER(442));
    insertDA(d,newINTEGER(346));
    printf("array d:");
    visualizeDA(stdout,d);
    printf("\n");
    int size = sizeDA(d);
    printf("extracting the underlying array\n");
    void **a = extractDA(d);
    void *p = a[0];
    printf("the first element of the extracted array: ");
    displayINTEGER(stdout,p);
    printf("\n");
    p = a[size-1];
    printf("the last element of the extracted array: ");
    displayINTEGER(stdout,p);
    printf("\n");
    printf("array d:");
    visualizeDA(stdout,d);
    printf("\n");
    return 0;
    }