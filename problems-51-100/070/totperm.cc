#ifdef PROBLEM_DESCRIPTION
Totient permutation


  [Show HTML problem content]  
Problem 70

Eulers Totient function, φ(n) [sometimes called the phi function], is used to
determine the number of positive numbers less than or equal to n which are
relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than
nine and relatively prime to nine, φ(9)=6.
   
The number 1 is considered to be relatively prime to every positive number, so φ(1)=1.

Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation of 79180.

Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation of n and the ratio n/φ(n) produces a minimum.


#endif

#include <cmath>
#include <cstdio>
#include "prime.h"
#include "base10.h"

bool test(long p1, long p2, long &phi, long maxV)
{
	long prod = p1 * p2;
	if (prod > maxV) return false;
	phi = (p1 - 1) * (p2 - 1);
	base10 prod10(prod);
	return prod10.sameDigits(phi);
}

long boundPrime(long n)
{
	double x = n;
	long   mid = sqrt(x);	// we'll look for the nearest prime on either side
							// of mid
	Prime	p(mid);
	int		mid_index = prime_next_index;
	
	printf("n = %ld   mid: %d\n", n, mid_index);

	if (isPrime(p.value()))
	{
		printf("p2 = %ld is a prime\n", p.value());
	}
	int i1, i2;
	long phi = 0;
	for (i1 = mid_index; ; i1--)
	{
		for (i2 = mid_index+1; ; i2++)
		{
			long p = prime_list[i1] * prime_list[i2];
			if (p > n) break;
			if (test(prime_list[i1], prime_list[i2], phi, n))
			{
				printf("i1: %d   P1: %ld   i2: %d   P2: %ld   phi: %ld   p: %ld\n",
					i1, prime_list[i1], i2, prime_list[i2], phi, p);
				return 1;
			}
		}
	}
	return 1;
}

int main()
{
	boundPrime(10000000);
}
	

