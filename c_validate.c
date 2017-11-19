#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cipher.h"
#include "checkascii.h"

void c_validate(char **input_name)
{
	printf("boi\n");
	char *output_name = "IO/output2";
	char key[] = "";
	
	FILE *c_key_file;
	c_key_file = fopen("c_key", "r");
	int c = 0;
	for ( int i = 0; i < 3; ++i )
	{
		while ( (c = fgetc(c_key_file)) != EOF )
		{
			key[0] = c;
			xor_cipher(input_name, key, &output_name);
			if ( checkmessage(&output_name, i, 3) == 1 )
			{
				printf("key : %c \n", c);
			}
		}
		printf("\n");
		fseek(c_key_file, 0, SEEK_SET);
	}
}
