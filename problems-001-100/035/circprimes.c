#ifdef PROBLEM_DESCRIPTION

The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?

#endif

#include "utils.h"


void rotDigits(int *d, int n)
{
	int save = d[0];
	for (int i = 0; i < n-1; i++)
		d[i] = d[i+1];
	
	d[n-1] = save;
}
	

bool isDigitsPrime(int *d, int n)
{
	long p = 0;
	//printf("Digits: ");
	//for (int k = 0; k < n; k++) printf("%d ", d[k]);
	for (int i = 0; i < n; i++)
	{
		p = 10 * p + d[n-i-1];
		//printf("p = %ld   i = %d\n", p, i);
	}
	bool pp = isPrime(p);
	//printf("Is %ld a prime?  %s\n", p, YN(pp));
	return pp;
}

bool isCircular(long p)
{
	int	digits[9];
	int dig;
	int n = 0;
	if (p < 0) return false;
	while ( (p > 0) ) {
		 dig = p%10;
		 if ( (p > 5) && ( (dig == 5) || (dig%2 == 0) ) ) return false;	// no fives or even's
		 digits[n++] = dig;
		 p /= 10;
	}
	
	for (int i = 0; i < n; i++)
	{
		if (!isDigitsPrime(digits, n)) return false;
		rotDigits(digits, n);
	}
	return true;
}

bool test(long p)
{
	return (isCircular(p));
}

#define MAX_PRIME 1000000l
int main()
{
	int n = 0;
	long sum = 0;
	int count = 0;
	while (prime_list[n] < MAX_PRIME)
	{
		if (test(prime_list[n]))
		{
		    sum += prime_list[n];
		    count ++;
		    printf("%ld is a circular prime\n", prime_list[n]);
		}
		n++;
	}
	printf("There are %d circular primes less than %ld \n", count, MAX_PRIME);
	printf("The sum of all circular primes less than %ld is %ld\n", MAX_PRIME, sum);
}
