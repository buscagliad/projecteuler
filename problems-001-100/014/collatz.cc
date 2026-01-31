
#include <stdio.h>

long collatz(long n, long &chain)
{
	//printf("%ld --> ", n);
	if (n == 1) return chain;
	chain++;
	if (n % 2 == 0) return collatz(n/2, chain);
	return collatz(3 * n + 1, chain);
}

long do_collatz(long n)
{
	long chain = 1;
	return collatz(n, chain);
}
	

int main()
{
	#define MAXN 1000000
	long n;
	long mc = 0;
	long mn = 0;
	for (n = 2; n < MAXN; n++)
	{
		long dc = do_collatz(n);
		if (dc > mc)
		{
			mc = dc;
			mn = n;
		}
	}
	printf("Max collatz chain for numbers < %d   occurs for n = %ld  and has a %ld long chain\n", MAXN, mn, mc);
}
