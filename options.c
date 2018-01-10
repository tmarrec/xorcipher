#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "checkascii.h"

/****************************************************************
* READOPT *													    *
***********														*
* Stocke dans des variables les options entrées par				*
* l'utilisateur.										 		*
*																*
* argc :														*
* *argv[] :														*
* **input_name : Nom du fichier en entrée						*
* **output_name : Nom du fichier en sortie						*
* **key : Clé													*
* **mode : Mode choisis											*
* **key_lenght : Longueur de la clé								*
****************************************************************/

void readopt(int argc, char *argv[], char **input_name, char **output_name, char **key, char **mode, char **key_lenght)
{
	char c = 0;
	while ( (c = getopt(argc, argv, "i:o:k:m:l:")) != -1 )
	{
		switch(c)
		{
			case 'i':
				*input_name = optarg;
				break;
			case 'o':
				*output_name = optarg;
				break;
			case 'k':
				*key = optarg;
				break;
			case 'm':
				*mode = optarg;
				break;
			case 'l':
				*key_lenght = optarg;
				break;
		}
	}
}

/****************************************************************
* CHECKOPT *												    *
************													*
* Vérifie que toutes les options soient correctes et retourne	*
* le mode choisis												*
*																*
* **input_name : Nom du fichier d'entrée						*
* **output_name : Nom du fichier en sortie						*
* **key : Clé													*
* **mode : Mode choisis											*
* **key_lenght : Longueur de la clé								*
****************************************************************/

unsigned char checkopt(char **input_name, char **output_name, char **key, char **mode, char **key_lenght)
{
    //	Verifie que la commande soit correcte.
	unsigned char opt_mode = 0;
	if ( *input_name != NULL && *output_name != NULL && *key != NULL && *mode == NULL && *key_lenght == NULL )
	{
		opt_mode = 0; // Mode chiffrage / dechiffrage
	}
	else if ( *input_name != NULL && *mode != NULL && *output_name == NULL && *key == NULL )
	{
		if ( *key_lenght == NULL )
		{
			*key_lenght = "0";
		}
		opt_mode = 1; // Mode cassage
	}
	else
	{
		printf("\nErreur commande\n");
		printf("Chiffrage / Dechiffrage:\n");
		printf("	./xorcipher -i inTextFile -o outTextFile -k cle\n");
		printf("Cassage:\n");
		printf("	./xorcipher -i inTextFile -m mode [-l longCle]\n");
		exit(-1);
	}
	// Verifie que le fichier input existe et soit accessible en lecture.
	FILE *test_read_file;
	if ( (test_read_file = fopen(*input_name, "r") ) == NULL )
	{
		printf("Impossible d'ouvrir le fichier donne en lecture\n");
		exit(-1);
	}
	fclose(test_read_file);
	// Si on est en mode Chiffrage / Dechiffrage, verifie si la cle est valide
	if ( opt_mode == 0 )
	{
		if ( checkkey(key) == false )
		{
			printf("La cle n'est pas valide\n");
			exit(-1);
		}
		return 0;
	}
	return 1;
}
