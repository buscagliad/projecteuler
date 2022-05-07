/*

Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.

*/
#include "factor.h"

bool	test_amicable(long	n)
{
	factor f(n);
	vlong_t fd = f.divisors();
	long    an = sum(fd);
	factor g(an);
	vlong_t fg = g.divisors();
	
	if (n == an) return false;

	if (n == sum(fg))
	{
		printf("%ld and %ld are amicable\n", n, an);
		return true;
	}
	return false;

}

int main()
{
	#define MAX 10000
	long am_sum = 0;
	for (long n = 2; n < MAX; n++)
		if (test_amicable(n)) am_sum += n;
	printf("Sum of amicable numbers less than %d is %ld\n", MAX, am_sum);
}
