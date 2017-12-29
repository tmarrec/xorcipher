#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cipher.h"
#include "checkascii.h"
#include "read_file.h"
#include "combination.h"

char get_c_key(char **c_key, char **key_lenght, char **input_name, bool print_result, int int_key_lenght)
{
	char key[] = "";
	unsigned int alphabet[71] = {44,45,46,48,49,50,51,52,53,54,55,56,57,58,63,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,95,90,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,125};
	unsigned char key_n = 0;
	
	char *file_text = NULL;
	file_text = read_file(input_name);
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	fseek(input_file, 0l, SEEK_END);
	int file_size = ftell(input_file);
	fclose(input_file);
	char *file_ciphered = calloc(file_size, sizeof(char));
	
	for ( unsigned int i = 0; i < int_key_lenght; ++i )
	{
		key_n = 0;
		for ( unsigned int j = 0; j < 70; ++j )
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
	
	if ( print_result == true )
	{
		for ( int i = 0; i < int_key_lenght; ++i )
		{
			printf("[");
			printf("%s", c_key[i]);
			printf("]");
		}
		printf("\n");
	}
	return 1;
}


char** c_validate(char **input_name, char **key_lenght, unsigned int *key_list_n, bool print_result, bool *isok)
{
	/*
	 * Liste les caracteres possibles pour la clé
	 */
	int int_key_lenght = atoi(*key_lenght);
	//printf("ok");
	char **c_key = NULL;
	c_key = (char**)calloc(int_key_lenght, sizeof(char*));
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		c_key[i] = (char*)calloc(71, sizeof(char));
	}
	//printf("sku");
	//exit(0);

	if ( get_c_key(c_key, key_lenght, input_name, print_result, int_key_lenght) == -1 )
	{
		/*key_list = calloc(1, sizeof(char**));
		key_list[0] = calloc(1, sizeof(char*));
		key_list[0] = "!(;)!"; // Cas où il y a pas de clé possible*/
		//c_key[0][0] = 20;
		//printf("lol20");
		*isok = false;
	}
	return c_key;
}
