/*

Given the positive integers, x, y, and z, are consecutive terms of an arithmetic progression, the least value of the positive integer, n, for which the equation, x^2 − y^2 − z^2 = n, has exactly two solutions is n = 27:

34^2 − 27^2 − 20^2 = 12^2 − 9^2 − 6^2 = 27

It turns out that n = 1155 is the least value which has exactly ten solutions.

How many values of n less than one million have exactly ten distinct solutions?

*/

#include "factor.h"
#include "vlong.h"

#define DEBUG 0

bool samediff(int x, int y, int z, int n)
{
	if (x*x - y*y - z*z == n) return true;
	return false;
}

bool testab(int a, int b, int n)
{
	return samediff(3*a + b, a + b, 2*a + b, n);
}

bool getab(int plus, int minus, int &a, int &b)
{
	int ppm = plus + minus;
	int pmm = plus - minus;
	if (ppm % 4 != 0) return false;
	a = (ppm) / 4;
	if (pmm % 2 != 0) return false;
	b = (pmm) / 2;
	if ( (2 * a + b > 0) && ( a + b > 0) )return true;
	return false;
}

int getsolutions(int n, int max)
{
	factor f(n);
	vlong_t d = f.divisors(false);
	
	int a;
	int b;
	int k = 0;
	
	for (size_t i = 0; i < d.size(); i++)
	{
		int plus = d[i];
		int minus = n / plus;
		//printf("plus: %d   minus: %d\n", plus, minus);
		if (getab(plus, minus, a, b))
		{
			k++;
			if (DEBUG)
			{
				printf("%2d:: a: %d  b: %d    x: %d  y: %d  z: %d", k, a, b, 3 * a + b, 2 * a + b, a + b);
				if (testab(a, b, n)) printf(" ***\n");
				else printf(" XXX\n");
			}
		}
		minus = -minus;
		plus = -plus;
		//printf("plus: %d   minus: %d\n", plus, minus);
		if (getab(minus, plus, a, b))
		{
			k++;
			if (DEBUG)
			{
				printf("%2d:: a: %d  b: %d    x: %d  y: %d  z: %d", k, a, b, 3 * a + b, 2 * a + b, a + b);
				if (testab(a, b, n)) printf(" ***\n");
				else printf(" XXX\n");
			}
		}
		if (k > max) break;
	}
	return k;
}

void test()
{
	int count = 0;
	for (int n = 1155; n < 1000000; n++)
	{
		if (getsolutions(n, 10) == 10) 
		{
			count++;
			printf("%d :: b = %d\n", count, n);
		}
	}
}

int main()
{
	getsolutions(27, 10);
	getsolutions(1155, 10);
	getsolutions(3*5*7*13, 10);
	
	test();
}
