// this header file support retrieving the totient value of n (phi(n))

#ifndef __TOTIENT_H__
#define __TOTIENT_H__


#include <stdio.h>
#include <stdlib.h>


//
// totient(int n) returns euler's totient function phi(n)
long totient(int n);

#define TOTIENT_FILE_DIRECTORY "/home/dave/projecteuler/totient/"
#define TOTIENT_TITLE_SIZE 100
#define TOTIENT_FILE_SIZE 1000000
#define TOTIENT_FILE_MAX  5  // currently only first 5 million totient values
#define TOTIENT_MAX_NUMBERS 50000000 // product of FILE_SIZE * FILE_MAX
static	long totient_list[TOTIENT_MAX_NUMBERS];
static	char totient_file_name[TOTIENT_TITLE_SIZE];
static	int  totient_file_index = 0;  // file 1 thru 50
static	int  totient_list_size;
static	long  totient_max_index;



#define INIT_TOTIENT_FILE	if (totient_file_index == 0) readTotientFile(1);

inline
bool	readTotientFile(int n)
{
	if (n <= totient_file_index) return true;
	if (n < 1 || n > TOTIENT_FILE_MAX) 
	{
		printf("ERROR - requested file exceeds allowed number (cur file:%d -  des file: %d)\n",
			totient_file_index, n);
		return false;
	}
	if (n == 1) totient_list_size = 0;
	if (n <= totient_file_index) return true;

	totient_file_index = n;
	sprintf(totient_file_name, "%sphi%2.2d.txt", TOTIENT_FILE_DIRECTORY, totient_file_index);
	FILE *f = fopen(totient_file_name, "r");
	if (!f) return false;
	while (!feof(f) && totient_list_size < n * TOTIENT_FILE_SIZE)
	{
		fscanf(f, "%ld", totient_list + totient_list_size);
		totient_list_size++;
	}
	totient_max_index = n * TOTIENT_FILE_SIZE;
	printf("ReadFile: %s    %d elements\n",
		totient_file_name, totient_list_size);
	fclose(f);
	return true;
}	



// totient(n) returns euler's totient function phi(n) 

inline
long totient(int n)
{
	INIT_TOTIENT_FILE;
	if (n < 1) return 0;
	n--; //adjust totient index
	if (n > totient_max_index) 
	{
		if (totient_file_index < TOTIENT_FILE_MAX)
		{
			printf(">totient(%d) ReadFile: %s - %d elements\n",
				n, totient_file_name, totient_list_size);
			readTotientFile(totient_file_index + 1);
			return totient(n);
		}
		else
		{
			printf("ERROR - totient index %d exceeds table\n", n);
			return -1;
		}
	}
	return totient_list[n];
}


#endif
