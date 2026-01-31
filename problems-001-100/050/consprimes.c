#ifdef PROBLEM_DESCRIPTION

Consecutive prime sum

Problem 50

The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13

This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?

#endif

#include <stdio.h>
#include "prime.h"
#include "digit.h"

int
longestPossible(long maxSum)
{
	int	i = 0;
	long csum = 0;

	while (csum < maxSum)
	{
		csum += prime_list[i++];
	}
	return i - 1;
}

int
prime_sum(int wsize, long &sum, long maxSum)
{
	long lsum = 0;
	long rsum = 0;
	int start = 0;
	int rstart = -1;
	bool done = false;
	while (!done)
	{
		lsum = 0;
		for (int i = start; i < wsize + start ; i++)
			lsum += prime_list[i];
		if (lsum < maxSum)
		{
			if (isPrime(lsum))
			{
				if (lsum > rsum)
				{
					rsum = lsum;
					rstart = start;
					done = true;
				}
			}
		}
		else
			done = true;
		start++;
	}
	sum = rsum;
	return  rstart;
}
	
bool
search(long MaxPrimeSum)
{
	long wsum = 0;

	for (int  consecPrimes = longestPossible(MaxPrimeSum); ; consecPrimes--)
	{
		int cnt = prime_sum(consecPrimes, wsum, MaxPrimeSum);
		if ( cnt >= 0 )
		{
			printf("Largest consecutive prime sum less than %ld is 	%ld\n"
					"with %d consecutive primes starting at %ld (%d)\n",
					MaxPrimeSum, wsum, consecPrimes, prime_list[cnt], cnt);
			return true;
		}
	}
	return false;
}
	
int main()
{
	Prime p;	// reads in file
	search(100);
	search(1000);
	search(1000000);
}
