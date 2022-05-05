#ifdef PROBLEM_DESCRIPTION

Pandigital multiples


Problem 38

Take the number 192 and multiply it by each of 1, 2, and 3:

    192 × 1 = 192
    192 × 2 = 384
    192 × 3 = 576

By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?

#endif

#include "utils.h"

long tenpower(long x)
{
	if (x < 10) return 10;
	if (x < 100) return 100;
	if (x < 1000) return 1000;
	if (x < 10000) return 10000;
	if (x < 100000) return 100000;
	if (x < 1000000) return 1000000;
	if (x < 10000000) return 10000000;
	if (x < 100000000) return 100000000;
	return -1;
}

long catapp(long a, long b)    // returns 10^n * a + b, where n is the number of digits of b
{								// example catapp(33, 125) =>  33125
	return a * tenpower(b) + b;
}

long catprod(long v, long n)
{
	long num = 0;
	for (long i = 1; i <= n; i++)
	{
		long m = i * v;
		num = catapp(num, m);
	}
	return num;
}

long	max_v = 0;
long	max_n = 0;
long	max_p = 0;
bool test(long v, long n)
{
	long p = catprod(v, n);
	bool ispd = isPandigital(p);
	//printf("n = %ld - is pandigital: %s\n", p, YN(ispd));
	if (ispd && (max_v < p) ) { max_p = p; max_v = v; max_n = n; }
	return ispd;
}
	
int	main()
{
	test(192, 3);
	test(9, 5);
	test(12, 3);
	
	test(1, 9);
	test(3, 6);
	test(4, 5);
	test(5, 5);
	test(6, 5);
	test(7, 5);
	test(8, 5);
	test(9, 5);
	
	// two-digit 10 thru 24 do not work, 4 yields at most 8 digits, 5 yields 10 digits
	// two digit 34 thru 99 do not work, 3 yields 10 digits 2 not enough digits 
	for (long n = 25; n <= 35; n++)
	    test(n, 4);
	    
	// three-digit 100 - 333 will yield 9 digits for 3
	// 334 and greater yields 8 digits for 2 and > 9 for 3
	for (long n = 100; n <= 333; n++)
	    test(n, 3);
	    
	// four-digit 1000 - 4999 yeilds only 8 digits for 2, and too many for 3
	// 5000 - 9999 yeidls 9 digits for 2
	for (long n = 5000; n <= 9999; n++)
	    test(n, 2);
	
	// problem does not allow for 1, which would be 987654321 as the best number
	//test(987654321, 1);
	
	printf("Largest concatenated product that is pandigital is: %ld, occuring at (%ld, %ld)\n", max_p, max_v, max_n);
	
}

	
	
