#include <cstdio>
#include <cstdlib>

long rep[] = {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111, 1111111111, 
	          11111111111, 111111111111, 1111111111111, 111111111111111};

long getg(long p)
{
	int i = 0;
	while (rep[i] < p) i++;
	return rep[i];
}

int A(long p)
{
	int n = 0;
	long r = 1;
	long g = getg(p);
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
	Prime prime(false);
	int n = 4;
	int h = 0;
	int stop = 1000000;
	int nstop = 1;
	long p = prime_list[n];
	while (prime_list[n] < stop) n++;
	while(true)
	{
		h = A(p);
		if (h > nstop)
		{
			printf("h = %d  repdiv: %ld\n", h, p);
			nstop = h;
		}
		if (h > stop) break;
		n++;
		while (prime_list[n] % 10 == 9) n++;
		p = prime_list[n];
	}
	printf("h = %d  repdiv: %ld\n", h, p);
}
	
