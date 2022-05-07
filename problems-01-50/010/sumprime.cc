#include <stdlib.h>
#include <stdio.h>
#include "prime.h"

int main(int argc, char **argv)
{
	long	num = 2000000;
	long	prime = 13;
	long	sum = 2 + 3 + 5 + 7 + 11 + 13;
	bool	done = false;
	if (argc == 2) num = atol(argv[1]);
	while (!done)
	{
		prime = next_prime(prime+2);
		if (prime < num)
		{
			sum += prime;
			printf("P: %ld   S: %ld\n", prime, sum);
		}
		else done = true;
	}
}
