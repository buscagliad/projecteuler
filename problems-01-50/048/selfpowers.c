#ifdef PROBLEM_DESCRIPTION

Self powers


Problem 48

The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

#endif

#include <cstdint>
#include <stdio.h>
#include "bigint.h"

#define TENDIGITS 10000000000l

uint64_t power(uint64_t n)
{
	uint64_t rv = 1;
	uint64_t cn = n;
	while (n > 0) {rv *= cn; n--;rv%=TENDIGITS;}
	printf("N: %lu  N^N: %lu\n", cn, rv);
	return rv;
}

void test(long n)
{
	BigInt sum;
	for (long k = 1; k <= n; k++)
	{
		BigInt Bk(k);
		BigInt p = Bk ^ Bk;
		sum += p;
	}
	printf("%ld ^ %ld = %s\n", n, n, sum.c_str());
}
// 9110846700
int main()
{
	//test(1000);
	//return 1;
	printf("1000^1000 %lu TENDIGITS: %lu\n", power(1000), power(1000)%TENDIGITS);
	uint64_t sum = 0;
	for (uint64_t n = 1; n <= 1000; n++)
	    sum += power(n);
	printf("sum is: %lu    last ten digits: %lu\n",
		sum, sum % TENDIGITS);
}
	
