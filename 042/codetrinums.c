#ifdef PROBLEM_DESCRIPTION

Coded triangle numbers


Problem 42

The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?

#endif

#include <stdio.h>
#include <ctype.h>

long
getWord(FILE *f, char *w)
{
	int rv = 0;
	int c = fgetc(f);
	while (!isalpha(c)) { c = fgetc(f); if (feof(f)) return -1; }
	while (isalpha(c)) { rv += c - 'A' + 1; *w++ = c; c = fgetc(f); }
	*w = 0;
	if (feof(f)) return -1;
	return rv;
}

#define MAX_TRI 50
int triNums[MAX_TRI];
void init()
{
	for (int i = 0; i < MAX_TRI; i++)
	{
		triNums[i] = (i+1)*(i+2)/2;
	}
}

bool isTri(int n)
{
	for (int i = 0; i < MAX_TRI; i++)
	   if (n == triNums[i]) return true;
	return false;
}

#define YN(g) (g)?"YES":"NO"

int main()
{
	init();
	char w[1000];
	int count = 0;
	FILE *f = fopen("p042_words.txt", "r");
	long g = getWord(f, w);
	while (g > 0)
	{
		bool tt = isTri(g);
		if (tt) count++;
		printf("Word: %s   Value: %ld (%s)\n", w, g, YN(tt));
		g = getWord(f, w);
	}
	printf("Total number of words that are triangle numbers: %d\n", count);
}
	
