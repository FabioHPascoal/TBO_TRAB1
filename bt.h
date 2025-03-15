#ifndef BT_H
#define BT_H

#include "node.h"


typedef struct BinaryTree BinaryTree;

BinaryTree *bt_create(int (*cmp_fn)(void *, void *));


void bt_insert(BinaryTree *bt, Node *key);
void bt_remove(BinaryTree *bt, Node *key);
void bt_remove_min(BinaryTree *bt);

int bt_is_empty(BinaryTree *bt);
Node *bt_min(BinaryTree *bt);
int bt_height(BinaryTree *bt);
void bt_print(BinaryTree *bt);
int bt_size(BinaryTree *bt);
void bt_destroy(BinaryTree *bt);

void rec_visit(BinaryTree *t, void (*visit)(BinaryTree*));

void rec_bst_postorder(BinaryTree *bt);
void rec_bst_inorder(BinaryTree *bt);
void rec_bst_preorder(BinaryTree *bt);

void iter_bst_preorder(BinaryTree *bt);
void iter_bst_postorder(BinaryTree *bt);
void iter_bst_inorder(BinaryTree *bt);
void iter_bst_levelorder(BinaryTree *bt);

#endif