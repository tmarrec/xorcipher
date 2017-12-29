#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "cipher.h"
#include "file.h"

unsigned long get_hash(char *word, unsigned int j)
{
	unsigned long somme = 0;
	for ( unsigned int i = 0; i < j; ++i )
	{
		somme += word[i]*pow(256,i);
	}
	return somme;
}

void fill_hash_table(bool *french_word_hash_table)
{
	FILE *hash_file = fopen("hash_table", "r");
	unsigned long hash;
	while ( fscanf(hash_file, "%lu", &hash) != EOF )
	{
		french_word_hash_table[hash] = true;
	}
	fclose(hash_file);
}

bool is_valid_word(unsigned int j, char *word, bool *french_word_hash_table)
{
	switch(j)
	{
		case 2 ... 4:
			word[0] = tolower(word[0]);
			return french_word_hash_table[get_hash(word, j)];
	}
	return false;
}

bool is_separator(int c)
{
	if ( c < 0 )
	{
		c += 256;
	}
	switch(c)
	{
		case 32 ... 34:
		case 13:
		case 44:
		case 46:
		case 58 ... 59:
		case 63:
			return true;	
		default:
			return false;
	}
}

void dict_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n)
{
	bool *french_word_hash_table = NULL;
	french_word_hash_table = (bool*)calloc(4217660786, sizeof(bool));
	fill_hash_table(french_word_hash_table);
		
	char *file_text = NULL;
	file_text = read_file(input_name);
	
	unsigned long file_size = get_file_size(input_name);
	char *file_ciphered = calloc(file_size, sizeof(char));

	unsigned char int_key_lenght = atoi(*key_lenght);
	int c;
	unsigned char j = 0;
	char word[2048];
	unsigned long counter = 0;
	unsigned long max_counter = 0;
	unsigned long max_i = 0;
	
	for (unsigned long i = 0; i < (*key_list_n); ++i )
	{
		file_ciphered = xor_cipher_return(file_text, key_list[i], file_size, int_key_lenght);
		for ( unsigned long cursor = 0; cursor < file_size; ++cursor)
		{
			c = file_ciphered[cursor];
			if ( is_separator(c) == true )
			{
				word[j] = 0;
				if ( is_valid_word(j, word, french_word_hash_table) == true )
				{
					counter++;
				}
				j = 0;
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
	}
	printf("%s\n", key_list[max_i]);
}

