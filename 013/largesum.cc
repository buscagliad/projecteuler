#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

#define NUM 100


bool getnum(FILE *f, char *lnum)
{
	fgets(lnum, NUM, f);
	if (strlen(lnum) < 10) return false;
	if (feof(f)) return false;
	lnum[50] = 0;
	return true;
}


int main()
{
	FILE *f = fopen("nums.txt", "r");
	char lnum[NUM];
	bool more = getnum(f, lnum);
	BigInt sum = 0;

	while (more)
	{
		BigInt	num(lnum);
		sum += num;
		more = getnum(f, lnum);
	}
	cout << "Sum is: " << sum << endl;
}
