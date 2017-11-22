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
	
	char **key_list = NULL;
	unsigned int n = 0;
	

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
		start = clock();
		if ( atoi(key_lenght) > 0 )
		{
			n = c_validate(&input_name, &key_lenght, key_list);
		}
		else
		{
			key_lenght = malloc(1*sizeof(int));
			for ( int i = 3; i < 8; ++i )
			{
				key_lenght[0] = i+'0';
				n = c_validate(&input_name, &key_lenght, key_list);
			}
		}
		end = clock();
		printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);
		if ( *mode == 49 )
		{
			if ( atoi(key_lenght) > 0 )
			{
				freq_analysis(&input_name, &key_lenght, key_list, n);
			}
		}
		else
		{
			
		}
	}
	return 0;
}
