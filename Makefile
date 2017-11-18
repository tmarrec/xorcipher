CC=gcc
CFLAGS=-Wall
OBJ=options.o checkascii.o main.o

util: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main

options.o: options.c
checkascii.o: checkascii.c
main.o: main.c

clean:
	rm *.o

maxclean: clean
	rm -rF $(EXEC)
