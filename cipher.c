#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* xor_cipher_return(char *file_text, char key[], int file_size, int key_lenght)
{
	char *file_ciphered = calloc(file_size, sizeof(char));
	unsigned int j;
	for ( j = 0; j < file_size; ++j )
	{
		file_ciphered[j] = key[j%key_lenght]^file_text[j];
	}
	file_ciphered[j] = '\0';
	return file_ciphered;
}

void xor_cipher(char **input_name, char key[], char **output_name)
{
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	
	FILE *output_file;
	output_file = fopen(*output_name, "w+");

	int c = 0;
	int i = 0;
	char ascii_c = 0;
	
	while ( (c = fgetc(input_file)) != EOF )
	{
		ascii_c = key[i];
		fputc(ascii_c ^ c, output_file);
		if ( i < strlen(key)-1 )
		{
			++i;
		}
		else
		{
			i = 0;
		}
	}
	fclose(input_file);
	fclose(output_file);
}
