/*

The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.

*/

#include "digit.h"
#include "fract.h"
#include "prime.h"

int	sharedDigit(long n, long k, long *a, long *b)
{
	long n1 = digit(n, 0);
	long n10 = digit(n, 1);
	long k1 = digit(k, 0);
	long k10 = digit(k, 1);
	long rv = 0;
	if (n1  == k1)  { rv++;  *a++ = n10; *b++  = k10; }
	if (n1  == k10) { rv++;  *a++ = n10; *b++  = k1;  }
	if (n10 == k1)  { rv++;  *a++ = n1;  *b++  = k10; }
	if (n10 == k10) { rv++;  *a++ = n1;  *b++  = k1;  }
	return rv;
}

void tt(long n, long d)
{
	fract f(n, d);
	cout << f.original_numerator() << " / " << f.original_denominator() << " = " << f << endl;
}

void test()
{
	tt(42, 84);
	tt(42, 48);
	exit(1);
}


int main()
{
	long n;
	//test();
	fract pr(1,1);
	for (n = 10; n <= 99; n++)
	{
		if (n%10 == 0) continue;
		//if (isPrime(n)) continue;
		for (long k = n + 1; k <= 99; k++)
		{
			if (k%10 == 0) continue;
			//if (isPrime(k)) continue;
			long a[4], b[4], m;
			 // continue if n, k have no shared 
			 // digit, or if the shared digit is 0
			if ( (m = sharedDigit(n, k, a, b)) <= 0) continue; 
			for (int i = 0; i < m; i++)
			{
				fract f(n, k);
				fract f1(a[i], b[i]);
				if (f == f1) {
					printf("n = %ld   k = %ld !!!!\n", n, k);
					cout << "Fract " << f << endl;
					pr *= f;
				}
			}
		}
	}
	printf("Product of reduced denominators for 2-digit cancelling fractions is\n");
	cout << pr << endl;
	return 1;
}
