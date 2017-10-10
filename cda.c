/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Fall 2017 -- Project 0 -- Circular Dynamic Array
 * @description: Public Interface for a Circular Dynamic Array along with funcitons that can be performed on the data structure.
 */

#include "cda.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/************************ Public Interface *****************************/

/**
 * Function to create/initialize a new circular dynamic array.
 * d -> display function for the circular dynamic array.
 */
CDA *
newCDA(void (*d)(FILE *, void *))
{
    CDA *items = malloc(sizeof(CDA));
    assert(items != 0);
    items->size = 0;
    items->frontIndex = 0;
    items->backIndex = 0;
    items->capacity = 1;
    items->data = malloc(sizeof(void *) * 1);
    items->display = d;
    return items;
}

/**
 * Function to insert a value into the front of the circular dynamic
 * array.
 * items -> circular dynamic array
 * value -> value to be inserted into the circular dynamic array.
 */
void
insertCDAfront(CDA *items, void *value)
{
    assert( items->capacity * 2 * sizeof(void*) != 0 );

  if (items->size == 0) {
    items->data[items->size] = value;
    items->frontIndex = 0;
    items->backIndex = 0;
  }
  else {
    if (items->size < items->capacity) {
      if (items->frontIndex == 0) {
        items->frontIndex = items->capacity - 1;
        items->data[items->capacity - 1] = value;
      }
      else {
        items->data[items->frontIndex - 1] = value;
        items->frontIndex -= 1;
      }
    }
    else {
      void **tmp = malloc(items->capacity * 2 * sizeof(void*));

      int i;
      int origIndex = items->frontIndex;
      for (i = 0; i < items->size; i++) {
        tmp[i] = items->data[origIndex];
        if (origIndex == items->capacity - 1) { origIndex = 0; }
        else { origIndex += 1; }
      }

      items->backIndex = i - 1;
      items->data = realloc( items->data, 2 * items->capacity * sizeof(void*));
      items->data = tmp;
      items->capacity *= 2;

      items->data[items->capacity - 1] = value;
      items->frontIndex = items->capacity - 1;
    }
  }

  items->size += 1;
}

void 
insertCDAback(CDA *items, void *value)
{
    assert(items->capacity * 2 * sizeof(void*) != 0);

    if(items->size == 0)
    {
        items->data[0] = value;
        items->frontIndex = 0;
        items->backIndex = 0;
    }
    else
    {
        if(items->size < items->capacity)
        {
            if(items->backIndex == items->capacity - 1)
            {
                items->backIndex = 0;
                items->data[items->backIndex] = value;
            }
            else
            {
                items->data[items->backIndex + 1] = value;
                items->backIndex += 1;
            }
        }
        else
        {
            void **temp = malloc(items->capacity * 2 * sizeof(void*));

            int i;
            int firstIndex = items->frontIndex;
            for(i = 0; i < items->size; i++)
            {
                temp[i] = items->data[firstIndex];
                if(firstIndex == items->capacity - 1) { firstIndex = 0; }
                else { firstIndex += 1; }
            }

            items->backIndex = items->size;
            items->frontIndex = 0;
            items->data = realloc(items->data, 2 * items->capacity * sizeof(void*));
            items->data = temp;
            items->capacity *= 2;

            items->data[items->size] = value;
        }
    }

    items->size += 1;
}

void *
removeCDAfront(CDA *items) 
{
    assert(items->size > 0);

    void *valueToReturn = NULL;

    if(items->size == 0)
    {
        items->backIndex = 0;
        items->frontIndex = 0;
        valueToReturn = NULL;
    }
    else
    {
        if(items->size - 1 < .25 * items->size)
        {
            void **temp = malloc(items->size / 2 * sizeof(void*));

            int i;
            int firstIndex = items->frontIndex;
            for(i = 0; i < items->size; i++)
            {
                temp[i] = items->data[firstIndex];
                if(firstIndex == items->capacity - 1) { firstIndex = 0; }
                else { firstIndex += 1; }
            }

            items->capacity /= 2;
            items->data = realloc(items->data, items->capacity * sizeof(void*));
            items->data = temp;
            items->frontIndex = 0;
            items->backIndex = items->size - 2;
        }

        valueToReturn = items->data[items->frontIndex];
        items->data[items->frontIndex] = NULL;
        items->size -= 1;
        
        if(items->frontIndex + 1 == items->capacity) { items->frontIndex = 0; }
        else { items->frontIndex += 1; }
    }

    return valueToReturn;
}

