#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool checkkey(char **key)
{
	bool key_is_ok = true;
	int ascii_c = 0;
	for ( int i = 0; i < strlen(*key); ++i )
	{
		ascii_c = (int)*(*key+i);
		if (!((ascii_c >= 65 && ascii_c <= 90)||(ascii_c >= 97 && ascii_c <= 122)||(ascii_c >= 44 && ascii_c <= 46 )||(ascii_c == 58)||(ascii_c == 63)||(ascii_c == 95)||(ascii_c == 123)||(ascii_c == 125)||(ascii_c >= 48 && ascii_c <= 57)))
		{
			return false;
		}
	}
	return true;
}
