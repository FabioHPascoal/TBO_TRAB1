#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdbool.h>

typedef int (*CmpFn)(void *, void *);

typedef struct Node Node;
typedef struct BST BST;

/*
 * Crie uma árvore binária vazia com a funçãp de comparação para busca e inserção
 */
BST *bst_construct(CmpFn cmp_fn);

/*
 * Destroi a árvore binária
 */
void bst_destroy(BST *bst);

/*
 * Insere uma chave na arvore binária
 */
void bst_add(BST *bst, void *data);

/*
 * Remove uma chave na arvore binária
 */
void bst_remove(BST *bst, void *key);

/*
 * Obtém o item de menor chave da árvore binária
 */
void *bst_min(BST *bst);

/*
 * Obtém o item de maior chave da árvore binária
 */
void *bst_max(BST *bst);

/*
 * Remove o item de menor chave da árvore binária
 */
void *bst_pop_min(BST *bst);

/*
 * Remove o item de maior chave da árvore binária
 */
void *bst_pop_max(BST *bst);

/*
 * Retorna a quantidade de nós na árvore
 */
int bst_node_count(BST *bst);

/*
 * Retorna se a árvore ta vázia
 */
bool bst_is_empty(BST *bst);

#endif