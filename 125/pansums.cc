/*

The palindromic number 595 is interesting because it can be written as the sum of 
consecutive squares: 6^2 + 7^2 + 8^2 + 9^2 + 10^2 + 11^2 + 12^2.

There are exactly eleven palindromes below one-thousand that can be written as 
consecutive square sums, and the sum of these palindromes is 4164. Note that 
1 = 0^2 + 1^2 has not been included as this problem is concerned with the squares 
of positive integers.

Find the sum of all the numbers less than 10^8 that are both palindromic and can be 
written as the sum of consecutive squares.
*/

#include <vector>
#include "base10.h"
#include "vlong.h"


#define MAXP 100000000

vlong	array;

void getp(long n)
{
	long sumsq = n * n;
	n++;
	sumsq += n * n;
	while (sumsq < MAXP)
	{
		base10	b(sumsq);
		if (b.isPalindrome())
		{
			array.add(sumsq);
			//printf("Found  %ld\n", sumsq);
		}
		n++;
		sumsq += n * n;
	}
}

int main()
{
	for (long n = 1; n * n < MAXP; n++)
	    getp(n);
	array.out();
	long sum = array[0];
	long laste = array[0];
	for (size_t i = 1; i < array.size(); i++)
	{
		long thise = array[i];
		if (thise == laste) continue;
		laste = thise;
		sum += thise;
	}
	printf("Sum is %ld\n", sum);
}
	
