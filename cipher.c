#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encode(char **input_name, char **key, char **output_name)
{
	printf("%s\n", *input_name);
		
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	int c = 0;
	int i = 0;
	char ascii_c = 0;
	while ( (c = fgetc(input_file)) != EOF )
	{
		ascii_c = (int)*(*key+i);
		printf("%x ", ascii_c ^ c);
		if ( i < strlen(*key)-1 )
		{
			++i;
		}
		else
		{
			i = 0;
		}
	}
}
