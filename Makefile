CC=gcc
CFLAGS=-Wall
OBJ=readopt.o main.o

util: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main

readopt.o: readopt.c
main.o: main.c

clean:
	rm *.o

maxclean: clean
	rm -rF $(EXEC)
