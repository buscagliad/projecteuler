/*
 * Non-abundant sums  Problem 23

A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#include "factor.h"

#define MAX_NON_ABUNDANT  28123
#define SAMALLEST_ABUNDANT 12

long getan(vlong &abnums)
{
	bool done = false;
	long start = SAMALLEST_ABUNDANT; // get next number
	while (!done)
	{
		auto fs = factor(start).divisors(true);
		long sumd = sum(fs);
		if (sumd > start) abnums.add(start);
		start++;
		if (start >= MAX_NON_ABUNDANT) done = true;
	}
	return abnums.size();
}

bool can_equal(vlong &v, long value)
{
	//size_t maxi = 0;
	//for (size_t i = 0; v[i] <= value; i++)
	vlong_it maxi = v.index_it(value);
	if (maxi == v.end()) return true;
	if (value < *(v.begin())) return false;
	printf("Maxi: %ld  value: %ld\n", *maxi, value);
	//if (*maxi > value) return true;
	for (vlong_it i = v.begin(); i != maxi; i++)
	{
		printf("i: %ld   max: %ld\n", *i, *maxi);
		for (vlong_it j = i; j != maxi; j++)
		{
			long sv = *i + *j;
			if (sv > value) break;
			if (value == sv) {
				//printf("%ld = %ld + %ld\n", value, v[i], v[j]);
				return true;
			}
		}
	}
	return false;
}

void test_index(vlong &vv)
{
	for (long n = 1; n < MAX_NON_ABUNDANT+44444; n+= 31)
	{
		vlong_it  vi = vv.index_it(n);
		if (vi == vv.end())
			printf("N: %ld  vi: END\n", n);
		else
		    printf("N: %ld  vi: %ld\n", n, *vi);
	}
}

int main()
{
	vlong abnums;
	getan(abnums);
	abnums.out();
	int index = 1;
	long nonsum = 0;
	test_index(abnums); return 1;
	for (long i = 1; i < MAX_NON_ABUNDANT; i++)
	{
		if (!can_equal(abnums, i))
		{
			printf("%d %ld\n", index++, i);
			nonsum += i;
		}
	}
	printf("Sum of numbers not able to be the sum of two abundant numbers is: %ld\n", nonsum);
}
