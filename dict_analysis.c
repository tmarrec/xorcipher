#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cipher.h"

void dict_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n)
{
	printf("DICT\n");
	FILE *dict_file = fopen("dict.txt", "r");
	//char french_word[336531];
	char **french_word = NULL;
	french_word = (char**)calloc(336531, sizeof(char*));
	for ( int i = 0; i < 25; ++i )
	{
		french_word[i] = (char*)malloc(25*sizeof(char));
	}
	unsigned int i = 0;
	while ( fscanf(dict_file, "%s", french_word[i]) == 1 )
	{
		printf("%s ", french_word[i]);
	}
	/*
	for ( int i = 0; i < (*key_list_n); ++i )
	{
		char *output_name = "IO/temp";
		xor_cipher(input_name, key_list[i], &output_name);
		FILE *output_file = fopen(output_name, "r");
		char word[25]; /* En ce basant sur le fait que le mot le plus long du francois soit
						* anticonstituionellement, donc aucun mot francais ne dépassera
						* 25 caracteres (cf. wikipedia) 
						*
		while ( fscanf(output_file, "%25s", word) == 1  )
		{
			printf("%s ", word);

		}
		printf("\n\n");
		fclose(output_file);
	}
	*/
	fclose(dict_file);
}

