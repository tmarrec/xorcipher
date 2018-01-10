#include <string.h>
#include <stdbool.h>

/****************************************************************
* CHECKKEY *                                                    *
************                                                    *
* Vérifie pour chaque caractères de la clé donné en entrée      *
* s'ils est un caractère valide pour une clé.                   *
*                                                               *
* **key : Clé                                                   *
****************************************************************/
bool checkkey(char **key)
{
	char ascii_c = 0;
	for ( unsigned char i = 0; i < strlen(*key); ++i )
	{
		ascii_c = (char)*(*key+i);
		switch(ascii_c)
		{
			case 0 ... 43:
		 	case 47:
			case 59 ... 62:
			case 64:
			case 91 ... 94:
			case 96:
			case 124:
			case 126 ... 127:
				return false;
		}
	}
	return true;
}

/****************************************************************
* CHECKMESSAGE_OPT *                                            *
********************                                            *
* Vérifie pour chaque caractères modulo l_key du texte donné en *
* entrée s'ils sont des caractères valides pour un texte        *
* déchiffré.                                                    *
*                                                               *
* *file_text : Tout les caractères du fichier                   *
* i_key : Position du caractère dans la clé                     *
* l_key : Longueur de la clé                                    *
* file_size : Longueur du fichier                               *
****************************************************************/
bool checkmessage_opt(unsigned char *file_text, unsigned char i_key, unsigned int l_key, unsigned long file_size)
{
	unsigned char c = 0;
	unsigned long i = (unsigned long)i_key;
	while ( i < file_size )
	{
		c = file_text[i];
		switch(c)
		{
			case 0 ... 9:
			case 11 ... 31:
			case 35 ... 38:
			case 42 ... 43:
			case 47 ... 57:
			case 60 ... 62:
			case 64:
			case 91 ... 94:
			case 96:
			case 124:
			case 126 ... 130:
			case 132 ... 191:
			case 193:
			case 195:
			case 197 ... 198:
			case 204 ... 205:
			case 208 ... 211:
			case 213:
			case 215 ... 216:
			case 218:
			case 220 ... 223:
			case 225:
			case 227:
			case 229 ... 231:
			case 236 ... 237:
			case 240 ... 243:
			case 245:
			case 247 ... 248:
			case 250:
			case 252 ... 255:
				return false;
		}
		i += l_key;
	}
	return true;
}
