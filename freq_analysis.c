#include <stdio.h>
#include <stdlib.h>

void freq_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int n)
{
	printf("plop\n");
	printf("n : %u\n", n);

	for ( int i = 0; i < n; ++i )
	{
		printf("%s ", key_list[i]);
	}
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	
	int c = 0;
	while ( (c = fgetc(input_file)) != EOF )
	{
		printf("%c ", c);
	}
	printf("\n");
}
