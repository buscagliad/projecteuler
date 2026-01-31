/*

Consider the consecutive primes p1 = 19 and p2 = 23. It can be verified that 1219 is the smallest number such that the last digits are formed by p1 whilst also being divisible by p2.

In fact, with the exception of p1 = 3 and p2 = 5, for every pair of consecutive primes, p2 > p1, there exist values of n for which the last digits are formed by p1 and n is divisible by p2. Let S be the smallest of these values of n.

Find ∑ S for every pair of consecutive primes with 5 ≤ p1 ≤ 1000000.


To determine S, we search for the first n such that 10^k * n + p1 = 0 mod p2.   k = min(n):: 10^n > p1

to speed the search, we note that n must be a multiple of p2 - p1


*/

#include "prime.h"

long tens[]={1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};

long getk(long p)
{
	for (int i = 0; i < 8; i++) if (tens[i] > p) return tens[i];
	return 0;
}

long getfact(long p1, long p2, long &v)
{
	long pf = p2 - p1;
	long t = getk(p1);
	for (long n = 1; n < p2; n++)
	{
		v = t * n * pf + p1;
		if (v % p2 == 0) return n * pf;
	}
	return -1;
}


long getfact2(long p1, long p2, long &v)
{
	long pf = 1;
	long t = getk(p1);
	for (long n = 1; n < p2; n++)
	{
		v = t * n * pf + p1;
		if (v % p2 == 0) return n * pf;
	}
	return -1;
}

long getfact3(long p1, long p2, long &v)
{
	long t = getk(p1);
	long m = (p2 - p1) % t;
	v = t * m + p1;
	printf("p1: %ld  p2: %ld   m: %ld   v: %ld\n",
			p1, p2, m, v);
	if (v % p2 == 0) return m;

	return -1;
}


long SUM = 0;

 void test1(long p1, long p2, bool plog = true)
{
	long v;
	long S = getfact(p1, p2, v);
	if (S > 0)
	{
	    if(plog) printf("p1: %ld  p2: %ld   v: %ld   S: %ld\n",
			p1, p2, v, S);
		SUM += v;
	}
	else
	{
		printf("p1: %ld  p2: %ld   ERROR\n",
			p1, p2);
		exit(1);
	}
}

void test2(long p1, long p2, bool plog = true)
{
	long v;
	long S = getfact2(p1, p2, v);
	if (S > 0)
	{
	    if(plog) printf("p1: %ld  p2: %ld   v: %ld   m: %ld\n",
			p1, p2, v, S);
		SUM += v;
	}
	else
	{
		printf("p1: %ld  p2: %ld   ERROR\n",
			p1, p2);
		exit(1);
	}
}

void test3(long p1, long p2, bool plog = true)
{
	long v;
	long S = getfact3(p1, p2, v);
	if (S > 0)
	{
	    if(plog) printf("p1: %ld  p2: %ld   v: %ld   m: %ld\n",
			p1, p2, v, S);
		SUM += v;
	}
	else
	{
		printf("p1: %ld  p2: %ld   ERROR\n",
			p1, p2);
		//exit(1);
	}
}

void test(long p1, long p2)
{
	//test1(p1, p2);
	test2(p1, p2);
	//test3(p1, p2);
}

int main()
{
	Prime pr;

	
	for (int i = 2; prime_list[i] < 1000000; i++)
	{
		test(prime_list[i], prime_list[i+1]);
	}
	printf("Sum is %ld\n", SUM);
}
