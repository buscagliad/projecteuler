#ifdef PROBLEM_DESCRIPTION


A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?

#endif

#include <iostream>
#include <stdio.h>

#include "bigint.h"

using namespace std;

// return the sum of the digits of a ^ b
long pdigsum(long a, long b)
{
	BigInt	A(a);
	BigInt	p = A ^ b;
	//cout << " a ^ b = " << p << "  num digits "<< p.num_digits() << endl;
	
	long digsum = 0;
	for (int i = 0; i < p.num_digits(); i++)
	    digsum += p.get_digit(i);
	return digsum;
}

int main()
{
	long ma, mb, mpds = 0;
	for (long a = 1; a < 100; a++)
	    for (long b = 1; b < 100; b++)
	    {
			long pds = pdigsum(a, b);
			if (pds > mpds)
			{
				ma = a;
				mb = b;
				mpds = pds;
			}
		}
	printf("a = %ld   b = %ld   digsum = %ld\n", ma, mb, pdigsum(ma, mb));
}
