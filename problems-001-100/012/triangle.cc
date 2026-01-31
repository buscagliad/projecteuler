#include <stdio.h>

#include "factor.h"
#include "sequence.h"


int main()
{
	long	n = 5;
	long    nf = 0;
	while (nf <= 500)
	{
		long  tn = sumint(n);
		factor f(tn);
		nf = f.num();
		printf("n: %ld   tn: %ld  nf: %ld\n", n, tn, nf);
		n++;
	}
}
