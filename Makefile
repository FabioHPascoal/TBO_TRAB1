all:
	gcc -Wall -g -o main *.c
run:
	./main < input.txt
valgrind:
	valgrind --leak-check=full ./main < input.txt
clean:
	rm -f main