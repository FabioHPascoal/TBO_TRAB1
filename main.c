#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "IO.h"

int main(int argc, char *argv[]) {

    IO *io = IO_create(argv[1], argv[2]);

    IO_Dijkstra(io);
    IO_sort_nodes(io);
    IO_build_output_file(io);
    IO_destroy(io);

    return 0;
}