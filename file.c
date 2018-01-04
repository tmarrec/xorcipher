#include <stdio.h>
#include <stdlib.h>

char* read_file(char **input_name)
{
	FILE *input_file = NULL;
	input_file = fopen(*input_name, "r");
	char *file_text = NULL;
	file_text = calloc(1, sizeof(char));
	int c;
	unsigned long i = 0;
	while ( (c = fgetc(input_file)) != EOF )
	{
		file_text[i++] = c;
		file_text = realloc(file_text, (i+1)*sizeof(char));
	}
	file_text[i] = 0;
	fclose(input_file);
	return file_text;
}

unsigned long get_file_size(char **input_name)
{
	FILE *input_file = NULL;
	input_file = fopen(*input_name, "r");
	fseek(input_file, 0l, SEEK_END);
	unsigned long file_size = ftell(input_file);
	fclose(input_file);
	return file_size;
}
