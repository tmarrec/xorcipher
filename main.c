#include <stdio.h>
#include <stdlib.h>

#include "readopt.h"

int main(int argc, char *argv[])
{
	printf("hey\n");
	
	char *inputName = 0;
	char *outputName = 0;
	char *key = 0;
	char *mode = 0;
	char *keyLenght = 0;

	readOpt(argc, argv, &inputName, &outputName, &key, &mode, &keyLenght);
	
	printf("inputName: %s\n", inputName);
	printf("outputName: %s\n", outputName);
	printf("key: %s\n", key);
	printf("mode: %s\n", mode);
	printf("keyLenght: %s\n", keyLenght);

	if ( inputName != NULL && outputName != NULL && key != NULL && mode == NULL && keyLenght == NULL )
	{
		printf("Chiffrage/dechiffrage");
	}
	else if ( inputName != NULL && mode != NULL && outputName == NULL && key == NULL )
	{
		printf("Cassage");
	}
	else
	{
		printf("Erreur commande\n");
	}
	return 0;
}
