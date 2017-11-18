#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("hey\n");
	int c;
	char *inputName = 0;
	char *outputName = 0;
	char *key = 0;
	char *mode = 0;
	char *keyLenght = 0;
	while ( (c = getopt(argc, argv, "i:o:k:m:l:")) != -1 )
	{
		switch(c)
		{
			case 'i':
				inputName = optarg;
				break;
			case 'o':
				outputName = optarg;
				break;
			case 'k':
				key = optarg;
				break;
			case 'm':
				mode = optarg;
				break;
			case 'l':
				keyLenght = optarg;
				break;
		}
	}
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
		printf("Erreur commande");
	}
	return 0;
}
