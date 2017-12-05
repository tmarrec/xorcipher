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
		french_word[i] = (char*)calloc(25, sizeof(char));
	}
	unsigned int i = 0;
	while ( fscanf(dict_file, "%s", french_word[i]) == 1 )
	{
		//printf("%d %s\n", i, french_word[i]);
		i++;
	}
	unsigned int max_word = 0;
	unsigned int right_key = 0;
	for ( int i = 0; i < (*key_list_n); ++i )
	{
		//printf("\n");
		char *output_name = "IO/temp";
		xor_cipher(input_name, key_list[i], &output_name);
		FILE *output_file = fopen(output_name, "r");
		char word[255]; /* En ce basant sur le fait que le mot le plus long du francois soit
						* anticonstituionellement, donc aucun mot francais ne dépassera
						* 25 caracteres (cf. wikipedia) 
						*/
		int word_count = 0;
		/*
		while ( fscanf(output_file, "%[^A-Z]25s", word) == 1  )
		{
			//printf("word: %s\n", word);
			word[0] = tolower(word[0]);
			if ( strlen(word) >= 2 && strlen(word) <= 4 )
			{
				printf("%s ", word);
				if ( binary_search(french_word, 0, 336531-1, word) == true )
				{
					//printf("%s ", word);
					word_count++;
				}

			}
		}*/
		/*	
		char c;
		unsigned int j = 0;
		while ( (c = fgetc(output_file)) != EOF )
		{
			if ( !((c >= 97 && c <= 122)) )
			{
				word[j] = 0;
				word[0] = tolower(word[0]);
				if ( strlen(word) >= 2 && strlen(word) <= 4 )
				{
					if ( binary_search(french_word, 0, 336531-1, word) == true )
					{
						word_count++;
					}
					printf("%s\n", word);
				}
				j = 0;
			}
			word[j] = c;
			//printf("%c", c);
			j++;
		}*/
		
		char c;
		char **word_used = NULL;
		word_used = (char**)calloc(1, sizeof(char*));
		word_used[0] = (char*)calloc(255, sizeof(char));

		unsigned int cursor = 0;
		unsigned int j = 0;
		while ( (c = fgetc(output_file)) != EOF )
		{
			if ( !((c >= 65 && c <= 90)||(c >= 97 && c <= 122))||(c >= 65 && c <= 90 && j > 0))
			{
				word[j] = 0;
				word[0] = tolower(word[0]);
				printf("%s ", word);
				if ( strlen(word) >= 2 && strlen(word) <= 4 )
				{
					if ( binary_search(french_word, 0, 336531-1, word) == true)
					{
						//word_used[cursor] = word;
						/*for ( int k = 0; k < cursor; k++ )
						{
							if ( strcmp(word_used[k], word) == 1 )
							{
								printf("\n%s %s ", word_used[k], word);
								printf("doublon");
								exit(0);
							}
						}*/
						strncpy(word_used[cursor], word, sizeof(word));
						cursor++;
						word_used = (char**)realloc(word_used, (cursor+1)*sizeof(char*));
						word_used[cursor] = (char*)calloc(255, sizeof(char));
						//printf("%s ", word);
						word_count++;
					}
				}
				j = 0;
				if ( c >= 65 && c <= 90 )
				{
					word[j] = c;
					j++;
				}
			}
			else
			{
				word[j] = c;
				j++;
			}
		}
		/*printf(">> ");
		for ( int lol = 0; lol < cursor; ++lol )
		{
			printf("%s ", word_used[lol]);
		}*/
		fclose(output_file);
		if ( 1 )
		{
			printf(" >> %s %d\n", key_list[i], word_count);
			printf("\n");
			//exit(0);
		}
		//GcfYeh
		if ( strcmp(key_list[i],"GcfYeh") == 0)
		{
			exit(0);
		}

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

