/*
 * @author: Alexander Mark Thompson
 * @title: Binary Search Tree File
 * @description: Main file for the binary search tree, where there are functions that perform
 *              common operations on a binary search tree.
 */

#include <stdlib.h>
#include <assert.h>
#include "bst.h"

struct binNode {
    void *key;
    void *value;
    struct binNode *left;
    struct binNode *right;
} binNode;

struct BST {
    struct binNode *root;
    int size;
    void (*display)(FILE *, void *);
    int (*compare)(void *, void *);
};

BST *
newBST(void (*display)(FILE *, void *, void *), int (*comparator)(void *, void *))
{
    assert(sizeof(BST) != 0);
    BST *tree = malloc(sizeof(BST));

    tree->root = NULL;
    tree->root->key = NULL;
    tree->root->value = NULL;
    tree->root->left = NULL;
    tree->root->right = NULL;

    tree->size = 0;
    tree->display = display;
    tree->compare = comparator;
    return tree;
}

void
insertBST(BST *binTree, void *key, void *value)
{
    assert(sizeof(binNode) != 0);

    BST *pointerToTree = binTree;
    pointerToTree->root = binTree->root;
    pointerToTree->root->key = binTree->root->key;
    pointerToTree->root->value = binTree->root->value;
    pointerToTree->root->left = binTree->root->left;
    pointerToTree->root->right = binTree->root->right;
    
    if(pointerToTree->root == NULL)
    {
        pointerToTree->root = malloc(sizeof(binNode));
        pointerToTree->root->key = key;
        pointerToTree->root->value = value;
        pointerToTree->root->left = NULL;
        pointerToTree->root->right = NULL;
        pointerToTree->size += 1;
    }
    else if(binTree->compare(value, pointerToTree->root->value) < 0)
    {
        pointerToTree->root = pointerToTree->root->left;
        insertBST(pointerToTree, key, value);
    }
    else if(binTree->compare(value, pointerToTree->root->value) > 0)
    {
        pointerToTree->root = pointerToTree->root->right;
        insertBST(pointerToTree, key, value);
    }
}

void *
findBST(BST *binTree, void *key)
{
    void *returnValue = NULL;

    BST *pointerToTree = binTree;
    pointerToTree->root = binTree->root;
    pointerToTree->root->key = binTree->root->key;
    pointerToTree->root->value = binTree->root->value;
    pointerToTree->root->left = binTree->root->left;
    pointerToTree->root->right = binTree->root->right;

    if(pointerToTree->root-> == NULL)
    {
        return returnValue;
    }

    if(pointerToTree->root->value == key)
    {
        returnValue = pointerToTree->root->value;
    }
    else if(pointerToTree->compare(key, pointerToTree->root->value) < 0)
    {
        pointerToTree->root = pointerToTree->root->left;
        findBST(pointerToTree, key);
    }
    else if(pointerToTree->compare(key, pointerToTree->root->value) > 0)
    {
        pointerToTree->root = pointerToTree->root->right;
        findBST(pointerToTree, key);
    }

    return valueToReturn;
}

int 
sizeBST(BST *binTree)
{
    return binTree->size;
}

void
displayBST(FILE *fp, BST *binTree)
{
    BST *pointerToTree = binTree;
    pointerToTree->root = binTree->root;
    pointerToTree->root->key = binTree->root->key;
    pointerToTree->root->value = binTree->root->value;
    pointerToTree->root->left = binTree->root->left;
    pointerToTree->root->right = binTree->root->right;

    pointerToTree->root = binTree->root->left;
    displayBST(fp, pointerToTree);
    fprintf(fp, "[");
    binTree->display(fp, pointerToTree->root->key, pointerToTree->root->value);
    fprintf(fp, "]");

    pointerToTree->root = pointer->root->right;
    displayBST(fp, pointerToTree);
}
