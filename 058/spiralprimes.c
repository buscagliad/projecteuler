#ifdef PROBLEM_DESCRIPTION

Spiral primes


  [Show HTML problem content]  
Problem 58

Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.

37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ≈ 62%.

If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed. If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%?

n = 13120  numprimes = 5248   numdiags = 52481  
Side = 26241  numprimes = 5248   numdiags = 52481  



#endif

#include <cstdio>
#include "prime.h"

int getCorners(long &c1, long &c2, long &c3, long &c4, long &n)
{
	n++;
	c1 = c4 + 2 * n;
	c2 = c1 + 2 * n;
	c3 = c2 + 2 * n;
	c4 = c3 + 2 * n;
	//printf("Corners: %ld %ld %ld %ld   n: %ld  length: %ld\n", 
	//	c1, c2, c3, c4, n, 2*n+1);
	return isPrime(c1) + isPrime(c2) + isPrime(c3) + isPrime(c4);
}

int main()
{
	Prime p(false);
	double numprimes = 3;		// 3, 5, 7
	double numdiags = 5;		// 1 + 3, 5, 7, 9
	long c1 = 3, c2 = 5, c3 = 7, c4 = 9;
	long n = 1;
	while (numprimes / numdiags > 0.1)
	//while (n < 5)
	{
		numprimes += getCorners(c1, c2, c3, c4, n);
		numdiags += 4;
	}
	printf("Side = %ld  numprimes = %.0f   numdiags = %.0f  \n",
		2*n+1, numprimes, numdiags);
}

