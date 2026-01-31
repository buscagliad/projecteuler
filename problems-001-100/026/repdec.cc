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
	long n = 1;
	//printf("p = %s   ", p.c_str());
	for (; n < MAXN; k = k*10 + 9)
	{

		//printf("[n:%2.2ld] k: %s \n", n, k.c_str());

		if (k % p == (long) 0)
		{
		    printf("p = %s :: %d   ", p.c_str(), k.num_digits());
		    cout << k;
		    printf("\n");
		    return true;
		}
		n++;
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

int num_repeats(int p, string &repeat)
{
	vlong v;
	int	n = 10;
	//if (p > 10) n = 100;
	//if (p > 100) n = 1000;
	int d = n / p;  // always a single digit
	repeat = "";
	repeat += d + '0';
	n = 10 * (n - d * p);
	int saved_n = n;
	v.add(n);
	do {
		d = n / p;
		n = 10 * (n - d * p);
		//printf("p: %d  n: %d  d: %d   saved: %d\n",
		//	p, n, d, saved_n);
		if ((n == 0) || v.exists(n) ) break;
		v.add(n);
		repeat += d + '0';
	} while (n != saved_n);
	return repeat.size();
}
		
int check(int n)
{		
	string str;
	int r = num_repeats(n, str);
	printf("Num repeates of %d is %d\n", n, r);
	//printf("    repeat: %s\n", str.c_str());
	return r;
}

int main()
{
	int max_n = 0;
	int max_repeats = 0;
	string max_str;
	int n;
	int r;
	string rep;
	for (n = 11; n < 1000; n++)
	{
		r = num_repeats(n, rep);
		printf("Num repeats of %d is %d\n", n, r);
		if (r > max_repeats)
		{
			max_n = n;
			max_repeats = r;
			max_str = rep;
		}
	}
	printf("N: %d   Repeat Count: %d\n", max_n, max_repeats);

// trying another way -- problem with assumption of 9's
// use above solution only.
	//exit(1);
	int num_complete = 0;
	int num_nines = 10000;
	Prime p;	// reads in file

	for (int i = 0; prime_list[i] < 1000; i++)
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
