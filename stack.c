/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Fall 2017 -- Project Zero -- Stack Main File
 * @description: Functions that can perform operations on the stack
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"
//#include "integerClass/integer.h"

struct stack {
  DA *vector;
  void (*display)(FILE *, void*);
};

STACK *newSTACK(void (*d)(FILE *, void *)) {
  assert( sizeof(STACK) != 0 );

  STACK *myStack = malloc( sizeof(STACK) );
  myStack->vector = newDA(d);
  myStack->display = d;

  return myStack;
}

void push(STACK *items, void *value) {
  insertDA(items->vector, value);
}

void *pop(STACK *items) {
  assert( sizeDA(items->vector) > 0 );
  void *popVal = removeDA(items->vector);
  return popVal;
}

void *peekSTACK(STACK *items) {
  assert( sizeDA(items->vector) > 0 );
  int index = sizeDA(items->vector);
  return getDA(items->vector, index - 1);
}

int sizeSTACK(STACK *items) {
  return sizeDA(items->vector);
}

void displaySTACK(FILE *fp, STACK *items) {
//  getDA(items->vector, 0);
/******************************************************************************/

  fprintf(fp, "|");

  if (sizeDA(items->vector) != 0) {
    int vectorSize = sizeDA(items->vector);
    int i;
    for (i = 0; i < vectorSize; i++ ) {
      void *element = getDA(items->vector, (vectorSize - 1) - i);
      items->display(fp, element);
      if (i != sizeSTACK(items) - 1) { fprintf(fp, ","); }
    }
  }

  fprintf(fp, "|");

/******************************************************************************/
}

void visualizeSTACK(FILE *fp, STACK *items) {
  displayDA(fp, items->vector);
}