#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "cipher.h"

void freq_analysis(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n)
{
	printf("plop\n");
	int freq_letter_france[27] = {9.42,1.02,2.64,3.39,15.87,0.95,1.04,0.77,8.41,0.89,0.00,5.34,3.24,7.15,5.14,2.86,1.06,6.46,7.90,7.26,6.24,2.15,0.00,0.30,0.24,0.32};

	for ( int i = 0; i < *key_list_n; ++i )
	{
		float *freq_letter = (float*)calloc(27, sizeof(float));
		
		
		printf("%s\n", key_list[i]);
		char *output_name = "IO/temp";
		xor_cipher(input_name, key_list[i], &output_name);
		FILE *output_file;
		output_file = fopen(output_name, "r");
		unsigned int n_c = 0;	
		int c = 0;
		while ( (c = fgetc(output_file)) != EOF )
		{
			if ( tolower(c) >= 97 && tolower(c) <= 122 )
			{
				freq_letter[tolower(c)-97]++;
			}
			else if ( (c >= 192 && c <= 194)||(c >= 224 && c <= 226) )
			{
				freq_letter[0]++; /* A */
			}
			else if ( (c >= 200&&c <= 202)||(c >= 232&&c <= 234) )
			{
				freq_letter[4]++; /* E */
			}
			else if ( (c >= 204&&c <= 206)||(c >= 236&&c <= 238) )
			{
				freq_letter[8]++; /* I */
			}
			else if ( (c >= 210&&c <= 212)||(c >= 242&&c <= 244) )
			{
				freq_letter[14]++; /* O */
			}
			else if ( (c >= 218&&c <= 219)||(c >= 249&&c <= 251) )
			{
				freq_letter[20]++; /* U */
			}
			n_c++;
		//:w
		//printf("%c", c);
		}

		for ( int j = 0; j < 27; ++j )
		{
			freq_letter[i] = ((double)freq_letter[j]/(double)n_c)*100;
		}
		
		float d_freq = 0;
		for ( int j = 0; j < 27; j++ )
		{
			d_freq += pow((freq_letter_france[i]-freq_letter[i]),2);
		}
		printf("d_freq: %f\n", d_freq);
	}
}
