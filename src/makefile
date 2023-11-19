CC = g++
FLAGS = -Wall -Wextra -O3

OBJS = DirectMapped.o SetAssociative.o FullyAssociative.o SetAssociativeNA.o SetAssociativeNLP.o

main: main.o $(OBJS)
	$(CC) $(FLAGS) main.o $(OBJS) -o $@

main.o: main.cpp $(OBJS)
	$(CC) $(FLAGS) main.cpp -c

%.o: %.cpp %.h
	$(CC) $(FLAGS) $< -c

.PHONY: clean
clean:
	rm -f *.o main