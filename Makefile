CC=gcc
CFLAGS=-Ofast -Wall
OBJ=options.o checkascii.o cipher.o c_validate.o freq_analysis.o dict_analysis.o read_file.o combination.o main.o

util: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o xorcipher -lm

options.o: options.c
checkascii.o: checkascii.c
cipher.o: cipher.c
c_validate.o: c_validate.c
freq_analysis.o: freq_analysis.c
dict_analysis.o: dict_analysis.c
read_file.o: read_file.c
combination.o: combination.c
main.o: main.c

clean:
	rm *.o

maxclean: clean
	rm -rF $(EXEC)
