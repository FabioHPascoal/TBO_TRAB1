#ifndef PQ_H
#define PQ_H

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

#endif