/*
 * 

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: As 1! = 1 and 2! = 2 are not sums they are not included.
*/
#include <stdio.h>
long fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};


bool fact_test(long on)
{
	long sum = 0;
	long n = on;
	while ( n > 0 )
	{
		sum += fact[n%10];
		//printf("dig = %ld  sum = %ld\n", n%10, sum);
		n /= 10;
	};
	return sum == on;
}

int main()
{
	long sum = 0;
	for (long k = 10; k < 10*fact[9]; k++)
	{
		if (fact_test(k)) {
			printf("Success for %ld!\n", k);
			sum += k;
		}
	}
	printf("Sum of numbers is %ld\n", sum);
	return 1;
}
