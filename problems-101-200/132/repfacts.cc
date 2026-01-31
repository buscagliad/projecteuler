#include <cstdio>
#include <cstdlib>


/* 

A number consisting entirely of ones is called a repunit. We shall define R(k) to be a repunit of length k.

For example, R(10) = 1111111111 = 11×41×271×9091, and the sum of these prime factors is 9414.

Find the sum of the first forty prime factors of R(10^9).

For this problem, we will cycle through each of the primes until we find 40 that are divide R(10^9).  To do this, we compute A(p), and if A(p) divides 10^9, the p is a 
prime factor of R(10^9)

*/
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
	int n = 4;
	Prime pr;
	int count = 0;
	int sum = 0;

	for (; count < 40; n++)
	{
		long p = prime_list[n];
		int h = A(p);
		if ((1000000000%h)==0)
		{
			sum += p;
			count++;
			printf("A(%ld) = %d  sum: %d\n", p, h, sum);
		}
	}
}
	
