/** 
 * @author: Alexander Mark Thompson
 * @title: CS 201 Fall 2017 Assignemnt 1
 * @description: Header file for char.c
 */

#ifndef __CHAR_INCLUDED__
#define __CHAR_INCLUDED__

#include <stdio.h>

typedef struct CHAR CHAR;

extern CHAR *newCHAR(char);
extern char getCHAR(CHAR *);
extern char setCHAR(CHAR *, char);
extern void displayCHAR(FILE *, void *);
extern void freeCHAR(CHAR *);

#endif