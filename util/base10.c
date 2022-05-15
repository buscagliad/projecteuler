#include <stdio.h>
#include "base10.h"

void	test(base10 &a, base10 &b)
{
	printf("a = %ld   b = %ld   same digits = %s\n", a.value(), b.value(), (a.sameDigits(b) ? "YES" : "NO"));
}


#define DEBUG 1

//bool	multest(base10 &a)
bool	multest(long av)
{
	base10  a(av);
	base10	m2(2*a.value());
	if (!a.sameDigits(m2)) return false;
	if (DEBUG) printf("a = %ld   m2 = %ld \n", a.value(), m2.value());
	base10	m3(3*a.value());
	if (!a.sameDigits(m3)) return false;
	if (DEBUG) printf("a = %ld   m3 = %ld \n", a.value(), m3.value());
	base10	m4(4*a.value());
	if (!a.sameDigits(m4)) return false;
	if (DEBUG) printf("a = %ld   m4 = %ld \n", a.value(), m4.value());
	base10	m5(5*a.value());
	if (!a.sameDigits(m5)) return false;
	if (DEBUG) printf("a = %ld   m5 = %ld \n", a.value(), m5.value());
	base10	m6(6*a.value());
	if (!a.sameDigits(m6)) return false;
	if (DEBUG) printf("a = %ld   m6 = %ld \n", a.value(), m6.value());
	return true;
}

int main()
{
	long	d;
	long    m;
	long    mult;
	for (d = 10; d <= 16; d++)
	{
		for (m = 100; m < 100000; m++)
		{
			if (m < 1000) mult = 1000;
			else if (m < 10000) mult = 10000;
			else if (m < 100000) mult = 100000;
			long n = d * mult + m;
			if (multest(n))
			{
				printf("Number found: %ld\n", n);
				exit(1);
			}
		}
	}
}
