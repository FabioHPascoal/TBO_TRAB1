#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

struct pq {
    void **heap;
    int size;
    int max_size;
    int (*cmp_fn)(void *, void *);
};

void swap(void **arr, int i1, int i2) {
    void *aux = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = aux;
}

void fix_down(PQ *pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int size = pq->size;

    if ((left < size) && (pq->cmp_fn(pq->heap[left], pq->heap[smallest]) < 0))
        smallest = left;

    if ((right < size) && (pq->cmp_fn(pq->heap[right], pq->heap[smallest]) < 0))
        smallest = right;

    if (smallest != idx){
        swap(pq->heap, idx, smallest);
        fix_down(pq, smallest);
    }
}

void fix_up(PQ *pq, int idx) {
    if (idx != 0) {
        int parent_idx = (idx - 1)/2;

        if (pq->cmp_fn(pq->heap[idx], pq->heap[parent_idx]) < 0){
            swap(pq->heap, idx, parent_idx);
            fix_up(pq, parent_idx);
        }
    }
}

PQ *PQ_create(int max_N, int (*cmp_fn)(void *, void *)) {
    PQ *pq = malloc(sizeof(PQ));
    if (pq == NULL) {
        fprintf(stderr, "Failed to allocate memory for PQ\n");
        return NULL;
    }

    pq->heap = malloc(max_N * sizeof(void *));
    if (pq->heap == NULL) {
        fprintf(stderr, "Failed to allocate memory for PQ heap\n");
        free(pq);
        return NULL;
    }

    pq->size = 0;
    pq->max_size = max_N;
    pq->cmp_fn = cmp_fn;

    return pq;
}


void PQ_destroy(PQ *pq) {
    free(pq->heap);
    free(pq);
}

void PQ_insert(PQ *pq, void *data) {
    if (pq->size == pq->max_size) {
        printf("Queue max size reached\n");
        return;
    }

    pq->heap[pq->size] = data;
    fix_up(pq, pq->size);
    pq->size++;
}

void *PQ_delmin(PQ *pq) {
    if (PQ_is_empty(pq)) {
        return NULL;
    }

    void *removed = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    fix_down(pq, 0);

    return removed;
}

bool PQ_is_empty(PQ *pq) {
    if (pq->size == 0) return true;
    return false;
}

int PQ_size(PQ *pq) {
    return pq->size;
}
