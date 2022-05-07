#ifdef PROBLEM_DESCRIPTION

Distinct primes factors


Problem 47

The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?

#endif

#include "utils.h"

bool consec4(long n)
{
	printf("Consec4 : n : %ld\n", n);
	factor n1(n);
	factor n2(n+1);
	factor n3(n+2);
	factor n4(n+3);
	if ( (n1.numDistinctPrimes() == 4) && 
	     (n2.numDistinctPrimes() == 4) && 
	     (n3.numDistinctPrimes() == 4) && 
	     (n4.numDistinctPrimes() == 4) ) 
	{
		return true;
	}
	return false;
}

int main()
{
	long n = 647;
	bool done = false;
	while(!done)
	{
		factor f(n);
		bool found = false;
		while (!found) {factor f(++n); if (f.numDistinctPrimes() >= 4) found = true;} 
		if (consec4(n)) { printf("FOUND: %ld\n", n); done = true; }
		n++;
	}
}
		
	
