binary_heap:
	gcc -Wall -g -o mainHeap main.c PQ.c bt.c node.c IO.c quick_sort_4.c

binary_tree:
	gcc -Wall -g -o mainBt main_bt.c PQ.c bt.c node.c IO.c quick_sort_4.c
clean:
	rm -f main