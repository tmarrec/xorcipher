#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "cipher.h"
#include "checkascii.h"

void c_validate(char **input_name, char **key_lenght)
{
	clock_t start = clock();
		
	char *output_name = "IO/output2";
	char key[] = "";
	char **c_key = NULL;
	c_key = (char**)malloc(atoi(*key_lenght)*sizeof(char*));
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		c_key[i] = (char*)malloc(1*sizeof(char));
	}
	
	FILE *c_key_file;
	c_key_file = fopen("c_key", "r");
	int c = 0;
	unsigned char index = 0;
	//printf(">>>> %d\n", atoi(*key_lenght));
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		if ( i > 0 )
		{
			index = atoi(*key_lenght)-i;
		}
		unsigned char key_n = 0;
		while ( (c = fgetc(c_key_file)) != EOF )
		{
			key[0] = c;
			xor_cipher(input_name, key, &output_name);
			if ( checkmessage(&output_name, i, atoi(*key_lenght)) == true )
			{
				key_n++;
				if ( key_n > 1)
				{
					c_key[i] = realloc(c_key[i], key_n*sizeof(char));
				}
				c_key[index][key_n-1] = c;
				//printf("key : %c \n", c);
			}
		}
		//printf("\n");
		fseek(c_key_file, 0, SEEK_SET);
	}
	
	/*
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		for ( int j = 0; j < (int)strlen(c_key[i]); ++j )
		{
			printf("%c ", c_key[i][j]);
		}
		printf("\n");
	}
	*/

	/*
	 *	Combinaison
	 */
	unsigned int n = 1;
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		n = n*(int)strlen(c_key[i]);
	}
	//printf("n : %d\n", n);
	int *cursor = NULL;
	cursor = calloc(atoi(*key_lenght), sizeof(int));
	char **key_list = NULL;
	key_list = malloc(n*sizeof(char**));
	for ( int i = 0; i < n; ++i )
	{
		key_list[i] = malloc(atoi(*key_lenght)*sizeof(char*));
	}
	char *temp = NULL;
	temp = malloc(atoi(*key_lenght)*sizeof(char*));
	
	unsigned int cursor_in_cursor = atoi(*key_lenght)-1; // LuL
	for ( int i = 0; i < n; ++i )
	{
		temp = malloc(atoi(*key_lenght)*sizeof(char*));
		for ( int j = 0; j < atoi(*key_lenght); ++j )
		{
			temp[j] = c_key[j][cursor[j]];
			key_list[i][j] = c_key[j][cursor[j]];
		}
		
		strcpy(key_list[i], temp);
		free(temp);

		cursor[cursor_in_cursor]++;
		while ( i < n-1 && cursor[cursor_in_cursor] == strlen(c_key[cursor_in_cursor]) )
		{
			cursor[cursor_in_cursor] = 0;
			cursor_in_cursor--;
			cursor[cursor_in_cursor]++;
		}
		cursor_in_cursor = atoi(*key_lenght)-1;
	}

	clock_t end = clock();
	for ( int i = 0; i < n; ++i )
	{
		printf("%s ", key_list[i]);
	}
	printf("\n");
	printf("En seulement %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);

	
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		free(c_key[i]);
	}
	free(c_key);
	
}
