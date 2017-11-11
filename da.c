/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Fall 2017 -- Project 0 -- Dynamic Array File
 * @descirption: Public Interface of functions to perform on a dynamic array.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "da.h"

struct da {
  void (*display)(FILE *, void*);
  int size;
  int filledIndices;
  void **array;
};

DA *newDA(void (*d)(FILE *, void *)) {
  assert( sizeof(DA) != 0 );

  DA *arr = malloc( sizeof(DA) );

  arr->array = malloc( 1 * sizeof(void*) );
  arr->display = d;
  arr->size = 1;
  arr->filledIndices = 0;

  return arr;
}

void insertDA(DA *items, void *value) {
  assert(sizeof(void*) * items->size * 2 != 0);

  //If there is room in the array for the insert
  if ( items->filledIndices < items->size ) {
    items->array[items->filledIndices] = value;
    items->filledIndices += 1;
  }

  else {

    items->array = realloc( items->array, 2 * items->size * sizeof(void*) );

    items->array[items->filledIndices] = value;

    items->size *= 2;
    items->filledIndices += 1;
  }

  return;
}

void *removeDA(DA *items) {
  //FIXME: The rubric says that the array should never shrink below the size of 1...what about initiaizing it to size 0?
  assert(items->filledIndices > 0);

  void *tmp = items->array[items->filledIndices-1];
  items->array[items->filledIndices-1] = NULL;
  items->filledIndices -= 1;

  if (items->filledIndices < items->size * .25 && items->size != 1) {
    items->array = realloc( items->array, (items->size/2) * sizeof(void*) );
    items->size /= 2;
  }

  return tmp;
}


void unionDA(DA *recipient, DA *donor) {
//  int totalSize = recipient->size + donor->size;
//  int totalFilled = recipient->size + donor->size;
/*
  recipient->array = realloc( recipient->array, totalSize * sizeof(void*) );
  recipient->size = totalSize;
*/

  int i;
  for (i = 0; i < donor->filledIndices; i++) {
    insertDA(recipient, donor->array[i]);
  }

  donor->array = realloc( donor->array, sizeof(void*) );
  donor->size = 1;
  donor->filledIndices = 0;
}

void *getDA(DA *items, int index) {
  assert(index >= 0 && index < items->filledIndices);
  return items->array[index];
}

void *setDA(DA *items, int index, void *value) {
  assert(index >= 0 && index <= items->filledIndices);  //FIXME: Add assertion that the index shall be >= 0 and <= size

  void *replacedVal;

  if (index == items->filledIndices) {
    insertDA(items, value);
    replacedVal = NULL;
  }
  else {
    replacedVal = items->array[index];
    items->array[index] = value;
  }

  return replacedVal;
}

void **extractDA(DA *items) {
  if (items->filledIndices == 0) {
    return 0;
  }
   assert( items->filledIndices * sizeof(void*) != 0 );

   items->array = realloc( items->array, items->filledIndices * sizeof(void*) );
   void **newArr = items->array;
   items->array = realloc( items->array, sizeof(void*) );
   items->size = 1;
   items->filledIndices = 0;

   return newArr;
}

int sizeDA(DA *items) {
  return items->filledIndices;
}

void visualizeDA(FILE *fp, DA *items) {
  int remaining = items->size - items->filledIndices;

  fprintf(fp, "[");

  if (items->filledIndices != 0) {
    int i;
    for (i = 0; i < items->filledIndices; i++) {
      items->display(fp, items->array[i]);
      if (i != items->filledIndices - 1) { fprintf(fp, ","); }
    }
  }

  fprintf(fp, "]");

  fprintf(fp, "[%d]", remaining);
}

void displayDA(FILE *fp, DA *items) {
  fprintf(fp, "[");

  if (items->filledIndices != 0) {
    int i;
    for (i = 0; i < items->filledIndices; i++) {
      items->display(fp, items->array[i]);
      if (i != items->filledIndices - 1) { fprintf(fp, ","); }
    }
  }

  fprintf(fp, "]");
}