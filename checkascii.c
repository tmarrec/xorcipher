#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
				break;
		}
	}
	return true;
}

bool checkmessage_opt(char *file_text, unsigned int i_key, unsigned int l_key, int file_size)
{
		
	int c = 0;
	int i = i_key;
	while ( i < file_size )
	{
		c = file_text[i];
		if ( c < 0 )
		{
			c = 256+c;
		}
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
				break;
		}
		i += l_key;
	}
	return true;
}
 
bool checkmessage(char **input_name, unsigned int i_key, unsigned int l_key)
{
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	int c = 0;
	fseek(input_file, i_key, SEEK_SET);
	while ( (c = fgetc(input_file)) != EOF )
	{
		if ( !((c >= 65&& c <= 90)||(c >= 97 && c <= 122)||(c == 32)||(c == 33||c == 34||c == 39||c == 40||c == 41||c == 59)||(c >= 44 && c <= 46)||(c == 58||c == 63||c == 95||c == 123||c == 125)||(c == 192||c == 194||c == 196||c == 224||c == 226||c == 228||c == 199||c == 131||c == 200||c == 201||c == 202||c == 203||c == 232||c == 233||c == 234||c == 235||c == 206||c == 207||c == 238||c == 239||c == 217||c == 219||c == 249||c == 251||c == 212||c == 214||c == 244||c == 246) || c == 10 ))
		{
			fclose(input_file);
			return false;
		}
		fseek(input_file, l_key-1, SEEK_CUR);
	}
	fclose(input_file);
	return true;
}
