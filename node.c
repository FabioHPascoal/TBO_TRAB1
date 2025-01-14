#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node {
    unsigned int nodeNumber;
    float *distances;
};

Node *node_create(int nodeNumber, float *distances) {
    Node *node = malloc(sizeof(Node));
    node->nodeNumber = nodeNumber;
    node->distances = distances;

    return node;
}

void node_destroy(Node *node) {
    free(node->distances);
    free(node);
}

int node_get_num(Node *node) {
    return node->nodeNumber;
}

float node_get_distance(Node *node1, Node *node2) {
    return node1->distances[node_get_num(node2)];
}

Node **node_create_array(unsigned int size) {
    return malloc(size * sizeof(Node));
}

void node_destoy_array(Node **arr) {
    free(arr);
}

void node_add_to_array(Node *node, Node **arr, unsigned int idx) {
    arr[idx] = node;
}

Node *node_get_from_array(Node **arr, unsigned int idx) {
    return arr[idx];
}