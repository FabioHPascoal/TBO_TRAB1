#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "item.h"

extern void sort(Item *a, int lo, int hi);

const int MAX_BUFFER_SIZE = 1000000;

struct IO {
    unsigned int startNode;
    unsigned int nodeCount;
    Node **nodes;
    char *inputFileName;
    char *outputFileName;
};

// int nodeCmp(void *node1, void *node2){
//     Node *n1 = (Node *)node1;
//     Node *n2 = (Node *)node2;

//     if (node_get_min_dist(n1) > node_get_min_dist(n2)) return 1;
//     if (node_get_min_dist(n1) < node_get_min_dist(n2)) return -1;
//     if (node_get_num(n1) > node_get_num(n2)) return 1;
//     if (node_get_num(n1) < node_get_num(n2)) return -1;

//     return 0;
// }

IO *IO_create(char *inputFileName, char *outputFileName) {

    IO *io = malloc(sizeof(IO));
    io->inputFileName = inputFileName;
    io->outputFileName = outputFileName;

    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("No such file\n");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_BUFFER_SIZE];

    // Reading starting node
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "node_%d", &io->startNode);
    
    // Counting total number of nodes
    unsigned int nodeCounter = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        nodeCounter++;
    }
    io->nodeCount = nodeCounter;

    rewind(file);

    Node **nodes = node_create_array(nodeCounter);

    fgets(buffer, sizeof(buffer), file); // To get past first line

    // Saving the remaining data
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        
        unsigned int nodeNum;
        char* token = strtok(buffer, ", ");
        sscanf(token, "node_%d", &nodeNum);

        float *distances = malloc(nodeCounter * sizeof(float));

        // So you can't reach a node from itself
        distances[nodeNum] = 0;

        for (int i = 0; i < nodeCounter; i++) {
            if (i == nodeNum) continue; // Already considered above

            char* token = strtok(NULL, ", ");
            if (sscanf(token, "%f", &distances[i]) == 0) {
                distances[i] = 0;
            }
        }

        Node *newNode = node_create(nodeNum, distances);
        node_add_to_array(newNode, nodes, nodeNum);

        // printf("Node %d:", nodeNum);
        // for (int i = 0; i < nodeCounter; i++) {
        //     printf(" %.0f", distances[i]);
        // }
        // printf("\n");
    }

    node_set_min_dist(nodes[io->startNode], 0);
    io->nodes = nodes;
    fclose(file);

    return io;
}

void IO_destroy(IO *io) {
    for (int i = 0; i < io->nodeCount; i++) {
        node_destroy(io->nodes[i]);
    }

    node_destoy_array(io->nodes);
    free(io);
}

void IO_Dijkstra(IO *io) {
    PQ *unvisitedNodes = PQ_create(io->nodeCount * io->nodeCount, nodeCmp);
    PQ_insert(unvisitedNodes, io->nodes[io->startNode]);

    while (!PQ_is_empty(unvisitedNodes)) {
        Node *selectedNode = PQ_delmin(unvisitedNodes);

        for (int i = 0; i < io->nodeCount; i++) {
            Node *neighbor = io->nodes[i];
            float distBetweenNodes = node_get_distance(selectedNode, neighbor);

            if (distBetweenNodes == 0) continue; // No path from first to second node

            float newDist = node_get_min_dist(selectedNode) + distBetweenNodes;

            if (newDist < node_get_min_dist(neighbor)) { // New best path found
                node_set_previous(neighbor, selectedNode);
                node_set_min_dist(neighbor, newDist);
                PQ_insert(unvisitedNodes, neighbor);
            }
        }
    }

    PQ_destroy(unvisitedNodes);
}

void IO_sort_nodes(IO *io) {
    sort(io->nodes, 0, io->nodeCount - 1);
}

void IO_build_output_file(IO *io) {
    FILE *outputFile = fopen(io->outputFileName, "w");

    for (int i = 0; i < io->nodeCount; i++) {
        Node *selectedNode = io->nodes[i];
        unsigned int nodeNum = node_get_num(selectedNode);

        fprintf(outputFile, "SHORTEST PATH TO node_%d: node_%d", nodeNum, nodeNum);

        if (nodeNum == io->startNode) {
            fprintf(outputFile, " <- node_%d", nodeNum);
        }

        Node *previousNode = node_get_previous(selectedNode);
        while (previousNode != NULL) {
            fprintf(outputFile, " <- node_%d", node_get_num(previousNode));
            previousNode = node_get_previous(previousNode);
        }

        fprintf(outputFile, " (Distance: %.2f)\n", node_get_min_dist(selectedNode));
    }

    fclose(outputFile);
}