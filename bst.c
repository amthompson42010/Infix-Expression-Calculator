/*
 * @author: Alexander Mark Thompson
 * @title: Binary Search Tree File
 * @description: Main file for the binary search tree, where there are functions that perform
 *              common operations on a binary search tree.
 */

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "bst.h"
#include "string.h"

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "bst.h"
#include "string.h"

struct node {
  void *key;
  void *value;
  struct node *left;
  struct node *right;
};

struct BST {
  struct node *root;
  int size;                                 
  void (*display)(FILE *, void *, void *);  
  int (*comparator)(void *, void *);        
};

/******************** Private functions ********************/

/**
 * Function to handle insertions. Takes the root, what place in the tree
 * the node is at (key), the node's value, and the Binary Search Tree. Then has 
 * conditionals that determine how to insert based off of the root.
 */
static void *insertBSTHelper(struct node *root, BST *tree, void *key, void *value) {
    if (root == NULL) {
      assert(sizeof(struct node));

      root = (struct node *)malloc(sizeof(struct node));
      root->key = key;
      root->value = value;
      root->left = root->right = NULL;

      tree->size += 1;
      return root;
    }
    else if (tree->comparator(key, root->key) < 0) {
      root->left = insertBSTHelper(root->left, tree, key, value);
    }
    else {
      root->right = insertBSTHelper(root->right, tree, key, value);
    }

    return root;
}

/**
 * Function to handle the Binary Search Tree's find method. Takes the root, 
 * what place the node is in within the tree (key), and the Binary Search Tree.
 * If the root is NULL, NULL is returned. Else the value of the root is returned.
 * This function uses recurssion to return the root's value if it is not NULL or
 * the key is not equal to the root's key.
 */
static void *findBSTHelper(struct node *root, BST *tree, void *key) {
  if (root == NULL || tree->comparator(key, root->key) == 0) {
    if (root == NULL) return NULL;
    return root->value;
  }
  else if (tree->comparator(key, root->key) < 0) {
    return findBSTHelper(root->left, tree, key);
  }
  else {
    return findBSTHelper(root->right, tree, key);
  }
}

/**
 * Function to print the tree in order. Takes the output file, the root,
 * and the Binary Search Tree. 
 */
static void printInOrderTree(FILE *fp, struct node *root, BST *tree) {
  if (tree->size == 0) {
    printf("[]");
    return;
  }
  else {
    printf("[");
    if (root->left) printInOrderTree(fp, root->left, tree);

    if (root->left) printf(" ");
    tree->display(fp, root->key, root->value);
    if (root->right) { printf(" "); }

    if (root->right) printInOrderTree(fp, root->right, tree);
    printf("]");
  }
}


/************************* Public functions *************************/

/**
 *  Function to create a new Binary Search Tree. 
 */
BST *newBST(void (*display)(FILE *,void *,void *),int (*comparator)(void *,void *)) {
  assert(sizeof(BST) != 0);

  BST *tree = malloc( sizeof(BST) );

  tree->root = NULL;
  tree->size = 0;
  tree->display = display;
  tree->comparator = comparator;


  return tree;
}

/**
 * Function to insert into the Binary Search Tree.
 */
void insertBST(BST *tree, void *key, void *value) {
  tree->root = insertBSTHelper(tree->root, tree, key, value);
}

/**
 * Function to find a node in the Binary Search Tree.
 */
void *findBST(BST *tree, void *key) {
  return findBSTHelper(tree->root, tree, key);
}

/**
 * Function to get the size of the Binary Search Tree.
 */
int sizeBST(BST *tree) {
  return tree->size;
}

/**
 * Function to print the Binary Search Tree in order.
 */
void displayBST(FILE *fp, BST *tree) {
  printInOrderTree(fp, tree->root, tree);
}
