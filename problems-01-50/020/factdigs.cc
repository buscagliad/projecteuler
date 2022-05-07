#include <stdio.h>
#include "bigint.h"

int main()
{
	BigInt	n(1000);
	BigInt	nfact = !n;
	printf ("Number of digits is;: %d\n", nfact.num_digits());
	long sum = 0;
	for (int i = 0; i < nfact.num_digits(); i++)
	    sum += nfact.get_digit(i);
	printf("Sum of digits is: %ld\n", sum);
}
