#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cipher.h"
#include "checkascii.h"
#include "file.h"
#include "combination.h"


/****************************************************************
* PRINT_RESULT *                                                *
****************                                                *
* Affiche chaque caractères possibles pour les clés             *
*                                                               *
* **c_key : Liste des caractères possibles                      *
* int_key_lenght : Longueur de la clé                           *
****************************************************************/

void print_result(char **c_key, int int_key_lenght)
{
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		printf("[");
		printf("%s", c_key[i]);
		printf("]");
	}
	printf("\n");
}

/****************************************************************
* GET_C_KEY *                                                   *
*************                                                   *
* Cherche les caractères possible pour les clés.                *
*                                                               *
* **c_key : Liste des caractères possibles                      *
* **input_name : Nom du fichier en entrée                       *
* need_print_result : Doit-on afficher le resultat?             *
* int_key_lenght : Longueur de la clé                           *
****************************************************************/

char get_c_key(char **c_key, char **input_name, bool need_print_result, unsigned char int_key_lenght)
{
	char key[1];
	unsigned char alphabet[71] = {44,45,46,48,49,50,51,52,53,54,55,56,57,58,63,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,125};
	unsigned char key_n = 0;
	unsigned char *file_text = NULL;
	file_text = read_file(input_name);
	unsigned long file_size = get_file_size(input_name);
	unsigned char *file_ciphered = NULL;
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		key_n = 0;
		for ( unsigned int j = 0; j < 71; ++j )
		{
			file_ciphered = calloc(file_size+1, sizeof(char));
			key[0] = alphabet[j];
			// Dechiffre le fichier chiffrer avec la clé key[0]
			file_ciphered = xor_cipher_return(file_text, key, file_size, 1);
			// Verifie si le fichier déchiffré a tout les caractères valides
			if ( checkmessage_opt(file_ciphered, i, int_key_lenght, file_size) == true )
			{
				c_key[i][key_n] = alphabet[j];
				key_n++;
			}
			free(file_ciphered);
		}
		if ( key_n == 0 ) // S'il n'y a pas de caractère possible
		{
			free(file_text);
			return -1;
		}
		c_key[i][key_n] = 0;
	}
	if ( need_print_result == true )
	{
		print_result(c_key, int_key_lenght);
	}
	free(file_text);
	return 1;
}

/****************************************************************
* C_VALIDATE *                                                  *
**************                                                  *
* Retourne la liste des caractères possible pourr les clés.     *
*                                                               *
* **input_name : Nom du fichier en entrée                       *
* **key_lenght : Longueur de la clé                             *
* print_result : Doit-on afficher le resultat?                  *
* *isok : Y a t'il des clés possibles?                          *
*                                                               *
* c_key : Liste des caractères possibles                        *
****************************************************************/

char** c_validate(char **input_name, char **key_lenght, bool print_result, bool *isok)
{
	unsigned char int_key_lenght = atoi(*key_lenght);
	char **c_key = NULL;
	c_key = (char**)calloc(int_key_lenght, sizeof(char*));
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		c_key[i] = (char*)calloc(71, sizeof(char));
	}
	if ( get_c_key(c_key, input_name, print_result, int_key_lenght) == -1 )
	{
		*isok = false;
	}
	return c_key;
}
