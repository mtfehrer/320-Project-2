CC = g++
FLAGS = -Wall -Wextra -O3

OBJS = DirectMapped.o SetAssociative.o FullyAssociativeLRU.o FullyAssociativePLRU.o SetAssociativeNA.o SetAssociativeNLP.o SetAssociativePOAM.o

main: main.o $(OBJS)
	$(CC) $(FLAGS) main.o $(OBJS) -o $@

main.o: main.cpp $(OBJS)
	$(CC) $(FLAGS) main.cpp -c

%.o: %.cpp %.h CacheEntryStructs.h
	$(CC) $(FLAGS) $< -c

.PHONY: clean
clean:
	rm -f *.o main