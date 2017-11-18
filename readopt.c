#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void readOpt(int argc, char *argv[], char **inputName, char **outputName, char **key, char **mode, char **keyLenght)
{
	int c = 0;
	while ( (c = getopt(argc, argv, "i:o:k:m:l:")) != -1 )
	{
		switch(c)
		{
			case 'i':
				*inputName = optarg;
				break;
			case 'o':
				*outputName = optarg;
				break;
			case 'k':
				*key = optarg;
				break;
			case 'm':
				*mode = optarg;
				break;
			case 'l':
				*keyLenght = optarg;
				break;
		}
	}
}
