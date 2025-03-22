#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"

extern void sort(Item *a, int lo, int hi);

struct IO {
    int startNode;
    int nodeCount;
    Node **nodes;
    char *inputFileName;
    char *outputFileName;
};

// Returns a structure to store all the necessary input/output data
IO *IO_create(char *inputFileName, char *outputFileName) {

    IO *io = malloc(sizeof(IO));
    if (!io) return NULL;

    io->inputFileName = inputFileName;
    io->outputFileName = outputFileName;

    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("No such file\n");
        exit(EXIT_FAILURE);
    }

    char *buffer = NULL;
    size_t bufferSize = 0;

    if (getline(&buffer, &bufferSize, file) != -1) {
        sscanf(buffer, "node_%d", &io->startNode);
    } 
    else {
        printf("Failed to read the start node\n");
        exit(EXIT_FAILURE);
    }

    // Counts how many nodes are present in the input file
    unsigned int nodeCounter = 0;
    while (getline(&buffer, &bufferSize, file) != -1) {
        nodeCounter++;
    }
    io->nodeCount = nodeCounter;

    rewind(file);

    Node **nodes = node_create_array(nodeCounter);

    getline(&buffer, &bufferSize, file);

    // Process all the lines in the file, and stores them as nodes
    while (getline(&buffer, &bufferSize, file) != -1) {
        
        unsigned int nodeNum;
        char* token = strtok(buffer, ", ");
        sscanf(token, "node_%d", &nodeNum);

        float *distances = malloc(nodeCounter * sizeof(float));

        distances[nodeNum] = 0;

        for (int i = 0; i < nodeCounter; i++) {
            if (i == nodeNum) continue;

            token = strtok(NULL, ", ");
            if (token != NULL && sscanf(token, "%f", &distances[i]) == 1) {
                continue;
            }
            distances[i] = 0;
        }

        Node *newNode = node_create(nodeNum, distances);
        node_add_to_array(newNode, nodes, nodeNum);
    }

    node_set_min_dist(nodes[io->startNode], 0);
    io->nodes = nodes;
    fclose(file);
    free(buffer);

    return io;
}

void IO_Dijkstra(IO *io) {
    
    // Priority queue is a better structure than 
    PQ *unvisitedNodes = PQ_create(io->nodeCount * io->nodeCount, nodeCmp);
    PQ_insert(unvisitedNodes, io->nodes[io->startNode]);

    // Calculates the minimum distance from an unvisited node to every other node
    while (!PQ_is_empty(unvisitedNodes)) {
        Node *selectedNode = PQ_delmin(unvisitedNodes);

        for (int i = 0; i < io->nodeCount; i++) {
            Node *neighbor = io->nodes[i];
            float distBetweenNodes = node_get_distance(selectedNode, neighbor);
            
            // No path from first to second node
            if (distBetweenNodes == 0) continue;

            float newDist = node_get_min_dist(selectedNode) + distBetweenNodes;

            // New best path found
            if (newDist < node_get_min_dist(neighbor)) {
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

void IO_destroy(IO *io) {
    for (int i = 0; i < io->nodeCount; i++) {
        node_destroy(io->nodes[i]);
    }

    node_destoy_array(io->nodes);
    free(io);
}