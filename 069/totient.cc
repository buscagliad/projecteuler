#ifdef PROBLEM_DESCRIPTION



#endif

#include "factor.h"

int main()
{
	double    ratio = 0;
	for (long i = 2; i <= 1000000; i++)
	{
		if (isPrime(i)) continue;
		factor f(i);
		long   t = f.totient();
		double r = (double) i / (double) t;
		if (r > ratio)
		{
			ratio = r;
			printf("%7ld   %7ld    %6.3f\n", i, f.totient(), r);
		}
	}
}
