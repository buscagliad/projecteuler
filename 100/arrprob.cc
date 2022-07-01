#ifdef PROBLEM_DESCRIPTION

Arranged probability


  [Show HTML problem content]  
Problem 100

If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red discs, and two discs were taken at random, it can be seen that the probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.

The next such arrangement, for which there is exactly 50% chance of taking two blue discs at random, is a box containing eighty-five blue discs and thirty-five red discs.

By finding the first arrangement to contain over 10^12 = 1,000,000,000,000 discs in total, determine the number of blue discs that the box would contain.

problem 57 has the repeated fraction for root(2)


: 707119501226.000000  n: 1000017988852.000000  diff: 201013723136.000000
b: 707119501227.000000  n: 1000017988853.000000  diff: 1029455740928.000000
b: 707119501228.000000  n: 1000017988855.000000  diff: 142138212352.000000
b: 707119501229.000000  n: 1000017988856.000000  diff: 686303805440.000000
b: 707119501230.000000  n: 1000017988857.000000  diff: 1514745823232.000000
b: 707119501231.000000  n: 1000017988859.000000  diff: 343151869952.000000
b: 707119501232.000000  n: 1000017988860.000000  diff: 1171593953280.000000
b: 707119501233.000000  n: 1000017988862.000000  diff: 0.000000
Probability of 1/2 for pulling 2 blue discs::  Blue discs: 707119501233   Total discs: 1000017988862



#endif

#include <cstdio>
#include <cmath>
#include "fract.h"



bool validprob(long b, long n)
{
	fract f1(b, n);
	fract f2(b-1, n-1);
	fract p = f1 * f2;
	
	f1.out();
	f2.out();
	p.out();
	printf("\n");
	return p == fract(1, 2);
}

void	test(long b, long n)
{
	if (validprob(b,n))
	    printf("Probability of 1/2 for pulling 2 blue discs::  Blue discs: %ld   Total discs: %ld\n", b, n);
	else 
	    printf("FAIL: Blue discs: %ld   Total discs: %ld\n", b, n);
}

void test2()
{
	long b = 707106678118;
	double sqrt2 = 1.41421356237309504880168872420969807856967187537694807317667973799;
	long n = (double)b * sqrt2;
	while (!validprob(b, n))
	{
		b++;
		n = (double)b * sqrt2;
	}
}

void test3()
{
	//long double bd = 707106678118;
	long double sqrt2 = 1.41421356237309504880168872420969807856967187537694807317667973799;
	long double nd = 1000000000000;
	long double bd = truncl(nd / sqrt2);
	bool done = false;
	while (!done)
	{
		long double left = 2 * bd * (bd - 1);
		long double right = nd * (nd - 1);
		printf("b: %Lf  n: %Lf  diff: %Lf\n", bd, nd, fabs(left-right));
		if (fabsl(left-right) < 0.5)
		{
			long b = roundl(bd);
			long n = roundl(nd);
			printf("Probability of 1/2 for pulling 2 blue discs::  Blue discs: %ld   Total discs: %ld\n", b, n);
			return;
		}
		nd += 1.0;
		bd = roundl(nd / sqrt2);
	}
}

int main()
{
	test(15, 21);
	test(85, 120);
	test(421, 621);
	test3();
	return 1;
	test2();
}
