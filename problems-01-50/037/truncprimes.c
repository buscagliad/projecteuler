#ifdef PROBLEM_DESCRIPTION

Truncatable primes

Problem 37

The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

#endif

#include "utils.h"

long lastdigit(long p)
{
	long t = 1;
	long n;
	for (n = 0; p > 9; p /= 10, n++, t *= 10);
	return p * t;
}

bool truncright(long p)
{
	if (p == 0) return true;
	if (!isPrime(p)) return false;
	return truncright(p/10);
}

bool truncleft(long p)
{
	if (p == 0) return true;
	if (!isPrime(p)) return false;
	return truncleft(p - lastdigit(p));
}

bool test(long p)
{
	if (truncright(p) && truncleft(p)){
		return true;
	}
	return false;
}

#define MAX_PRIME 1000000l

int main()
{
	int n = 4;
	long sum = 0;
	int count = 0;
	while (prime_list[n] < MAX_PRIME)
	{
		if (test(prime_list[n]))
		{
		    sum += prime_list[n];
		    count ++;
		    printf("%ld is a truncatable prime\n", prime_list[n]);
		}
		n++;
	}
	printf("There are %d truncatable primes less than %ld \n", count, MAX_PRIME);
	printf("The sum of all truncatable primes less than %ld is %ld\n", MAX_PRIME, sum);}
