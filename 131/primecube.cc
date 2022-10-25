
#include <cstdio>
#include <cmath>
#include "prime.h"

bool iscube(long n, long &cr)
{
	double nr = exp(log((double)n)/3.0);
	cr = round(nr);
	if (cr * cr * cr == n) return true;
	return false;
}

int main()
{
	Prime pr;
	bool done = false;
	long lastn;
	int count = 0;
	long n;
	long ncr;
	long p = prime_list[0];
	for (int i = 0; p < 1000000; i++)
	{
		done = false;
		n = 1;
		lastn = 1;
		for (long a = 1; !done ; a++)
		{
			n = a * a * a;
			if (iscube(p + n, ncr))
			{
				done = true;
			    printf("%3.3d:: P: %ld   a: %ld  n: %ld  cubed root: %ld\n", ++count, p, a, n, ncr);
			}
			if (n - lastn > p) done = true;
			lastn = n;
		}
		p = prime_list[i];
	}
		
}
