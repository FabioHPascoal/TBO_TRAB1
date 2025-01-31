#ifndef ITEM_H
#define ITEM_H

#include "node.h" // Assumindo que essa biblioteca define Node, node_get_min_dist, e node_get_num.

typedef Node *Item;

#define key(A)          (A)
#define less(A, B)      (nodeCmp((void *)(A), (void *)(B)) < 0)
#define exch(A, B)      { Item t = A; A = B; B = t; }
#define compexch(A, B)  if (less(B, A)) exch(A, B)

static inline int nodeCmp(void *node1, void *node2) {
    Node *n1 = (Node *)node1;
    Node *n2 = (Node *)node2;

    if (node_get_min_dist(n1) > node_get_min_dist(n2)) return 1;
    if (node_get_min_dist(n1) < node_get_min_dist(n2)) return -1;
    if (node_get_num(n1) > node_get_num(n2)) return 1;
    if (node_get_num(n1) < node_get_num(n2)) return -1;

    return 0;
}

#endif
