CC = g++
FLAGS = -Wall -Wextra -g -O0

main: main.o DirectMapped.o SetAssociative.o FullyAssociative.o
	$(CC) $(FLAGS) main.o DirectMapped.o SetAssociative.o FullyAssociative.o -o main

main.o: main.cpp DirectMapped.o SetAssociative.o FullyAssociative.o
	$(CC) $(FLAGS) main.cpp -c

DirectMapped.o: DirectMapped.cpp DirectMapped.h
	$(CC) $(FLAGS) DirectMapped.cpp -c

SetAssociative.o: SetAssociative.cpp SetAssociative.h
	$(CC) $(FLAGS) SetAssociative.cpp -c

FullyAssociative.o: FullyAssociative.cpp FullyAssociative.h
	$(CC) $(FLAGS) FullyAssociative.cpp -c

clean:
	rm *.o main