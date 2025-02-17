#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "IO.h"

const int STR_SIZE = 64;

int main() {
    char inputFileName[STR_SIZE];
    scanf("%s", inputFileName);

    char outputFileName[STR_SIZE];
    scanf("%s", outputFileName);

    IO *io = IO_create(inputFileName, outputFileName);

    IO_Dijkstra(io);
    IO_sort_nodes(io);
    IO_build_output_file(io);
    IO_destroy(io);

    return 0;
}