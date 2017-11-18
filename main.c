#include <stdio.h>
#include <stdlib.h>

#include "options.h"

int main(int argc, char *argv[])
{
	printf("hey\n");
	
	char *input_name = 0;
	char *output_name = 0;
	char *key = 0;
	char *mode = 0;
	char *key_lenght = 0;

	unsigned char opt_mode = 0;

	readopt(argc, argv, &input_name, &output_name, &key, &mode, &key_lenght);
	opt_mode = checkopt(&input_name, &output_name, &key, &mode, &key_lenght);

	return 0;
}
