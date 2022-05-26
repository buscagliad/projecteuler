#ifdef PROBLEM_DESCRIPTION

Prime pair sets
Problem 60

The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.

Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.


#endif


#include "prime.h"
#include <cstdio>
#define MAX_PRIME 100000

long pwr10(long a)
{
	long rv = 1;
	while (a > 0)
	{
		rv *= 10;
		a /= 10;
	}
	return rv;
} 

long marry(long a, long b) // returns a * 10^[loga] + b
{
	long m = a * pwr10(b) + b;
	//printf("a = %ld   b = %ld   m = %ld\n", a, b, m);
	return m;
}

bool	check(long a, long b)
{
	long v = marry(a, b);
	long u = marry(b, a);
	return isPrime(u) && isPrime(v);
}

long prime_check(Prime p[], int n)
{
	long sum = 0;
	for (int i = 0; i < n; i++) { if (!isPrime(p[i].value())) return 0; else sum += p[i].value(); }
	for (int i = 0; i < n - 1; i++)
	    for (int j = i+1; j < n; j++)
	        if (!check(p[i].value(), p[j].value())) return 0;
	//printf("%d Prime pairs: ", n);
	//for (int i = 0; i < n; i++) printf("  %ld", p[i].value());
	//printf("\n");
	return sum;
}



long prime2(long a, long b)
{
	if (isPrime(a) && isPrime(b) )
	{
		//printf("Two prime pairs:  %ld, %ld\n", a, b);
		if (check(a, b) )
		{
			//printf("SUCCESS!!  Two prime pairs:  %ld, %ld\n", a, b);
		    return a + b;
		}
	}
	return 0;
}

bool pfind3(Prime *p, int n, int maxIndex)
{
	p[n].next();
	if (p[n].value() > MAX_PRIME) return false;
	if (prime_check(p, n+1))
	{
		//printf("n+1: %d  max: %d\n", n+1, maxIndex);
		if(n+1 == maxIndex) return true;
		p[n+1]=p[n];
		n++;
		return pfind3(p, n, maxIndex);
	}
	return pfind3(p, n, maxIndex);
}

bool pfind2(Prime &a, Prime &b)
{
	if (a.value() == 5) a.next();
	if (prime2 (a.value(), b.value())) 
	{
		return true;
	}
	else
	{
		if (b.value() > MAX_PRIME)
		{
			a.next();
			b = a;
			b.next();
			return pfind2(a, b);
		}
		else
		{
			b.next();
			return pfind2(a, b);
		}
	}
}

int main()
{
	//long p[] = {3, 7, 109, 673};
	//prime_check(p, 4);
	//return 1;
	Prime abc(true);
	Prime p[5];
	p[0].setIndex(1); // 3
	p[1].setIndex(3); // 7
	int maxIndex = 5;
	for (int i = 0; i < 100000; i++) 
	{ 
		pfind2(p[0], p[1]);
		p[2]=p[1];
		if(pfind3(p, 2, maxIndex)) break;
		p[1].next(); if (p[1].value()==5)p[1].next();
		if (p[1].value() > 10000)
		{
			p[0].next(); if (p[0].value() == 5) p[0].next();
			p[1] = p[0];
			p[1].next();
		}
	}
	printf("*** %d Prime pairs: ", maxIndex);
	long sum = 0;
	for (int i = 0; i < maxIndex; i++) { sum += p[i].value(); printf("  %ld", p[i].value()); }
	printf("\n");
	printf("Sum is %ld\n", sum);
	return 1;
}

		           
