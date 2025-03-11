#ifndef RBT_H
#define RBT_H

#define BLACK false
#define RED true
#include <stdbool.h>
#include "node.h"

typedef struct rbt RBT;
typedef struct rbt_node RBTNode;
typedef struct rbtree RBTree;

RBT *rbt_create(Node *n, bool color);
bool rbt_red(RBT *node);
RBT *rbt_rotate_left(RBT *node);
RBT *rbt_rotate_right(RBT *node);
void rbt_flip_colors(RBT *node);
Node *rbt_value(RBT *rbt);
RBT *rbt_add(RBT *rbt, Node *n);
void rbt_destroy(RBT *rbt);
RBT *rbt_remove(RBT *rbt, Node *n);
RBT *rbt_min(RBT *node);
RBT *rbt_remove_min(RBT *node);


#endif