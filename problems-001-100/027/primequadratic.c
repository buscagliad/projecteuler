
#include "prime.h"
#include "sequence.h"
#include "factor.h"


int	find_primes(int a, int b, vlong &vu, vlong &vl)
{
	bool done = false;
	vu.clear();
	vl.clear();
	for (int n = 0; !done; n++)
	{
		long p = (n + a)*n + b;
		if (isPrime(p)) {// printf("  a:%3d  b:%3d   adding: %ld\n", a, b, p); 
			if (!vl.exists(p)) vl.add(p);
			vu.add(p); }
		else done = true;
	}
	return vu.size();
}

int main()
{
	Prime p;
	vlong vu, vl;
	vlong maxLength;
	int   maxLa = 0, maxLb = 0;
	vlong maxPrimes;
	int   maxPa, maxPb;

	for (int i = 0; i < prime_list_size  &&  prime_list[i] < 1000; i++)
	{
		int b = prime_list[i];
		for (int a = -b; a < 1000; a++)
		{
			find_primes(a, b, vu, vl);
			if (vu.size() > maxLength.size())
			{
				maxLength = vu;
				maxLa = a;
				maxLb = b;
				//printf("a = %d  b = %d\n", a, b);
				//v.out();
			}
			if (vu.size() > maxPrimes.size())
			{
				maxPrimes = vu;
				maxPa = a;
				maxPb = b;
				//printf("a = %d  b = %d\n", a, b);
				//v.out();
			}
		}
	}
	printf("Maximum number of (uniqued) primes is: %ld\n", maxLength.size());
	printf("      a = %d   b = %d    a*b = %d\n", maxLa, maxLb, maxLa * maxLb);
	printf("Maximum number of primes is: %ld\n", maxPrimes.size());
	printf("      a = %d   b = %d    a*b = %d\n", maxPa, maxPb, maxPa * maxPb);
	return 1;
}

