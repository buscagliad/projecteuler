#include <stdlib.h>
#include <stdio.h>
#include "prime.h"

int main(int argc, char **argv)
{
	long	num = 10001;
	long	nthprime = 13;
	long	n = 1;
	if (argc == 2) num = atol(argv[1]);
	for (; n <= num; n++)
	{
		nthprime = next_prime();
		printf("N: %ld   P: %ld\n", n, nthprime);
	}
}
