#include <cstdio>
#include <cstdlib>
#include "digit.h"
#include "prime.h"
#include "factor.h"

#define ANSWER 10647966294722

#define CLARGE  120000 //1000

int	Rad[CLARGE];
//bool RelPrime[CLARGE][CLARGE];

void init()
{
	int max = 0;
	for (int i = 1; i < CLARGE; i++)
	{
	    Rad[i] = factor(i).rad();
	    if (Rad[i] > max) max = Rad[i];
	}
	printf("Max rad is: %d\n", max);
	//for (int i = 1; i < CLARGE; i++)
	//    for (int j = 1; j < CLARGE; j++)
	//		RelPrime[i][j] = gcd(i, j) == 1;

}

#define relprime(a,b) (gcd(a,b)==1)

int main()
{
	Prime p;
	long a, b, c;
	long ra, rb, rc;
	long n = 0;
	long sumc = 0;
	init();
	
	for (a = 1; a < CLARGE/2; a++)
	{
		ra = Rad[a];;
		for (b = a + 1; a + b < CLARGE; b++)
		{
			if (!relprime(a,b)) continue;
			c = a + b;
			if (!relprime(a,c)) continue;
			if (!relprime(b,c)) continue;
			rb = Rad[b];
			if (ra * rb >= c) continue;
			rc = Rad[c];
			if (ra * rb * rc < c)
			{
				n++;
				sumc += c;
				printf("%3ld  (%ld,%ld,%ld) :  csum: %ld\n", n, a, b, c, sumc);
			}
		}

	}
}
