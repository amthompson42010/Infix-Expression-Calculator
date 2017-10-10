/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Fall 2017 -- Project Zero -- Stack Main File
 * @description: Functions that can perform operations on the stack
 */

#include "stack.h"
#include "da.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct stack 
{
    DA *stackArray;
    void (*display)(FILE *, void*);
};

STACK *newSTACK(void (*d)(FILE *, void *))
{
    assert(sizeof(STACK) != 0);

    STACK *myStack = malloc(sizeof(STACK));
    myStack->stackArray = newDA(d);
    myStack->display = d;

    return myStack;
}

void push(STACK *items, void *value)
{
    insertDA(items->stackArray, value);
}

void *pop(STACK *items)
{
    assert(sizeDA(items->stackArray) > 0);
    void *popValue = removeDA(items->stackArray);
    return popValue;
}

void *peekSTACK(STACK *items)
{
    assert(sizeDA(items->stackArray) > 0);
    int index = sizeDA(items->stackArray);
    return getDA(items->stackArray, index - 1);
}

int sizeSTACK(STACK *items)
{
    return sizeDA(items->stackArray);
}

void displaySTACK(FILE *fp, STACK *items)
{
    fprintf(fp, "|");

    if(sizeDA(items->stackArray) != 0)
    {
        int arraySize = sizeDA(items->stackArray);
        int i;
        for(i = 0; i < arraySize; i++)
        {
            void *elem = getDA(items->stackArray, (arraySize - 1) - i);
            items->display(fp, elem);
            if(i != sizeSTACK(items) - 1) { fprintf(fp, ","); }
        }
    }

    fprintf(fp, "|");
}

void visualizeSTACK(FILE *fp, STACK *items)
{
    displayDA(fp, items->stackArray);
}
