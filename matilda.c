/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 Fall 2017 Assignment 1
 * @description: Main file to run the infix expression calculator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#include "stack.h"
#include "bst.h"
#include "queue.h"
#include "integer.h"
#include "string.h"
#include "real.h"
#include "scanner.h"


// All of these functions are defined below the main.
static void readInFile(FILE *, QUEUE *);       
static int priorityOf(char c);

void populateBST(FILE *, BST *);                
void printInput(QUEUE *);                       
QUEUE *convertToPostfix(QUEUE *);
QUEUE *getLastLine(QUEUE *);                    
char *processPostFix(QUEUE *queue, BST *tree);  
void displayPair(FILE *, void *, void *);
STRING *evaluate(double, double, char);


int main(int argc, char *argv[]) {
  
  // Author name option
  int i;
  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) { printf("Alexander Mark Thompson\n"); return 0; }
  }


  
  if (argc == 1) { return 0; }

  
  char *name = argv[argc - 1];
  FILE *fp1 = fopen(name, "r");
  BST *tree = newBST(displayPair, compareSTRING);
  populateBST(fp1, tree);

  if (fp1 != NULL) fclose(fp1);

  // Iteratinig through the rest of the comand line arguments
  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-b") == 0) {

      char *filename = argv[argc - 1];
      FILE *fp = fopen(filename, "r");

      QUEUE *queue = newQUEUE(displaySTRING);
      readInFile(fp, queue);

      displayBST(stdout, tree);
      printf("\n");

      if (fp != NULL) fclose(fp);
    }
    else if (strcmp(argv[i], "-i") == 0) {

      char *filename = argv[argc - 1];
      FILE *fp = fopen(filename, "r");

      QUEUE *queue = newQUEUE(displaySTRING);
      readInFile(fp, queue);

      printInput(queue);

      if (fp != NULL) fclose(fp);
    }
    else if (strcmp(argv[i], "-p") == 0) {

      char *filename = argv[argc - 1];
      FILE *fp = fopen(filename, "r");

      QUEUE *queue = newQUEUE(displaySTRING);
      readInFile(fp, queue);

      QUEUE *lastLine = getLastLine(queue);
      QUEUE *postFixExpr = convertToPostfix(lastLine);

      while (sizeQUEUE(postFixExpr) > 0) {
        displaySTRING(stdout, dequeue(postFixExpr));
        printf(" ");
      }
      printf("\n");

      if (fp != NULL) fclose(fp);
    }
  }

  char *file1 = argv[argc - 1];
  FILE *fptr = fopen(file1, "r");

  QUEUE *queue2 = newQUEUE(displaySTRING);
  readInFile(fptr, queue2);

  QUEUE *finalLine = getLastLine(queue2);
  QUEUE *postExpr = convertToPostfix(finalLine);

  if (sizeQUEUE(postExpr) > 1) {
    char *finalVal = processPostFix(postExpr, tree);
    printf("%s\n", finalVal);
  }
  else {
    char *string = getSTRING(peekQUEUE(postExpr));
    char chr = *string;
    if (isalpha(chr)) {
      REAL *r = findBST(tree, newSTRING(string));
      if (r == NULL) {
        printf("variable %s was not declared\n", string);
        return 0;
      }
      displayREAL(stdout, r);
      printf("\n");
    }
    else {
      displaySTRING(stdout, newSTRING(string));
      printf("\n");
    }
  }

  return 0;
}

/**
 * Function to read the file and enqueue into a queue.
 * @param fp    [file]
 * @param queue [queue to insert into]
 */
static void readInFile(FILE *fp, QUEUE *queue) {
  char *str = readToken(fp);

  while (str) {
    enqueue(queue, newSTRING(str));
    str = readToken(fp);
  }
}

/**
 * Function to determine the order of operations.
 * @param  c [operator]
 */
static int priorityOf(char c) {
  switch (c) {
    case '+':
      return 1;
    case '-':
      return 2;
    case '*':
      return 3;
    case '/':
      return 4;
    case '%':
      return 5;
    case '^':
      return 6;
  }
  return -1;
}

/**
 * Function to populate a Binary Search Tree
 * @param fp   [fiel to read values from]
 * @param tree [binary search tree to populate]
 */
void populateBST(FILE *fp, BST *tree) {
  char *str = readToken(fp);

  while (str) {
    if (strcmp(str, "var") == 0) {
      char *s = readToken(fp);
      STRING *key = newSTRING(s);

      readToken(fp);

      char *x = readToken(fp);
      double db = atof(x);
      REAL *value = newREAL(db);

      insertBST(tree, key, value);
    }

    str = readToken(fp);
  }
}

/**
 * Function to dispaly the input
 * @param queue [queue that the data is being read from]
 */
void printInput(QUEUE *queue) {
  int i;
  int size = sizeQUEUE(queue);

  for (i = 0; i < size; i++) {
    STRING *x;

    if (sizeQUEUE(queue) > 0) {
      x = dequeue(queue);
      displaySTRING(stdout, x);
    }

    if (strcmp(getSTRING(x), ";") == 0) printf("\n");
    else { printf(" "); }
  }
}

