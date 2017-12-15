#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "cipher.h"
#include "read_file.h"

void freq_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n)
{
	float freq_letter_france[27] = {9.42,1.02,2.64,3.39,15.87,0.95,1.04,0.77,8.41,0.89,0.00,5.34,3.24,7.15,5.14,2.86,1.06,6.46,7.90,7.26,6.24,2.15,0.00,0.30,0.24,0.32};
	unsigned int min_freq = 0;
	unsigned int min_freq_i = 0;

	char *file_text = NULL;
	file_text = read_file(input_name);
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	fseek(input_file, 0l, SEEK_END);
	unsigned int file_size = ftell(input_file);
	fclose(input_file);
	char *file_ciphered = calloc(file_size, sizeof(char));

	unsigned int n_c = 0;
	int c = 0;
	bool good_c = true;

	for ( unsigned int i = 0; i < (*key_list_n); ++i )
	{
		float *freq_letter = (float*)calloc(27, sizeof(float));
		file_ciphered = xor_cipher_return(file_text, key_list[i], file_size);
		n_c = 0;	
		c = 0;
		good_c = true;
		
		for ( unsigned int j = 0; j < file_size; ++j )
		{
			c = file_ciphered[j];
			if ( c < 0 )
			{
				c += 256;
			}

			switch(c)
			{
				case 65 ... 90:
					freq_letter[tolower(c)-97]++;
					break;

				case 97 ... 122:
					freq_letter[c-97]++;
					break;

				case 192 ... 194:
				case 224 ... 226:
					freq_letter[0]++; // A
					break;

				case 200 ... 202:
				case 232 ... 234:
					freq_letter[4]++; // E
					break;

				case 204 ... 206:
				case 236 ... 238:
					freq_letter[8]++; // I 
					break;

				case 210 ... 212:
				case 242 ... 244:
					freq_letter[14]++; // O
					break;
				
				case 218 ... 219:
				case 249 ... 251:
					freq_letter[20]++; // U
					break;

				default:
					good_c = false;
			}

			if ( good_c == true )
			{
				n_c++;
			}
			good_c = true;
		}

		for ( int j = 0; j < 27; ++j )
		{
			freq_letter[j] = ((float)freq_letter[j]/(float)n_c)*100;
		}
		
		float d_freq = 0;
		for ( int j = 0; j < 27; j++ )
		{
			d_freq += pow((freq_letter_france[j]-freq_letter[j]),2);
		}
		if ( min_freq == 0 )
		{
			min_freq = d_freq;
		}
		else if ( d_freq < min_freq )
		{
			min_freq_i = i;
			min_freq = d_freq;
		}
	}
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		printf("%c", key_list[min_freq_i][i]);
	}
	printf("\n");
}
