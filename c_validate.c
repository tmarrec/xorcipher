#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cipher.h"
#include "checkascii.h"
#include "file.h"
#include "combination.h"

void print_result(char **c_key, int int_key_lenght)
{
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		printf("[");
		printf("%s", c_key[i]);
		printf("]");
	}
	printf("\n");
}

char get_c_key(char **c_key, char **key_lenght, char **input_name, bool need_print_result, int int_key_lenght)
{
	char key[1];
	unsigned int alphabet[71] = {44,45,46,48,49,50,51,52,53,54,55,56,57,58,63,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,95,90,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,125};
	unsigned char key_n = 0;
	char *file_text = NULL;
	file_text = read_file(input_name);
	unsigned long file_size = get_file_size(input_name);
	char *file_ciphered = calloc(file_size, sizeof(char));
	for ( unsigned int i = 0; i < int_key_lenght; ++i )
	{
		key_n = 0;
		for ( unsigned int j = 0; j < 71; ++j )
		{
			key[0] = alphabet[j];
			file_ciphered = xor_cipher_return(file_text, key, file_size, 1);
			if ( checkmessage_opt(file_ciphered, i, int_key_lenght, file_size) == true )
			{
				c_key[i][key_n] = alphabet[j];
				key_n++;
			}
		}
		if ( key_n == 0 )
		{
			return -1;
		}
		c_key[i][key_n] = 0;
	}
	if ( need_print_result == true )
	{
		print_result(c_key, int_key_lenght);
	}
	return 1;
}


char** c_validate(char **input_name, char **key_lenght, unsigned int *key_list_n, bool print_result, bool *isok)
{
	int int_key_lenght = atoi(*key_lenght);
	char **c_key = NULL;
	c_key = (char**)calloc(int_key_lenght, sizeof(char*));
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		c_key[i] = (char*)calloc(71, sizeof(char));
	}
	if ( get_c_key(c_key, key_lenght, input_name, print_result, int_key_lenght) == -1 )
	{
		*isok = false;
	}
	return c_key;
}
