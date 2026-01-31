#ifdef PROBLEM_DESCRIPTION

Prime permutations

Problem 49

The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?

#endif

#include <stdio.h>
#include "prime.h"
#include "digit.h"

int
ps_search(int index, long &p1, long &p2, long &p3)
{
	while (prime_list[index] < 1000) index++;
	p1 = 0;
	p2 = 0;
	p3 = 0;
	
	for (int i1 = index; prime_list[i1] < 10000; i1++)
	{
		for (int i2 = i1 + 1; prime_list[i2] < 10000; i2++)
		{
			if (!isPermutation(prime_list[i1], prime_list[i2])) continue;
			//printf("PERM: %ld and %ld\n", prime_list[i1], prime_list[i2]);
			long delta = prime_list[i2] -  prime_list[i1];
			for (int i3 = i2 + 1; prime_list[i3] - prime_list[i2] <= delta; i3++)
			{
				if (!isPermutation(prime_list[i2], prime_list[i3])) continue;
				if (prime_list[i3] - prime_list[i2] == delta)
				{
					p1 = prime_list[i1]; 
					p2 = prime_list[i2]; 
					p3 = prime_list[i3];
					return i1;
				}
			}
		}
	}
	return -1;
} 

int	main()
{
	Prime p;
	long p1, p2, p3;
	int index = 1;
	p1 = 1234;
	p2 = 4321;
	printf("%ld and %ld are permutations: %d\n", p1, p2, isPermutation(p1, p2));
	p1 = 126634;
	p2 = 432166;
	printf("%ld and %ld are permutations: %d\n", p1, p2, isPermutation(p1, p2));
	p1 = 12634;
	p2 = 432166;
	printf("%ld and %ld are permutations: %d\n", p1, p2, isPermutation(p1, p2));
	index = ps_search(index, p1, p2, p3);
	printf("P1: %ld  P2: %ld  P3: %ld  \n", p1, p2, p3);
	index = ps_search(index +1, p1, p2, p3);
	printf("P1: %ld  P2: %ld  P3: %ld  \n", p1, p2, p3);
}
