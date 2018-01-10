#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "options.h"
#include "cipher.h"
#include "c_validate.h"
#include "freq_analysis.h"
#include "dict_analysis.h"
#include "combination.h"

int main(int argc, char *argv[])
{
	char *input_name = NULL;
	char *output_name = NULL;
	char *key = NULL;
	char *mode = NULL;
	char *key_lenght = NULL;
	unsigned char opt_mode = 0;
	char **c_key = NULL;
	char **key_list = NULL;
	unsigned long *key_list_n = NULL;
	key_list_n = calloc(1, sizeof(unsigned long));
	clock_t start = 0;
	clock_t end = 0;
	bool isok = true;
	// Lis les options	
	readopt(argc, argv, &input_name, &output_name, &key, &mode, &key_lenght);
	opt_mode = checkopt(&input_name, &output_name, &key, &mode, &key_lenght);
	if ( opt_mode == 0 ) // Chiffrage/Dechiffrage
	{
		start = clock();
		xor_cipher(&input_name, key, &output_name);
		end = clock();
		printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);
	}
	else
	{
		if ( *mode == 49 ) // -m 1
		{
			if ( atoi(key_lenght) > 0 ) // avec -l
			{
				start = clock();
				c_key = c_validate(&input_name, &key_lenght, true, &isok);
				end = clock();
				// Dans le cahier des charges il est dit de mettre les temps pour tout les modules
				// Donc il valide pas les scripts de tests
				printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);
			}
			else // sans -l
			{
				start = clock();
				key_lenght = calloc(1, sizeof(char));
				for ( char i = 3; i < 8; ++i )
				{
					key_lenght[0] = i+'0';
					c_key = c_validate(&input_name, &key_lenght, true, &isok);
				}
				free(key_lenght);
				end = clock();
				printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);
			}
		}
		else if ( *mode == 50 ) // -m 2
		{
			if ( atoi(key_lenght) > 0 ) // avec -l
			{	
				start = clock();
				c_key = c_validate(&input_name, &key_lenght, false, &isok);
				key_list = get_key_list(&key_lenght, c_key , key_list_n);
				freq_analysis(&input_name, &key_lenght, key_list, key_list_n);
				end = clock();
				printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);
			}
			else // sans -l
			{
				start = clock();
				key_lenght = malloc(1*sizeof(int));
				for ( int i = 3; i < 8; ++i )
				{
					key_lenght[0] = i+'0';
					c_key = c_validate(&input_name, &key_lenght, false, &isok);
					if ( isok == true )
					{
						key_list = get_key_list(&key_lenght, c_key, key_list_n);
						freq_analysis(&input_name, &key_lenght, key_list, key_list_n);
					}
					else
					{
						isok = true;
					}
				}
				free(key_lenght);
				end = clock();
				printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);
			}
		}
		else // -m 3
		{
			if ( atoi(key_lenght) > 0 ) // avec -l
			{
				start = clock();
				c_key = c_validate(&input_name, &key_lenght, false, &isok);
				key_list = get_key_list(&key_lenght, c_key, key_list_n);
				dict_analysis(&input_name, &key_lenght, key_list, key_list_n);
				end = clock();
				printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);
			}
			else // sans -l
			{
				start = clock();
				key_lenght = malloc(1*sizeof(int));
				for ( int i = 3; i < 8; ++i )
				{
					key_lenght[0] = i+'0';
					c_key = c_validate(&input_name, &key_lenght, false, &isok);
					if ( isok == true )
					{
						key_list = get_key_list(&key_lenght, c_key, key_list_n);
						dict_analysis(&input_name, &key_lenght, key_list, key_list_n);
					}
					else
					{
						isok = true;
					}

				}
				free(key_lenght);
				end = clock();
				printf("En %f secondes faut le savoir hein !\n", (double)(end-start)/CLOCKS_PER_SEC);
			}
		}
	}
	return EXIT_SUCCESS;
}
