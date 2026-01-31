
#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"


int main(int argc, char **argv)
{
	long NUM = 100;
	if (argc == 2) NUM = atol(argv[1]);
	long s = sumint(NUM);
	long sq = sumsq(NUM);
	printf("Sum of first %ld integers quantity squared is: %ld\n", NUM, s * s);
	printf("Sum of the squares of the first %ld integers is: %ld\n", NUM, sq);
	printf("The difference is: %ld\n", s * s - sq);
	return 1;
}
