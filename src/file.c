#include <stdio.h>
#include <stdlib.h>

/****************************************************************
* GET_FILE_SIZE *                                               *
*****************                                               *
* Calcule la taille d'un fichier                                *
*                                                               *
* **input_name : Le nom du fichier en entrée                    *
*                                                               *
* file_size : Taille du fichier                                 *
****************************************************************/

unsigned long get_file_size(char **input_name)
{
	FILE *input_file = NULL;
	input_file = fopen(*input_name, "r");
	fseek(input_file, 0l, SEEK_END);
	unsigned long file_size = ftell(input_file);
	fclose(input_file);
	return file_size;
}

/****************************************************************
* READ_FILE *                                                   *
*************                                                   *
* Met tout les caractères d'un fichier dans un tableau          *
*                                                               *
* **input_name : Le nom du fichier en entrée                    *
*                                                               *
* file_text : Tout les caractères du fichier                    *
****************************************************************/

unsigned char* read_file(char **input_name)
{
	FILE *input_file = NULL;
	input_file = fopen(*input_name, "r");
	unsigned char *file_text = NULL;
	file_text = calloc(1, sizeof(unsigned char));
	char c;
	unsigned long i = 0;
	while ( (c = fgetc(input_file)) != EOF )
	{
		file_text[i++] = (unsigned char)c;
		file_text = realloc(file_text, (i+1)*sizeof(char));
	}
	file_text[i] = 0;
	fclose(input_file);
	return file_text;
}
