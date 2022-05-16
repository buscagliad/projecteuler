//long	NchooseM(long n, long m)
#include <stdio.h>

#include "sequence.h"

int main()
{
	long   n;
	long   r;
	long   count = 0;
	
	for (n = 1; n <= 100; n++)
	{
		for (r = 1; r <= n; r++)
		{
			long ncm = NchooseM(n, r);
			if (ncm > 1000000)
			{
				printf("%ld  choose  %ld   =   %ld\n", n, r, ncm);
				count += n - 2 * r + 1;
				r = 101;
			}
		}
	}
	printf("Count is: %ld\n", count);
}
