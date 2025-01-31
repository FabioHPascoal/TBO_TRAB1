#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "math.h"

struct Node {
    unsigned int nodeNumber;
    float minDist;
    float *distances;
    Node *previousNode;
};

Node *node_create(int nodeNumber, float *distances) {
    Node *node = malloc(sizeof(Node));
    node->nodeNumber = nodeNumber;
    node->minDist = INFINITY;
    node->distances = distances;
    node->previousNode = NULL;

    return node;
}

void node_destroy(Node *node) {
    free(node->distances);
    free(node);
}

int node_get_num(Node *node) {
    return node->nodeNumber;
}

float node_get_min_dist(Node *node) {
    return node->minDist;
}

void node_set_min_dist(Node *node, float dist) {
    node->minDist = dist;
}

Node *node_get_previous(Node *node) {
    return node->previousNode;
}

void node_set_previous(Node *node, Node *prev) {
    node->previousNode = prev;
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