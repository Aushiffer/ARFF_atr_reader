CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc
PROGRAM = arff

all: $(PROGRAM)

$(PROGRAM): main.o reader.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o reader.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

reader.o: reader.c reader.h
	$(CC) $(CFLAGS) -c reader.c

clean:
	rm -rf *.gch *.o $(PROGRAM)