void *
removeCDAback(CDA *items)
{
    assert(items->size > 0);

    void *valueToReturn = NULL;

    if(items->size == 0)
    {
        items->backIndex = 0;
        items->frontIndex = 0;
        return NULL;
    }
    else{
        if(items->size - 1 < .25 * items->size)
        {
            void **temp = malloc(items->capacity / 2 * sizeof(void*));

            int i;
            int firstIndex = items->frontIndex;
            for(i = 0; i < items->size; i++)
            {
                temp[i] = items->data[firstIndex];
                if(firstIndex == items->capacity - 1) { firstIndex = 0; }
                else { firstIndex += 1; }
            }

            items->capacity /= 2;;
            items->data = realloc(items->data, items->capacity * sizeof(void *));
            items->data = temp;
            items->frontIndex = 0;
            items->backIndex = items->size - 1;
        }

        valueToReturn = items->data[items->backIndex];
        items->data[items->backIndex] = NULL;

        if(items->backIndex - 1 < 0) { items->backIndex = items->capacity - 1; }
        else { items->backIndex -= 1; }
    }

    items->size -= 1;

    return valueToReturn;
}

void 
unionCDA(CDA *recipient, CDA *donor)
{
    if(donor->size == 0)
    {
        donor->frontIndex = 0;
        donor->backIndex = 0;
        donor->size = 0;
        donor->capacity = 0;

        return;
    }

    int index = donor->frontIndex;

    int i;
    for(i = 0; i < donor->size; i++)
    {
        insertCDAback(recipient, donor->data[index]);
        if(index + 1 == donor->size) { index = 0; }
        else { index += 1; }
    }

    donor->data = extractCDA(donor);
}

void *
getCDA(CDA *items, int index)
{
    assert(index >= 0 && index < items->size);
    return items->data[items->frontIndex + index];
}

void *
setCDA(CDA *items, int index, void *value)
{
    assert(index >= -1 && index <= items->size);

    void *valueToReturn = 0;
    if(index == items->capacity)
    {
        insertCDAback(items, value);
    }
    else if(index == -1)
    {
        insertCDAfront(items, value);
    }
    else
    {
        valueToReturn = items->data[index];
        items->data[index] = value;
    }

    return valueToReturn;
}

void **
extractCDA(CDA *items)
{
    int numberOfIterations = items->size;

    if(items->size == 0)
    {
        return 0;
    }
    assert(items->size * sizeof(void*) != 0);
    void **temp = malloc(items->size * sizeof(void*));

    int i;
    int firstIndex = items->frontIndex;
    for(i = 0; i < items->size; i++)
    {
        temp[i] = items->data[firstIndex];
        if(firstIndex == items->capacity - 1) { firstIndex = 0; }
        else { firstIndex += 1; }
    }

    for(i = 0; i < numberOfIterations; i++)
    {
        removeCDAback(items);
    }

    items->capacity = 1;
    items->frontIndex = 0;
    items->backIndex = 0;
    items->size = 0;

    return temp;
}

int 
sizeCDA(CDA *items)
{
    return items->size;
}

void 
visualizeCDA(FILE *fp, CDA *items)
{
    fprintf(fp, "(");

    if(items->size != 0)
    {
        int index = 0;
        int i = items->frontIndex;
        while(index < items->size)
        {
            items->display(fp, items->data[i]);
            if(index != items->size - 1) { fprintf(fp, ","); }
            i += 1;
            index += 1;
            if(i == items->capacity) { i = 0; }
        }
    }
    fprintf(fp, ")");

    int remainder = items->capacity - items->size;

    fprintf(fp, "(%d)", remainder);
}

void 
displayCDA(FILE *fp, CDA *items)
{
    fprintf(fp, "(");

    if(items->size != 0)
    {
        int index = 0;
        int i = items->frontIndex;
        while(index < items->size)
        {
            items->display(fp, items->data[i]);
            if(index != items->size - 1) { fprintf(fp, ","); }
            i += 1;
            index += 1;
            if(i == items->capacity) { i = 0; }
        }
    }

    fprintf(fp, ")");
}
