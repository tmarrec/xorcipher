#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "cipher.h"
#include "read_file.h"

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

unsigned long get_hash(char *word)
{
	//printf("%s", word);
	unsigned long somme = 0;
	for ( int i = 0; i < strlen(word); ++i )
	{
		somme += word[i]*pow(256,i);
	}
	return somme;
}

void fill_hash_table(bool *french_word_hash_table)
{
	FILE *dict_file = fopen("dict.txt", "r");
	int c = 0;
	unsigned long somme = 0;
	int i = 0;
	//unsigned long max = 0;
	while ( (c = fgetc(dict_file)) != EOF )
	{
		if ( c == 10 && i <= 4 && i >= 2)
		{
			//printf("%lu\n", somme);
			french_word_hash_table[somme] = true;
			i = 0;
			somme = 0;
		}
		else if ( c == 10 )
		{
			//printf("\n");
			i = 0;
			somme = 0;
		}
		else
		{
			//printf("%c %d", c, c);
			somme += c*pow(256,i);
			i++;	
		}		
	}
	//exit(0);
}



void dict_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n)
{
	char **french_word = NULL;
	french_word = (char**)calloc(336531, sizeof(char*));
	for ( int i = 0; i < 336531; ++i )
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
	unsigned int file_size = ftell(input_file);
	fclose(input_file);
	char *file_ciphered = calloc(file_size, sizeof(char));

	int int_key_lenght = atoi(*key_lenght);
	int c;
	int j = 0;
	char word[255];
	int counter = 0;

	for ( int i = 0; i < (*key_list_n); ++i )
	{
		counter = 0;
		file_ciphered = xor_cipher_return(file_text, key_list[i], file_size, int_key_lenght);
		printf("%s\n", file_ciphered);
		for ( int cursor = 0; cursor < file_size; ++cursor )
		{
			c = file_ciphered[cursor];
			if ( c < 0 )
			{
				c += 256;
			}
			//printf("%c", c);
			if ( !((c >= 65 && c <= 90)||(c >= 97 && c <= 122)||(c == 192)||(c == 194)||(c == 196)||(c == 224)||(c == 226)||(c == 228)||(c == 199)||(c == 131)||(c >= 200 && c <= 203)||(c >= 232 && c <= 235)||(c == 206)||(c == 207)||(c == 238)||(c == 239)||(c == 217)||(c == 219)||(c == 249)||(c == 251)||(c == 212)||(c == 214)||(c == 244)||(c == 246))||(c >= 65 && c <= 90 && j > 0))
			{
				word[j] = 0;
				word[0] = tolower(word[0]);
				if ( strlen(word) >= 2 && strlen(word) <= 4 )
				{
					printf("%s ", word);
					if ( french_word_hash_table[get_hash(word)] == true )
					{
						//printf("ok\n");
						//printf("%s ", word);
						counter++;
					}
				}
				j = 0;
				switch(c)
				{
					case 65 ... 90:
					case 192:
					case 194:
					case 196:
					case 224:
					case 226:
					case 228:
					case 199:
					case 131:
					case 200 ... 203:
					case 232 ... 235:
					case 206 ... 207:
					case 238 ... 239:
					case 217:
					case 219:
					case 249:
					case 251:
					case 212:
					case 214:
					case 244:
					case 246:
						word[j] = c;
						j++;
						break;
				}
			}
			else
			{
				word[j] = c;
				j++;
			}
		}
		//printf("\n");
		printf("\ncounter : %d\n", counter);
	}


	/*FILE *dict_file = fopen("dict.txt", "r");
	char **french_word = NULL;
	french_word = (char**)calloc(336531, sizeof(char*));
	for ( int i = 0; i < 336531; ++i )
	{
		french_word[i] = (char*)calloc(25, sizeof(char));
	}
	unsigned int i = 0;
	int *french_word_hash = NULL;
	french_word_hash = (int*)calloc(1000000, sizeof(int));
	fill_hash_table(french_word_hash);
	if ( french_word_hash[0] == 1 )
	{
		printf("lool");
		exit(0);
	}*/
	/*while ( fscanf(dict_file, "%s", french_word[i]) == 1 )
	{
		//printf("%d %s\n", i, french_word[i]);
		int somme = 0;
		for ( int j = 0; j < strlen(french_word[i]); ++j )
		{
			//printf("%c", french_word[i][j]);
			if ( french_word[i][j] < 0 )
			{
				somme = somme + (256+french_word[i][j])*(10*j);
			}
			else
			{
				somme = somme + french_word[i][j]*(10*j);
			}
		}
		//printf("\n");
		printf("%d\n", somme);
		french_word_hash[somme] = 1;
			
		i++;
	}*//*
	unsigned int max_word = 0;
	unsigned int right_key = 0;
	for ( int i = 0; i < (*key_list_n); ++i )
	{
		//printf("\n");
		char *output_name = "IO/temp";
		xor_cipher(input_name, key_list[i], &output_name);
		FILE *output_file = fopen(output_name, "r");
		char word[255];*/ /* En ce basant sur le fait que le mot le plus long du francois soit
						* anticonstituionellement, donc aucun mot francais ne dépassera
						* 25 caracteres (cf. wikipedia) 
						*//*
		int word_count = 0;*/
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
		}*//*
		
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
				//printf("%s ", word);
				if ( strlen(word) >= 2 && strlen(word) <= 4 )
				{
					if ( binary_search(french_word, 0, 336531-1, word) == true)
					{
						printf("%s ", word);*/
						//word_used[cursor] = word;
						/*for ( int k = 0; k < cursor; k++ )
						{
							if ( strcmp(word_used[k], word) == 1 )
							{
								printf("\n%s %s ", word_used[k], word);
								printf("doublon");
								exit(0);
							}
						}*//*
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
		}*/
		/*printf(">> ");
		for ( int lol = 0; lol < cursor; ++lol )
		{
			printf("%s ", word_used[lol]);
		}*//*
		fclose(output_file);
		if ( 1 )
		{
			//printf(" >> %s %d\n", key_list[i], word_count);
			//printf("\n");
			//exit(0);
		}
		//GcfYeh
		if ( strcmp(key_list[i],"GcfYeh") == 0)
		{
			//exit(0);
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
	fclose(dict_file);*/
}