/**
 * Function to convert teh queue into post fix
 * @param  queue [queue with data to be used]
 */
QUEUE *convertToPostfix(QUEUE *queue) {
  STACK *stack = newSTACK(displaySTRING);
  QUEUE *postFixQueue = newQUEUE(displaySTRING);

  char *s;
  char c;

  while (sizeQUEUE(queue) > 0) {
    s = getSTRING(dequeue(queue));
    c = *s;

    if (isalnum(c)) enqueue(postFixQueue, newSTRING(s));
    else if (c == '(') { push(stack, newSTRING(s)); }
    else if (c == ')') {
      if (sizeSTACK(stack) > 0) {
        char topStack = *getSTRING(peekSTACK(stack));
        while (topStack != '(') {
          enqueue(postFixQueue, peekSTACK(stack));

          if (sizeSTACK(stack) == 0) break;
          pop(stack);
          topStack = *getSTRING(peekSTACK(stack));
        }
        pop(stack);
      }
    }
    else {
      if (sizeSTACK(stack) > 0) {
        char topStack = *getSTRING(peekSTACK(stack));
        while (priorityOf(c) <= priorityOf(topStack) && topStack != '(') {
          enqueue(postFixQueue, peekSTACK(stack));

          pop(stack);
          if (sizeSTACK(stack) == 0) break;
          topStack = *getSTRING(peekSTACK(stack));
        }
      }
      push(stack, newSTRING(s));

    }
  }

  while (sizeSTACK(stack) > 0) {
    enqueue(postFixQueue, peekSTACK(stack));
    pop(stack);
  }

  return postFixQueue;
}

/**
 * Function to get the last line in the queue.
 * @param  queue [queue with data to be used.]
 */
QUEUE *getLastLine(QUEUE *queue) {
  STACK *fullStack = newSTACK(displaySTRING);
  STACK *smallStack = newSTACK(displaySTRING);
  QUEUE *lastLine = newQUEUE(displaySTRING);

  while (sizeQUEUE(queue) > 0) {
    push(fullStack, dequeue(queue));
  }

  pop(fullStack);

  while (sizeSTACK(fullStack) > 0) {
    char *s = getSTRING(peekSTACK(fullStack));
    char c = *s;
    if (c == ';') break;
    push(smallStack, pop(fullStack));
  }

  while (sizeSTACK(smallStack) > 0) {
    if (sizeSTACK(smallStack) == 0) break;
    enqueue(lastLine, pop(smallStack));
  }

  return lastLine;
}


char *processPostFix(QUEUE *queue, BST *tree) {
  STACK *stack = newSTACK(displaySTRING);

  char *elem1;
  char *elem2;
  char c1, c2;
  double value1, value2;

  while (sizeQUEUE(queue) > 0) {
    char *str = getSTRING(peekQUEUE(queue));
    char c = *str;

    if (isalnum(c)) push(stack, dequeue(queue));
    else if (strlen(str) > 1 && str[0] == '-') push(stack, dequeue(queue));
    else {
      if (sizeSTACK(stack) > 0) {
        elem1 = getSTRING(pop(stack));
        c1 = *elem1;
        if (isalpha(c1)) {
          REAL *r = findBST(tree, newSTRING(elem1));
          if (r == NULL) {
            printf("variable %s was not declared\n", elem1);
            exit(0);
          }
          value1 = getREAL(r);
        }
        else {
          if (elem1[0] == '-' && strlen(elem1) > 1) value1 = atof(elem1);
          else value1 = atof(elem1);
        }
      }
      if (sizeSTACK(stack) > 0) {
        elem2 = getSTRING(pop(stack));
        c2 = *elem2;
        if (isalpha(c2)) {
          REAL *r = findBST(tree, newSTRING(elem2));
          if (r == NULL) {
            printf("variable %s was not declared\n", elem2);
            exit(0);
          }
          value2 = getREAL(r);

        }
        else {
          if (elem2[0] == '-' && strlen(elem2) > 1) value2 = atof(elem2);
          else value2 = atof(elem2);
        }
      }

      STRING *eval = evaluate(value1, value2, c);
      push(stack, eval);
      dequeue(queue);
    }
  }

  return getSTRING(pop(stack));
}

void displayPair(FILE *fp, void *key, void *value) {
  displaySTRING(fp, key);
  fprintf(fp, "=");
  displayREAL(fp, value);
}

STRING *evaluate(double a, double b, char c) {
  double val;
  char *str = malloc(sizeof(char *));

  switch (c) {
    case '+':
      val = b + a;
      break;
    case '-':
      val = b - a;
      break;
    case '*':
      val = b * a;
      break;
    case '/':
      val = b / a;
      break;
    case '%':
      val = fmod(b, a);
      break;
    case '^':
      val = pow(b, a);
      break;
  }

  sprintf(str, "%lf", val);
  STRING *s = newSTRING(str);

  return s;
}