#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cipher.h"
#include "checkascii.h"
#include "read_file.h"

char get_c_key(char **c_key, char **key_lenght, char **input_name, bool print_result)
{
	char key[] = "";
	FILE *c_key_file;
	c_key_file = fopen("c_key", "r");
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
	int int_key_lenght = atoi(*key_lenght);
	for ( unsigned int i = 0; i < atoi(*key_lenght); ++i )
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
		c_key[i][key_n] = '\0';
		fseek(c_key_file, 0, SEEK_SET);
	}
	fclose(c_key_file);
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		if ( strlen(c_key[i]) == 0 )
		{
			return -1;
		}
	}
	if ( print_result == true )
	{
		for ( int i = 0; i < atoi(*key_lenght); ++i )
		{
			printf("[");
			for ( int j = 0; j < strlen(c_key[i]); ++j )
			{
				printf("%c", c_key[i][j]);
			}
			printf("]");
		}
		printf("\n");
	}
	return 1;
}

void combination_arrays(char **key_lenght, int n, int *cursor, char **key_list, char **c_key)
{	
	char *temp = NULL;
	temp = calloc(atoi(*key_lenght)+1, sizeof(char*));
	
	unsigned int cursor_in_cursor = atoi(*key_lenght)-1; // LuL
	for ( unsigned int i = 0; i < n; ++i )
	{
		//temp = malloc(atoi(*key_lenght)*sizeof(char*));
		for ( unsigned char j = 0; j < atoi(*key_lenght); ++j )
		{
			temp[j] = c_key[j][cursor[j]];
			key_list[i][j] = c_key[j][cursor[j]];
		}
		
		strcpy(key_list[i], temp);
		//free(temp);

		cursor[cursor_in_cursor]++;
		while ( i < n-1 && cursor[cursor_in_cursor] == strlen(c_key[cursor_in_cursor]) )
		{
			cursor[cursor_in_cursor] = 0;
			cursor_in_cursor--;
			cursor[cursor_in_cursor]++;
		}
		cursor_in_cursor = atoi(*key_lenght)-1;
	}
	free(temp);
}

char** c_validate(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n, bool print_result)
{
	/*
	 * Liste les caracteres possibles pour la clé
	 */

	char **c_key = NULL;
	c_key = (char**)calloc(atoi(*key_lenght), sizeof(char*));
	for ( unsigned char i = 0; i < atoi(*key_lenght); ++i )
	{
		c_key[i] = (char*)calloc(71, sizeof(char));
	}

	if ( get_c_key(c_key, key_lenght, input_name, print_result) == -1 )
	{
		key_list = calloc(1, sizeof(char**));
		key_list[0] = calloc(1, sizeof(char*));
		key_list[0] = "!(;)!"; // Cas où il y a pas de clé possible
		return key_list;
	}

	/*
	 *	Combinaison des clés avec les caracteres possibles
	 */

	unsigned int n = 1;
	for ( unsigned char i = 0; i < atoi(*key_lenght); ++i )
	{
		n = n*(int)strlen(c_key[i]);
	}
	int *cursor = NULL;
	cursor = calloc(atoi(*key_lenght), sizeof(int));
	
	key_list = calloc(n, sizeof(char**));
	for ( unsigned int i = 0; i < n; ++i )
	{
		key_list[i] = calloc(atoi(*key_lenght), sizeof(char*));
	}

	combination_arrays(key_lenght, n, cursor, key_list, c_key);
	/*	
	for ( int i = 0; i < n; ++i )
	{
		printf("%s ", key_list[i]);
	}
	printf("\n");
	*/	
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		free(c_key[i]);
	}
	free(c_key);
	
	free(cursor);
	
	*key_list_n = n;
	return key_list;
}
