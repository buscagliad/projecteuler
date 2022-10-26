
/*
There are some prime values, p, for which there exists a positive integer, n, such that the expression n^3 + n^2 p is a perfect cube.

For example, when p = 19, 8^3 + 8^2×19 = 12^3.

What is perhaps most surprising is that for each prime with this property the value of n is unique, and there are only four such primes below one-hundred.

How many primes below one million have this remarkable property?
* 
* 
* For this problem, we will note that if n = a^3, and p + n is a perfect cube, i.e. p + n = x^3,
* then, 
* 	n^3 + n^2 p = n^2 ( n + p ) = a^6 ( x^3 ) = ( a^2 x )^3
* 
* So, step one is to find n (which must be a perfect cube (a^3)) such that when added to p is a 
* perfect cube.  (iscube tests for an integer being a perfect cube, and returns the cube root
* if it is).  To limit the search, we can stop whenenver (n+1)^3 - n^3 > p.
*/
#include <cstdio>
#include <cmath>
#include "prime.h"

bool iscube(long n, long &cr)
{
	double nr = exp(log((double)n)/3.0);
	cr = round(nr);
	if (cr * cr * cr == n) return true;
	return false;
}

int main()
{
	Prime pr;
	bool done = false;
	long lastn;
	int count = 0;
	long n;
	long ncr;
	long p = prime_list[0];
	for (int i = 0; p < 1000000; i++)
	{
		done = false;
		n = 1;
		lastn = 1;
		for (long a = 1; !done ; a++)
		{
			n = a * a * a;
			if (iscube(p + n, ncr))
			{
				done = true;
			    printf("%3.3d:: P: %ld   a: %ld  n: %ld  cubed root: %ld\n", ++count, p, a, n, ncr);
			}
			if (n - lastn > p) done = true;
			lastn = n;
		}
		p = prime_list[i];
	}
		
}
