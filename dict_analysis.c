#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "cipher.h"

bool binary_search(char **french_word, int l, int r, char *word)
{
	unsigned int m = 0;
	if ( r >= l )
	{
		m = l+(r-l)/2;
		if ( strcmp(french_word[m], word) == 0 )
		{
			return true;
		}
		else if ( strcmp(french_word[m], word) > 0 )
		{
			return binary_search(french_word, l, m-1,  word);
		}
		return binary_search(french_word, m+1, r, word);
	}
	return false;
}

void dict_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n)
{
	FILE *dict_file = fopen("dict.txt", "r");
	char **french_word = NULL;
	french_word = (char**)calloc(336531, sizeof(char*));
	for ( int i = 0; i < 336531; ++i )
	{
		french_word[i] = (char*)calloc(25,sizeof(char));
	}
	unsigned int i = 0;
	while ( fscanf(dict_file, "%s", french_word[i]) == 1 )
	{
		//printf("%d %s\n", i, french_word[i]);
		i++;
	}
	unsigned int cursor = 336531/2;
	unsigned int max_word = 0;
	unsigned int right_key = 0;
	for ( int i = 0; i < (*key_list_n); ++i )
	{
		char *output_name = "IO/temp";
		xor_cipher(input_name, key_list[i], &output_name);
		FILE *output_file = fopen(output_name, "r");
		char word[25]; /* En ce basant sur le fait que le mot le plus long du francois soit
						* anticonstituionellement, donc aucun mot francais ne dépassera
						* 25 caracteres (cf. wikipedia) 
						*/
		int word_count = 0;
		while ( fscanf(output_file, "%25s", word) == 1  )
		{
			word[0] = tolower(word[0]);
			if ( binary_search(french_word, 0, 336531-1, word) == true )
			{
				word_count++;
			}
		}
		fclose(output_file);
		if ( word_count > max_word )
		{
			right_key = i;
			max_word = word_count;
		}
	}
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		printf("%c", key_list[right_key][i]);
	}
	printf("\n");
	fclose(dict_file);
}

