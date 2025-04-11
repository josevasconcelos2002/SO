CC = gcc

all: folders ex1 ex2 ex3

ex1: bin/ex1

ex2: bin/ex2

ex3: bin/ex3

folders:
	@mkdir -p obj bin tmp

bin/ex1: obj/ex1.o 
	$(CC) $^ -o $@

obj/ex1.o: src/ex1.c
	$(CC) -c $< -o $@

bin/ex2: obj/ex2.o 
	$(CC) $^ -o $@

obj/ex2.o: src/ex2.c
	$(CC) -c $< -o $@

bin/ex3: obj/ex3.o 
	$(CC) $^ -o $@

obj/ex3.o: src/ex3.c
	$(CC) -c $< -o $@

clean:
	rm -rf obj/* tmp/* bin/*