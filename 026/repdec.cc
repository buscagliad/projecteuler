/*

Problem 26 - Reciprocal cycles

A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

    1/2	= 	0.5
    1/3	= 	0.(3)
    1/4	= 	0.25
    1/5	= 	0.2
    1/6	= 	0.1(6)
    1/7	= 	0.(142857)
    1/8	= 	0.125
    1/9	= 	0.(1)
    1/10	= 	0.1 

Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.


*/
#include <stdio.h>
#include "factor.h"
#include "prime.h"
#include <iostream>
#include "bigint.h"
using namespace std;

bool	bigfact(long pl, int num_nines)
{
	BigInt k(9);
	BigInt p(pl);
	int MAXN = num_nines;
	long n = MAXN;
	//printf("p = %s   ", p.c_str());
	for (; n > 0; k = k*10 + 9)
	{

		//printf("[n:%2.2ld] k: %s \n", n, k.c_str());

		if (k % p == (long) 0)
		{
		    printf("p = %s :: %d   ", p.c_str(), k.num_digits());
		    cout << k;
		    printf("\n");
		    return true;
		}
		n--;
	}
	//printf("p = %s :: %d \n", p.c_str(), MAXN);
	return false;
}

void test(long la, long lb)
{

	long lc = (la + lb)/2;
	BigInt a(la);
	BigInt b(lb);
	BigInt Q, R;
	BigInt c = avg(a, b);
	cout << a << " and " << b << "  avg -> " << c;
	printf("\n %ld  and  %ld  =  %ld\n", la, lb, lc);
	divide(a, b, Q, R);
	
	R = a % b;
	Q = a / b;
	cout << a << " mod " << b << "  Q = " << Q << "  R = " << R << endl;
}

int main()
{

	int num_complete = 0;
	int num_nines = 10000;

	for (int i = 0; i < plist_size; i++)
	{
			if ( (prime_list[i] == 2) || 
				 (prime_list[i] == 3) ||
				 (prime_list[i] == 5) ) {
				num_complete++; }
			else
			{
				if (bigfact(prime_list[i], num_nines)) num_complete++;
			}
	}
}
