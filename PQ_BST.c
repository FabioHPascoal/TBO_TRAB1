// Fábio Pascoal - 2024102901
// Gessica Silva - 2022102174
// Nathan Garcia - 2022102179

#include <stdio.h>
#include <stdlib.h>

#include "PQ.h"
#include "bst.h"

struct pq {
    BST *bst;
    int (*cmp_fn)(void *, void *);
};

PQ *PQ_create(int max_N, int (*cmp_fn)(void *, void *)){
    PQ *pq = (PQ *)malloc(sizeof(PQ));
    if (!pq) return NULL;

    pq->bst = bst_construct(cmp_fn);
    pq->cmp_fn = cmp_fn;

    return pq;
}

void PQ_destroy(PQ *pq) {
    bst_destroy(pq->bst);
    free(pq);
}

void PQ_insert(PQ *pq, void *data) {
    bst_add(pq->bst, data);
}

void *PQ_delmin(PQ *pq) {
    return bst_pop_min(pq->bst);
}

bool PQ_is_empty(PQ *pq) {
    return bst_is_empty(pq->bst);
}

int PQ_size(PQ *pq) {
    return bst_node_count(pq->bst);
}