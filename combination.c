#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void combination_arrays(char **key_lenght, int n, int *cursor, char **key_list, char **c_key, int int_key_lenght)
{	
	char *temp = NULL;
	temp = calloc(int_key_lenght+1, sizeof(char*));
	
	unsigned int cursor_in_cursor = int_key_lenght-1; // LuL
	for ( unsigned int i = 0; i < n; ++i )
	{
		for ( unsigned char j = 0; j < int_key_lenght; ++j )
		{
			temp[j] = c_key[j][cursor[j]];
			//key_list[i][j] = c_key[j][cursor[j]];
		}
		
		strcpy(key_list[i], temp);

		cursor[cursor_in_cursor]++;
		while ( i < n-1 && cursor[cursor_in_cursor] == strlen(c_key[cursor_in_cursor]) )
		{
			cursor[cursor_in_cursor] = 0;
			cursor_in_cursor--;
			cursor[cursor_in_cursor]++;
		}
		cursor_in_cursor = int_key_lenght-1;
	}
	free(temp);
}

char** get_key_list(char **key_lenght, char **c_key, unsigned int *key_list_n)
{
	int int_key_lenght = atoi(*key_lenght);
	unsigned int n = 1;
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		n = n*(int)strlen(c_key[i]);
	}
	int *cursor = NULL;
	cursor = calloc(int_key_lenght, sizeof(int));

	char **key_list = NULL;
	key_list = calloc(n, sizeof(char**));
	for ( unsigned int i = 0; i < n; ++i )
	{
		key_list[i] = calloc(int_key_lenght, sizeof(char*));
	}
	combination_arrays(key_lenght, n, cursor, key_list, c_key, int_key_lenght);
	for ( unsigned int i = 0; i < int_key_lenght; ++i )
	{
		free(c_key[i]);
	}
	free(c_key);
	free(cursor);
	*key_list_n = n;

	return key_list;
}
