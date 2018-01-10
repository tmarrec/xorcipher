#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#include "cipher.h"
#include "file.h"

/****************************************************************
* INCREASE_FREQ_LETTER *                                        *
************************                                        *
* Augmente la valeur de la fréquence d'apparition d'un          *
* caractère                                                     *
*                                                               *
* j : Position du curseur dans le tableau de charactère         *
* *n_c : Nombre de caractères dans le tableau                   *
* *freq_letter : La fréquence d'apparition des lettres          *
* *file_ciphered : Tableau de caractères du fichier chiffré	    *
****************************************************************/

void increase_freq_letter(unsigned long j, unsigned long *n_c, float *freq_letter, unsigned char *file_ciphered)
{
	bool good_c = true;
	unsigned char c;
	c = file_ciphered[j];
	switch(c)
	{
		case 65 ... 90:
			freq_letter[tolower(c)-97]++;
			break;
		case 97 ... 122:
			freq_letter[c-97]++;
			break;
		case 192 ... 194:
		case 196:
		case 224 ... 228:
			freq_letter[0]++; // A
			break;
		case 200 ... 203:
		case 232 ... 235:
			freq_letter[4]++; // E
			break;
		case 199:
		case 131:
			freq_letter[2]++; // C
			break;
		case 206 ... 207:
		case 238 ... 239:
			freq_letter[8]++; // I
			break;
		case 212:
		case 214:
		case 244:
		case 246:
			freq_letter[14]++; // O
			break;
		case 217:
		case 219:
		case 249:
		case 251:
			freq_letter[20]++; // U
			break;
		default:
			good_c = false;
	}
	if ( good_c == true )
	{
		(*n_c)++;
	}
	else
	{
		good_c = true;
	}
}

/****************************************************************
* INCREASE_FREQ_LETTER *                                        *
************************                                        *
* Utilise l'analyse de fréquence des caractères pour déterminer	*
* la clé probable                                               *
*                                                               *
* **input_name : Nom du fichier en entrée                       *
* **key_lenght : Longueur de la clé                             *
* **key_list : Liste des clés possibles                         *
* *key_list_n : Nombre de clés                                  *
****************************************************************/

void freq_analysis(char **input_name, char **key_lenght, char **key_list, unsigned long *key_list_n)
{
	float freq_letter_france[27] = {9.42,1.02,2.64,3.39,15.87,0.95,1.04,0.77,8.41,0.89,0.00,5.34,3.24,7.15,5.14,2.86,1.06,6.46,7.90,7.26,6.24,2.15,0.00,0.30,0.24,0.32};
	unsigned long min_freq = 0;
	unsigned long min_freq_i = 0;
	unsigned char *file_text = NULL;
	file_text = read_file(input_name);
	unsigned long file_size = get_file_size(input_name);
	unsigned char *file_ciphered = calloc(file_size, sizeof(unsigned char));
	unsigned long n_c = 0;
	float d_freq = 0;
	float *freq_letter = (float*)calloc(27, sizeof(float));
	unsigned char int_key_lenght = atoi(*key_lenght);
	for ( unsigned long i = 0; i < (*key_list_n); ++i )
	{
		file_ciphered = xor_cipher_return(file_text, key_list[i], file_size, int_key_lenght);
		n_c = 0;
		for ( unsigned long j = 0; j < file_size; ++j ) // Augmente la fréquence pour chaque char
		{
			increase_freq_letter(j, &n_c, freq_letter, file_ciphered);
		}
		d_freq = 0;
		for ( unsigned char j = 0; j < 27; ++j ) // Calcule la fréquence pour les char de A a Z
		{
			d_freq += pow((freq_letter_france[j]-((freq_letter[j]/n_c)*100)),2);
			freq_letter[j] = 0;
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
	for ( unsigned char i = 0; i < int_key_lenght; ++i )
	{
		printf("%c", key_list[min_freq_i][i]);
	}
	printf("\n");
}
