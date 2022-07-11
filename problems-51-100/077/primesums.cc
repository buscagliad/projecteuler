#ifdef PROBLEM_DESCRIPTION

Prime summations


Problem 77

It is possible to write ten as the sum of primes in exactly five different ways:

7 + 3
5 + 5
5 + 3 + 2
10,3
3 + 3 + 2 + 2
2 + 2 + 2 + 2 + 2

11,3
   3 + 2 + 2 + 2 + 2
   3 + 3 + 3 + 2
   
11,2 == 0

What is the first value which can be written as the sum of primes in over five thousand different ways?

Total: 68  Prime: 67  index: 18
Number of ways to add to 68 is 3936
Total: 69  Prime: 67  index: 18
Number of ways to add to 69 is 4268
Total: 70  Prime: 67  index: 18
Number of ways to add to 70 is 4624
Total: 71  Prime: 71  index: 19
Number of ways to add to 71 is 5007



#endif

#include "prime.h"

//
Prime	P;

long	ways(long total, long max)
{
	long res = 0;
	//printf(">>>Total: %ld   Max: %ld  res: %ld\n", total, max, res);
	if (max == 1) // Prime[1] == 3
	{
		if (total % 2 == 1) total -= 3;
		while (total >= 0)
		{
			res++;
			total = total - 6;
		}
		return res;
	}
	if (max == 0) // Prime[0] == 2
	{
		if (total % 2 == 1) return 0;
		return 1;
	}
	// by defintion
	while (total >= 0)
	{
		res = res + ways(total, max - 1);
		total = total - P.get(max);
	}
	//printf("Total: %ld   Max: %ld  res: %ld\n", total, max, res);
	return res;
}



int main()
{
	long	total = 20;	// desired total
	long    numways = 0;
	while (numways <= 5000)
	{
		total++;
		int ix = P.getIndex(total);
		numways = ways(total, ix);
		printf("Total: %ld  Prime: %ld  index: %d\n", total, P.get(ix), ix);
		printf("Number of ways to add to %ld is %ld\n", total, numways);
	}
}


