#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "options.h"
#include "checkascii.h"
#include "cipher.h"
#include "c_validate.h"
#include "freq_analysis.h"

int main(int argc, char *argv[])
{
	char *input_name = NULL;
	char *output_name = NULL;
	char *key = NULL;
	char *mode = NULL;
	char *key_lenght = NULL;
	unsigned char opt_mode = 0;

	clock_t start = 0;
	clock_t end = 0;
	
	readopt(argc, argv, &input_name, &output_name, &key, &mode, &key_lenght);
	opt_mode = checkopt(&input_name, &output_name, &key, &mode, &key_lenght);
	if ( opt_mode == 0 )
	{
		start = clock();
		xor_cipher(&input_name, key, &output_name);
		end = clock();
		printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);

	}
	else
	{
		c_validate(&input_name, &key_lenght);
		if ( *mode == 49 )
		{
			freq_analysis(&input_name);
		}
		else
		{
			
		}
	}
	return 0;
}
