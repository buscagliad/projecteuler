// what is the largest prime divisor 
// of the given number??

// function check whether a number
// is prime or not
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "prime.h"
#include "factor.h"

int main(int argc, char **argv)
{
	vlong_t fac;
	long fn = 46134626;
	if (argc == 2) fn = atol(argv[1]);
	factor cfn(fn);
	if (argc == 2) fn = atol(argv[1]);
	prime_factor(fn, fac);
	print_factors(fac);
	cfn.out();
	return 1;
}
