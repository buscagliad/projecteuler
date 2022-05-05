#ifdef PROBLEM_DESCRIPTION

Goldbachs other conjecture


Problem 46

It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×1^2
15 = 7 + 2×2^2
21 = 3 + 2×3^2
25 = 7 + 2×3^2
27 = 19 + 2×2^2
33 = 31 + 2×1^2

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?

#endif

#include <stdio.h>
#include "prime.h"
#include "digit.h"

bool goldbach(long n)
{
	for (int i = 0; i < prime_list_size && prime_list[i] < n; i++)
	{
		long k = (n - prime_list[i])/2;
		if (isSquare(k))
		{
			long q = sqrt(double(k))+0.1;
			printf("%ld = %ld + 2 x %ld ^ 2 = %ld\n", n, prime_list[i], q, 
				prime_list[i] + 2 * q * q );
			return true;
		}
	}
	return false;
}

int main()
{
	long k;
	for (k = 33; ; k+=2)
	{
		if (isPrime(k)) continue;
		if (!goldbach(k))
		{
			printf("Goldback failed at k = %ld\n", k);
			return 1;
		}
	}
}
