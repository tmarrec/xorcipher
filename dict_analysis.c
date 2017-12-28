#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "cipher.h"
#include "read_file.h"


unsigned long get_hash(char *word)
{
	unsigned long somme = 0;
	for ( unsigned int i = 0; i < strlen(word); ++i )
	{
		somme += word[i]*pow(256,i);
	}
	return somme;
}

void fill_hash_table(bool *french_word_hash_table)
{
	FILE *dict_file = fopen("dict.txt", "r");
	int c;
	unsigned long somme = 0;
	unsigned int i = 0;
	while ( (c = fgetc(dict_file)) != EOF )
	{
		if ( c == 10 && i <= 4 && i >= 2)
		{
			french_word_hash_table[somme] = true;
			//printf("%lu\n", somme);
			i = 0;
			somme = 0;
		}
		else if ( c == 10 )
		{
			i = 0;
			somme = 0;
		}
		else
		{
			somme += c*pow(256,i);
			i++;	
		}		
	}
	fclose(dict_file);
}

void dict_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n)
{
	char **french_word = NULL;
	french_word = (char**)calloc(336531, sizeof(char*));
	for ( unsigned int i = 0; i < 336531; ++i )
	{
		french_word[i] = (char*)calloc(25, sizeof(char));
	}
	bool *french_word_hash_table = NULL;
	french_word_hash_table = (bool*)calloc(4217660786, sizeof(bool));
	fill_hash_table(french_word_hash_table);
		
	char *file_text = NULL;
	file_text = read_file(input_name);
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	fseek(input_file, 0l, SEEK_END);
	unsigned long file_size = ftell(input_file);
	fclose(input_file);
	char *file_ciphered = calloc(file_size, sizeof(char));

	unsigned char int_key_lenght = atoi(*key_lenght);
	int c;
	unsigned char j = 0;
	char word[1024];
	unsigned long counter = 0;
	unsigned long max_counter = 0;
	unsigned long max_i = 0;

	for (int i = 0; i < (*key_list_n); ++i )
	{
		file_ciphered = xor_cipher_return(file_text, key_list[i], file_size, int_key_lenght);
		for ( unsigned long cursor = 0; cursor < file_size; ++cursor)
		{
			//printf("%c", c);
			c = file_ciphered[cursor];
			if ( c < 0 )
			{
				c += 256;
			}
			if ( c == 32 || c == 13 || c == 44 || c == 46 || c == 58 || c == 59 || c == 34 || c == 63 || c == 33 )
			{
				word[j] = 0;
				j = 0;
				if ( strlen(word) >= 2 && strlen(word) <= 4 )
				{
					word[0] = tolower(word[0]);
					//printf("%s ", word);
					if ( french_word_hash_table[get_hash(word)] == true )
					{
						//printf("%s ", word);
						counter++;
					}
				}
			}
			else
			{
				word[j] = c;
				j++;
			}
		}
		if ( counter > max_counter )
		{
			max_counter = counter;
			max_i = i;
		}
		counter = 0;

		/*if ( strcmp(key_list[i], "adijd") == 0 )
		{
			printf("lol");
			exit(0);		
		}*/
	}
	printf("%s\n", key_list[max_i]);
}

