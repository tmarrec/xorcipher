#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************************
* XOR_CIPHER_RETURN *                                           *
*********************                                           *
* Chiffre le texte donné en entrée et renvoie le texte chiffré	*
*                                                               *
* *file_texte : Texte non chiffré                               *
* key[] : Clé                                                   *
* file_size : Longueur du texte                                 *
* key_lenght : Longueur de la clé                               *
****************************************************************/

unsigned char* xor_cipher_return(unsigned char *file_text, char key[], unsigned long file_size, int key_lenght)
{
	unsigned char *file_ciphered = NULL;
	file_ciphered = calloc(file_size, sizeof(unsigned char));
	unsigned long i;
	for ( i = 0; i < file_size; ++i )
	{
		file_ciphered[i] = key[i%key_lenght]^file_text[i];
	}
	file_ciphered[i] = 0;
	return file_ciphered;
}

/****************************************************************
* XOR_CIPHER *                                                  *
**************                                                  *
* Chiffre le fichier donné en entrée et l'écrit dans un autre 	*
* fichier                                                       *
*                                                               *
* **input_name : Nom du fichier donné en entrée                 *
* key[] : Clé                                                   *
* **output_name : Nom du fichier donné en sortie                *
****************************************************************/

void xor_cipher(char **input_name, char key[], char **output_name)
{
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	FILE *output_file;
	output_file = fopen(*output_name, "w+");
	int c = 0;
	unsigned long i = 0;
	unsigned char key_lenght = strlen(key);
	while ( (c = fgetc(input_file)) != EOF )
	{
		fputc(key[i%key_lenght]^c,output_file);
		i++;
	}
	fclose(input_file);
	fclose(output_file);
}
