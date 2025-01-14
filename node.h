#ifndef NODE_H
#define NODE_H

typedef struct Node Node;

/*
 * Cria um novo nó
 */
Node *node_create(int nodeNumber, float *distances);

/*
 * Libera a memória de um nó.
 */
void node_destroy(Node *node);

/*
 * Retorna o número do nó.
 */
int node_get_num(Node *node);

/*
 * Retorna o array com a distância do nó 1 para o nó 2.
 */
float node_get_distance(Node *node1, Node *node2);

/*
 * asdasa
 */
Node **node_create_array(unsigned int size);

/*
 * asdasa
 */
void node_destoy_array(Node **arr);

/*
 * asdasa
 */
void node_add_to_array(Node *node, Node **arr, unsigned int idx);

/*
 * asdasa
 */
Node *node_get_from_array(Node **arr, unsigned int idx);

#endif