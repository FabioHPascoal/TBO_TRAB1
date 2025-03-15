#include "rbt.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

struct rbt {
    RBT *l, *r;
    Node *value;
    bool color;
};

RBT *rbt_create(Node *n, bool color){
    RBT *rbt= calloc(1, sizeof(RBT));
    rbt->value = n;
    rbt->color = color;
    rbt->l = NULL;
    rbt->r = NULL;
    return rbt;
}

RBT *rbt_min(RBT *node) {
    if (!node) 
        return NULL;
    if (!node->l) 
        return node;
    return rbt_min(node->l);
}

RBT *rbt_remove_min(RBT *node) {
    if (!node) 
        return NULL;
    if (!node->l) {
        free(node);
        return NULL;
    }
    node->l = rbt_remove_min(node->l);
    return node;
}

bool rbt_red(RBT *node){
    if (!node) 
        return BLACK;
    return node->color;
}

RBT *rbt_rotate_left(RBT *node){
    if (!node || !node->r) return node;

    RBT *aux = node->r;
    node->r = aux->l;
    aux->l = node;
    aux->color = aux->l->color;
    aux->l->color = RED;
    return aux;
}

RBT *rbt_rotate_right(RBT *node){
    if (!node || !node->l) return node;

    RBT *aux = node->l;
    node->l = aux->r;
    aux->r = node;
    aux->color = aux->r->color;
    aux->r->color = RED;
    return aux;
}

void rbt_flip_colors(RBT *node){
    node->color = RED;
    node->l->color = BLACK;
    node->r->color = BLACK;
}

Node *rbt_value(RBT *rbt){
    return rbt->value;
}

RBT *rbt_add(RBT *rbt, Node *n) {
    if (!rbt) {
        return rbt_create(n, RED);
    }

    int cmp = nodeCmp(n,rbt->value);
    if (cmp == -1) {
        rbt->l = rbt_add(rbt->l, n);
    } 
    else if (cmp == 1) {
        rbt->r = rbt_add(rbt->r, n);
    }

    // Balanceamento da árvore
    if (rbt_red(rbt->r) && !rbt_red(rbt->l)) {
        rbt = rbt_rotate_left(rbt);
    }
    if (rbt_red(rbt->l) && rbt_red(rbt->l->l)) {
        rbt = rbt_rotate_right(rbt);
    }
    if (rbt_red(rbt->l) && rbt_red(rbt->r)) {
        rbt_flip_colors(rbt);
    }

    return rbt;
}

void rbt_destroy(RBT *rbt){
    if (rbt == NULL) 
        return;
    rbt_destroy(rbt->r);
    rbt_destroy(rbt->l);
    free(rbt);
}