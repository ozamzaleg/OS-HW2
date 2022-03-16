#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "targil2.h"
#include "defenition.h"


int *readArrFromFile(FILE *file, char *letter, int *len)
{

	int *arr;

	if (fscanf(file, "%c%d", letter, len) != 2)
	{

		ferror(file);
		exit(EXIT_FAILURE);
	}

	arr = (int *)calloc((*len),sizeof(int));
	if (!arr)
	{
		printf("%s", "allocate not succss");
		exit(EXIT_FAILURE);
	}
	
	return arr;
}



void readElementFromFile (FILE *file , int len, int* arr)
	{
	
	for (int i = 0; i < len; i++)
	{
		if (fscanf(file, "%d", &arr[i]) != 1)
		{
			ferror(file);
			exit(EXIT_FAILURE);
		}
	}
}


char* getNameFile(char* argv[], int argc)
{
	for (int i = 0; i < argc; i++)
	{	
		
		if ((strstr(argv[i], TEXT)) != NULL)
		{
	
			return argv[i];
		}
	}
	return NULL;
}


int getMax(int* arr, int start, int end)
{

	int max = arr[0];
	for (int i = start; i < end; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}
