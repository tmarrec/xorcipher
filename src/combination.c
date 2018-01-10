#include <stdlib.h>
#include <string.h>

/****************************************************************
* COMBINATION_ARRAYS *                                          *
**********************                                          *
* Fait la combinaison des clés possibles avec les caractères    *
* possibles                                                     *
*	                                                              *
* n : Nombre de clé	possible                                    *
* *cursor : curseur dans les clés                               *
* **key_list : Liste des clés possibles                         *
* **c_key : Liste des caractères possibles pour les clés        *
* int_key_lenght : Longueur de la clé                           *
* *c_key_lenght : Tableau de la longueur des clés               *
****************************************************************/
// Ici je creer un tableau contenant le nombre de caractères possibles
// pour chaque caractère de la clé, par exemple :
// [ab][cdef][g] -> [2][4][1]
// Puis je creer un tableau dont chaque case est codé en base de la
// case du tableau précédent.
// Ex:  pour [2][4][1]
//            ^  ^  ^
// base 2 ----|  |  |
// base 4 -------|  |
// base 1 ----------|
// Et a ce tableau dont chaque case a une base différente je
// l'incrémente a chaque tour de boucle
// Ce qui donne les indices des caractères de la clé, et ces
// indices forment l'ensemble des clés possibles
void combination_arrays(unsigned long n, unsigned long *cursor, char **key_list, char **c_key, unsigned char int_key_lenght, unsigned char *c_key_lenght)
{
	char *temp = NULL;
	temp = calloc(int_key_lenght, sizeof(char));
	unsigned char cursor_in_cursor = int_key_lenght-1;
	for ( unsigned long i = 0; i < n; ++i )
	{
		for ( unsigned char j = 0; j < int_key_lenght; ++j )
		{
			temp[j] = c_key[j][cursor[j]];
		}
		strcpy(key_list[i], temp);
		cursor[cursor_in_cursor]++;
		while ( i < n-1 && cursor[cursor_in_cursor] == c_key_lenght[cursor_in_cursor] )
		{
			cursor[cursor_in_cursor] = 0;
			cursor_in_cursor--;
			cursor[cursor_in_cursor]++;
		}
		cursor_in_cursor = int_key_lenght-1;
	}
	free(temp);
}

/****************************************************************
* GET_KEY_LIST *                                                *
****************                                                *
* Recupere la liste des clés possible a partir de la liste      *
* des caractères possibles                                      *
*                                                               *
* **key_lenght : Longueur de la clé                             *
* **c_key : Liste des caractères possibles pour les clés        *
* *key_list_n : Nombre de clé possible                          *
*                                                               *
* key_list : Liste des clés                                     *
****************************************************************/

char** get_key_list(char **key_lenght, char **c_key, unsigned long *key_list_n)
{
	unsigned char int_key_lenght = atoi(*key_lenght);
	unsigned char *c_key_lenght = NULL;
	c_key_lenght = calloc(int_key_lenght, sizeof(unsigned char));
	unsigned long n = 1;
	char temp;
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		temp = strlen(c_key[i]);
		n = n*temp;
		c_key_lenght[i] = temp;
	}
	unsigned long *cursor = NULL;
	cursor = calloc(int_key_lenght, sizeof(unsigned long));
	char **key_list = NULL;
	key_list = calloc(n, sizeof(char**));
	for ( unsigned int i = 0; i < n; ++i )
	{
		key_list[i] = calloc(int_key_lenght, sizeof(char*));
	}
	combination_arrays(n, cursor, key_list, c_key, int_key_lenght, c_key_lenght);
	// Libère la mémoire
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		free(c_key[i]);
	}
	free(c_key);
	free(cursor);
	free(c_key_lenght);
	*key_list_n = n;
	return key_list;
}
