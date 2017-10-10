/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Fall 2017 -- Project 0 -- Dynamic Array File
 * @descirption: Public Interface of functions to perform on a dynamic array.
 */

#include "da.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/****************************** Public Interface ********************************/

/**
 * Function to create/initialize a new dynamic array.
 * display -> the display function for the dynamic array.
 */
DA *
newDA(void (*d)(FILE *, void *))
{
    DA *items = malloc(sizeof(DA));
    assert(items != 0);
    items->size = 0;
    items->capacity = 1;
    items->display = d;
    items->data = malloc(sizeof(void *) * 1);
    assert(items->data != 0);
    return items;
}

/**
 * Function to insert into the dynamic array.
 * items -> the dynamic array
 * value -> value to be inserted
 */
void 
insertDA(DA *items, void *value)
{
    assert(sizeof(void *) * items->capacity * 2 != 0);

    if(items->size < items->capacity)
    {
        items->data[items->size] = value;
        items->size +=1;
    }
    else
    {
        items->data = realloc(items->data, 2 * items->capacity * sizeof(void*));
        items->data[items->size] = value;
        items->capacity *= 2;
        items->size += 1;
    }
    return;
}

/**
 * Function to remove a value out of the dynamic array.
 * If the ratio of size and capacity are less than or equal
 * to 25% then the array is shrunken by half.
 * items -> the dynamic array
 */
void *
removeDA(DA *items)
{
    assert(items->size > 0);

    void *temp = items->data[items->size - 1];
    items->data[items->size - 1] = NULL;
    items->size -= 1;

    if(items->size < items->capacity * .25)
    {
        items->data = realloc(items->data, (items->capacity / 2) * sizeof(void*));
        items->capacity /= 2;
    }

    return temp;
}


/**
 * Function to join to dynamic arrays.
 * recipient -> dynamic array to be merged into
 * donor -> dynamic array to be merged into the recipient
 */
void
unionDA(DA *recipient, DA *donor)
{
    int i;
    for(i = 0; i < donor->size; i++)
    {
        insertDA(recipient, donor->data[i]);
    }

    donor->data = realloc(donor->data, sizeof(void*));
    donor->capacity = 1;
    donor->size = 0;
}

/**
 * Function to a value at a particular index in the dynamic array.
 * items -> the dynamic array
 * index -> index to be found in the dynamic array
 */
void
*getDA(DA *items, int index)
{
    assert(index >= 0);
    assert(index < items->size);
    return items->data[index];
}

/**
 * Function to set a particular index to a specific value in the
 * dynamic array.
 * items -> the dynamic array
 * index -> the index to be found in the dynamic array
 * value -> the value to be inserted into the value at the given 
 *          index in the dynamic array
 */
void *
setDA(DA *items, int index, void *value)
{
    assert(index >= 0);
    assert(index <= items->size);

    void *oldValue;

    if(index == items->size)
    {
        insertDA(items, value);
        oldValue = NULL;
    }
    else
    {
        oldValue = items->data[index];
        items->data[index] = value;
    }

    return oldValue;
}

/**
 * Function to return a shrunken version of the current dynamic 
 * array. If capacity is greater than the size that means that
 * there is extra space in the array. This function is used
 * to take away that extra space.
 * items -> the dynamic array
 */
void **
extractDA(DA *items)
{
    if(items->size == 0)
    {
        return 0;
    }
    assert(items->size * sizeof(void*) != 0);

    items->data = realloc(items->data, items->size * sizeof(void*));
    void **separateArray = items->data;
    items->data = realloc(items->data, sizeof(void*));
    items->capacity = 1;
    items->size = 0;

    return separateArray;
}

/**
 * Function to get the size of the dynamic array.
 * items -> the dynamic array.
 */
int
sizeDA(DA *items)
{
    return items->size;
}

/**
 * Function to print out the dynamic array in a brackets, and the array's
 * size to the right in brackets.
 * fp -> the file pointer to print the array to
 * items -> the dynamic array
 */
void 
visualizeDA(FILE *fp, DA *items)
{
    int remainingSpace = items->capacity - items->size;
    fprintf(fp, "[");
    if(items->size != 0)
    {
        int i;
        for(i = 0; i < items->size; i++)
        {
            items->display(fp, items->data[i]);
            if(i != items->size - 1) { fprintf(fp, ","); }
        }
    }

    fprintf(fp, "]");
    fprintf(fp, "[%d]", remainingSpace);
}

/**
 * Function to display the dynamic array, but not the size of the array.
 * fp -> the file pointer to print the array to
 * items -> the dynamic array
 */
void
displayDA(FILE *fp, DA *items)
{
    int i;
    fprintf(fp, "[");
    for(i = 0; i < items->size; ++i)
    {
        items->display(fp, items->data[i]);
        if(i != items->size - 1) { fprintf(fp, ","); }
    }
    fprintf(fp, "]");
}
