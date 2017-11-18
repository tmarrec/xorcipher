#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void readopt(int argc, char *argv[], char **input_name, char **output_name, char **key, char **mode, char **key_lenght)
{
	int c = 0;
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

char checkopt(char **input_name, char **output_name, char **key, char **mode, char **key_lenght)
{
	printf("input_name: %s\n", *input_name);
	printf("output_name: %s\n", *output_name);
	printf("key: %s\n", *key);
	printf("mode: %s\n", *mode);
	printf("key_lenght: %s\n", *key_lenght);

	if ( *input_name != NULL && *output_name != NULL && *key != NULL && *mode == NULL && *key_lenght == NULL )
	{
		printf("Chiffrage/dechiffrage");
		return 0;
	}
	else if ( *input_name != NULL && *mode != NULL && *output_name == NULL && *key == NULL )
	{
		printf("Cassage");
		return 1;
	}
	else
	{
		printf("\nErreur commande\n");
		printf("Chiffrage / Dechiffrage:\n");
		printf("	./xorcipher -i inTextFile -o outTextFile -k cle\n");
		printf("Cassage:\n");
		printf("	./xorcipher -i inTextFile -m mode [-l longCle]\n");
		return -1;
	}		
}
