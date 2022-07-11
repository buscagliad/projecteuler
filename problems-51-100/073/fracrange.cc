#ifdef PROBLEM_DESCRIPTION

Counting fractions in a range


Problem 73

Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that there are 3 fractions between 1/3 and 1/2.

How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper fractions for d ≤ 12,000?
#endif

#include <stdio.h>
#include "digit.h"

int	countfracs(int b)
{
	int sum = 0;
	int a = 1;
	do
	{
		if ( (2 * a < b) && (b < 3 * a) )
		{
			if (gcd(a, b) == 1)
				sum ++;
			
		}
		a++;
	}
	while (b > 2 * a);
	return sum;
}

int main()
{
	int	MAX = 12000;
	int count = 0;
	for (int b = 2; b <= MAX; b++)
	{
		int cf = countfracs(b);
		count += cf;
	}
	printf("count is %d\n", count);
}

	
	
