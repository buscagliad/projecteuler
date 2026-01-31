#ifdef PROBLEM_DESCRIPTION
Square root convergents


  [Show HTML problem content]  
Problem 57

It is possible to show that the square root of two can be expressed as an infinite continued fraction.

By expanding this for the first four iterations, we get:





The next three expansions are
,
, and
, but the eighth expansion,

, is the first example where the number of digits in the numerator exceeds the number of digits in the denominator.

In the first one-thousand expansions, how many fractions contain a numerator with more digits than the denominator?
#endif


#include <stdio.h>
#include <bigint.h>

typedef	BigInt NUM;

void next(NUM &pn, NUM &qn, NUM &num)
{
	NUM spn = pn;
	NUM sqn = qn;
	
	pn = sqn;
	qn = 2 * sqn + spn;
	num = 3 * sqn + spn;
}

#define DO	next(p, q, num); printf("NUM = %s / %s\n", num.c_str(), q.c_str()); if (num_digits(num) > num_digits(q)) counter++;

int num_digits(NUM a)
{
	return a.num_digits();
}

int main()
{
	NUM p(1l);
	NUM q(2l);
	NUM num(1l);
	int counter = 0;
	
	for (int i = 0; i < 1000; i++) {DO; }
	printf("counter = %d\n", counter);
}
