#ifndef IO_H
#define IO_H

#include "PQ.h"
#include "node.h"

typedef struct IO IO;


/*
 * asdas.
 */
IO *IO_create(char *inputFileName, char *outputFileName);

/*
 * asda.
 */
void IO_destroy(IO *io);

/*
 * asdasd.
 */
unsigned int IO_get_node_count(IO *io);

/*
 * asdasd.
 */
void IO_Dijkstra(IO *io);

/*
 * asdasd.
 */
void IO_sort_nodes(IO *io);

/*
 * asdasd.
 */
void IO_build_output_file(IO *io);

#endif