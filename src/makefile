CC = g++
FLAGS = -Wall -Wextra

main: main.o DirectMapped.o
	$(CC) $(FLAGS) main.o DirectMapped.o -o main

main.o: main.cpp DirectMapped.o
	$(CC) $(FLAGS) main.cpp -c

DirectMapped.o: DirectMapped.cpp DirectMapped.h
	$(CC) $(FLAGS) DirectMapped.cpp -c

clean:
	rm *.o main