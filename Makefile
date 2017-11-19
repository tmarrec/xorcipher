CC=gcc
CFLAGS=-Wall
OBJ=options.o checkascii.o cipher.o c_validate.o main.o

util: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main

options.o: options.c
checkascii.o: checkascii.c
cipher.o: cipher.c
c_validate.o: c_validate.c
main.o: main.c

clean:
	rm *.o

maxclean: clean
	rm -rF $(EXEC)
