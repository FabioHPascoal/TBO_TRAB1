#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdbool.h>

typedef int (*CmpFn)(void *, void *);

typedef struct Node Node;
typedef struct BST BST;

BST *bst_construct(CmpFn cmp_fn);
void bst_destroy(BST *bst);

void bst_add(BST *bst, void *data);
void bst_remove(BST *bst, void *key);

void *bst_min(BST *bst);
void *bst_max(BST *bst);
void *bst_pop_min(BST *bst);
void *bst_pop_max(BST *bst);

int bst_node_count(BST *bst);
bool bst_is_empty(BST *bst);

#endif