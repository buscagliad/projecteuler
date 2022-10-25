#include <cstdio>
#include <cstdlib>


/* 



A number consisting entirely of ones is called a repunit. We shall define R(k) to be a repunit of length k; for example, R(6) = 111111.

Let us consider repunits of the form R(10n).

Although R(10), R(100), or R(1000) are not divisible by 17, R(10000) is divisible by 17. Yet there is no value of n for which R(10n) will divide by 19. In fact, it is remarkable that 11, 17, 41, and 73 are the only four primes below one-hundred that can be a factor of R(10n).

Find the sum of all the primes below one-hundred thousand that will never be a factor of R(10n).


For this problem, we will cycle through each of the primes less than 100,000 noting which will divide R(10n).  To do this, we compute A(p), and if A(p) cannot divide 10n for any n, we will mark this as a non-factor and add it to our running sum.  A number will not divide R(10n) if A(p) is not completely comprised of 2's and/or 5's.  If A(p) has factors other than 2 or 5, R(10n) will never be divisible by p.

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
bool	fact2or5(long p, int h)
{
	// remove all factors of two
	//printf("P: %ld  h: %d", p, h);
	while (h % 2 == 0) 
	{
		h /= 2;
		//printf(" 2");
	}	
	while (h % 5 == 0) 
	{
		h /= 5;
		//printf(" 5");
	}	
	if (h != 1) 
	{
		//printf(" xxx %d\n", h);
		return false;
	}
	//printf("  ^^^ %d\n", h);
	return true;
}

int main()
{
	Prime pr;
	int count = 0;
	long sum = 17;  //2 + 3 + 5 + 7
	int n = 4;  // start will p = 11
	long p = prime_list[n];
	#define MAX_PRIME 100000
	while ( p < MAX_PRIME )
	{
		int h = A(p);
		if (!fact2or5(p, h))
		{
			sum += p;
			count++;
			//printf("A(%ld) = %d  sum: %ld\n", p, h, sum);
		}
		n++;
		p = prime_list[n];
	}
	printf("Sum of all primes < %d that are never divisors "
			"of R(10^n) is: %ld\n", MAX_PRIME, sum);
}
	
