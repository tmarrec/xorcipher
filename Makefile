CC=gcc
CFLAGS=-Ofast -Wall -Wextra -g
OBJ=src/options.o src/checkascii.o src/cipher.o src/c_validate.o src/freq_analysis.o src/dict_analysis.o src/file.o src/combination.o src/main.o

util: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o xorcipher -lm

src/options.o: src/options.c
src/checkascii.o: src/checkascii.c
src/cipher.o: src/cipher.c
src/c_validate.o: src/c_validate.c
src/freq_analysis.o: src/freq_analysis.c
src/dict_analysis.o: src/dict_analysis.c
src/file.o: src/file.c
src/combination.o: src/combination.c
src/main.o: src/main.c

clean:
	rm src/*.o

maxclean: clean
	rm src/-rF $(EXEC)
