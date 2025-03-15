bst:
	gcc -Wall -g -o main.out main.c IO.c node.c quick_sort_4.c PQ_BST.c bst.c
heap:
	gcc -Wall -g -o main.out main.c IO.c node.c quick_sort_4.c PQ_HEAP.c
clean:
	rm -f main