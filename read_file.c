#include <stdio.h>
#include <stdlib.h>

char* read_file(char **input_name)
{
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	fseek(input_file, 0L, SEEK_END);
	char *file_text = calloc(ftell(input_file), sizeof(char));
	fseek(input_file, 0L, SEEK_SET);
	int c;
	int i = 0;
	//TODO Optimiser avec fread?
	while ( (c = fgetc(input_file)) != EOF )
	{
		file_text[i++] = c;
	}
	file_text[i] = '\0';
	fclose(input_file);
	return file_text;
}

