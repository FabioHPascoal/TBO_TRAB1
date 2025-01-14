#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "node.h"

const int MAX_BUFFER_SIZE = 1000000;

struct IO {
    unsigned int startNode;
    unsigned int nodeCount;
    Node **nodes;
    char *inputFileName;
    char *outputFileName;
};

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
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        nodeCounter++;
    }
    io->nodeCount = nodeCounter;

    rewind(file);

    Node **nodes = node_create_array(nodeCounter);

    fgets(buffer, sizeof(buffer), file); // To get past first line

    // Saving the remaining data
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        
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
        // for(int i = 0; i < nodeCounter; i++) {
        //     printf(" %.0f", distances[i]);
        // }
        // printf("\n"); 
    }

    io->nodes = nodes;

    fclose(file);

    return io;
}

void IO_destroy(IO *io) {
    for (int i = 0; i < io->nodeCount; i++) {
        node_destroy(node_get_from_array(io->nodes, i));
    }

    node_destoy_array(io->nodes);
    free(io);
}