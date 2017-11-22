#include <stdio.h>
#include <stdlib.h>

#include "cipher.h"

void freq_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n)
{
	printf("plop\n");
	for ( int i = 0; i < *key_list_n; ++i )
	{
		unsigned int **freq_letter = (unsigned int**)calloc(27, sizeof(unsigned int*));
		for ( int i = 0; i < 27; ++i )
		{
			freq_letter[i] = (unsigned int*)calloc(2, sizeof(unsigned int));
		}
		printf("%s\n", key_list[i]);
		char *output_name = "IO/temp";
		xor_cipher(input_name, key_list[i], &output_name);
		FILE *output_file;
		output_file = fopen(output_name, "r");
	
		int c = 0;
		while ( (c = fgetc(output_file)) != EOF )
		{
			printf("%c", c);
		}
		printf("\n");
	}
}
