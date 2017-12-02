CC=gcc
CFLAGS=-Wall
OBJ=options.o checkascii.o cipher.o c_validate.o freq_analysis.o dict_analysis.o main.o

util: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o xorcipher -lm

options.o: options.c
checkascii.o: checkascii.c
cipher.o: cipher.c
c_validate.o: c_validate.c
freq_analysis.o: freq_analysis.c
dict_analysis.o: dict_analysis.c
main.o: main.c

clean:
	rm *.o

maxclean: clean
	rm -rF $(EXEC)
