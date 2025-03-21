// Fábio Pascoal - 2024102901
// Gessica Silva - 2022102174
// Nathan Garcia - 2022102179

#ifndef PQ_H
#define PQ_H

#include <stdbool.h>

typedef struct pq PQ;

/*
 * Cria uma nova fila de prioridade mínima com o limite de elementos informado.
 */
PQ *PQ_create(int max_N, int (*cmp_fn)(void *, void *));

/*
 * Libera a memória da fila.
 */
void PQ_destroy(PQ *pq);

/*
 * Insere o evento na fila segundo o seu tempo.
 */
void PQ_insert(PQ *pq, void *data);

/*
 * Remove e retorna o evento mais próximo.
 */
void *PQ_delmin(PQ *pq);

/*
 * Testa se a fila está vazia.
 */
bool PQ_is_empty(PQ *pq);

/*
 * Retorna o tamanho da fila.
 */
int PQ_size(PQ *pq);

#endif
