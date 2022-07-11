#ifdef PROBLEM_DESCRIPTION

Counting fractions in a range


Problem 73

Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that 2/5 is the fraction immediately to the left of 3/7.

By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending order of size, find the numerator of the fraction immediately to the left of 3/7.



Answer:  428570
Completed on Thu, 26 May 2022, 15:32

NOTE:  I somehow lost the code to this problem - and I'm not oging to regenerate - however, problem
73 is very similar - so i've copied its c file here and renamed it.

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

	
	
