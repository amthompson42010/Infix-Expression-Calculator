

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "integer.h"

static void displayItems(QUEUE *);
static void visualizeItems(QUEUE *);
static void testEnqueueDequeuePeek(QUEUE *);

int main(void) {
  QUEUE *items = newQUEUE(displayINTEGER);
  testEnqueueDequeuePeek(items);
  return 0;
}

static void testEnqueueDequeuePeek(QUEUE *items) {
  int i;

  // Display empty QUEUE
  displayItems(items);
  visualizeItems(items);
  printf("The size is %d.\n", sizeQUEUE(items));
  printf("\n");

  // Add 100 values in
  for (i = 0; i < 100; i++)
    enqueue(items, newINTEGER(i));
  displayItems(items);
  visualizeItems(items);
  printf("\n");

  // Show the last value
  int x = getINTEGER((INTEGER *) peekQUEUE(items));
  printf("The last item is %d.\n", x);
  printf("The size is %d.\n", sizeQUEUE(items));

  // Remove the last value
  printf("The value ");
  displayINTEGER(stdout, dequeue(items));
  printf(" was removed.\n");
  printf("The size is %d.\n", sizeQUEUE(items));

  // Remove the rest
  for (i = 0; i < 99; i++)
    dequeue(items);
  displayItems(items);
  visualizeItems(items);
  printf("\n");

  // Add 10 values back in
  for (i = 0; i < 10; i++)
    enqueue(items, newINTEGER(i));
  displayItems(items);
  visualizeItems(items);
  printf("\n");
}

static void displayItems(QUEUE *items) {
  printf("displayQUEUE: ");
  displayQUEUE(stdout,items);
  printf("\n");
}

static void visualizeItems(QUEUE *items) {
  printf("visualizeQUEUE: ");
  visualizeQUEUE(stdout,items);
  printf("\n");
}
