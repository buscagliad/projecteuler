#include <cstdio>
#include <cstdlib>


// Note:  A(p) <= p, therefore start with p at 1000001, increment by 2
//  skip numbers divisible by 5, find first number that A(p) > 1000000
//
long rep[] = {	        1,           11,           111,           1111,        11111, 
				   111111,      1111111,      11111111,      111111111,   1111111111, 
	          11111111111, 111111111111, 1111111111111, 11111111111111};

long getg(long p, int &n)
{
	int i = 0;
	while (rep[i] < p) i++;
	n = i;
	return rep[i];
}

int A(long p)
{
	int n = 0;
	long r = 1;
	long g = getg(p, n);
	//printf("p: %ld   g: %ld\n", p, g); 
	while (r != 0)
	{
		n++;
		long d = g / p;
		r = g % p;
		//printf("n=%d  g=%ld  d=%ld  r=%ld\n", n, g, d, r);
		g = (g - d * p) * 10 + 1;
		//if (n>28)exit(1);
	}
	//printf("n:%d\n", n);
	return n;
}
#include "prime.h"

int main()
{
	int h = 0;
	int stop = 1000000;
	int nstop = 1;

	long p = 1000001;
	while(true)
	{
		h = A(p);
		printf("A(%ld) = %d\n", p, h);
		if (h > nstop)
		{
			printf("A(%ld) = %d\n", p, h);
			nstop = h;
		}
		if (h > stop) break;
		p+=2;
		while (p % 5 == 0) p+=2;
	}
	printf("A(%ld) = %d\n", p, h);
}
	
