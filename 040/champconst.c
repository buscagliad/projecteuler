#ifdef PROBLEM_DESCRIPTION


Champernownes constant

Problem 40

An irrational decimal fraction is created by concatenating the positive integers:
           111111
  123456789012345
0.123456789101112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000

#endif

#include <cstdio>
#include <string.h>

#include "digit.h"

/*

1-9 (index 1 thru 9)
10-99 (index 10 thru 10 + 90 * 2 - 1) (10 thru 189)
100-999 (index 190 thru 190 + 900 * 3 - 1) (190 thru 2889)
1000-9999 (index 2890 thru 2890 + 9000 * 4 - 1) ( 2890 thru 38889 )

 */

#define NTH
long index_low[10];	// nth digit index :  index_low[n]  thru  index_high[n]
long index_high[10];


void init()
{
	index_low[1] = 1;
	index_high[1] = 9;
	long ninex = 9;
	for (long d = 2; d <= 9; d++)
	{
		ninex *= 10;
		index_low[d] = index_high[d-1] + 1;
		index_high[d] = index_low[d] + ninex * d - 1;
	}
}

void debug()
{
	for (long d = 1; d <= 9; d++)
	{
		printf("for an index for a %ld digit entry, range is %ld thru %ld\n",
			d, index_low[d], index_high[d]);
	}
}

//
// getndigit - returns the digit (from the right, 0 is the most right)
long getndigit(long number, long digit)
{
	switch(digit)
	{
		case 7: number /= 10;
		case 6: number /= 10;
		case 5: number /= 10;
		case 4: number /= 10;
		case 3: number /= 10;
		case 2: number /= 10;
	}
	return number % 10;

}

long champnum(int index)
{
	int i = 1;
	for (i = 1; i <= 10; i++)
	{
		if ((index_low[i] <= index) && (index <= index_high[i])) break;
	}
	// i - represents the number of digits (starting at 10^i thru 10^(i+1)-1
	int left_over = index - index_low[i];
	// which number does left_over represent
	int ndigit = left_over / i;	// ndigit represents the amount over 10^i
	int which_digit = i - left_over % i; // this is the digit in the 'which_number' below
	long teni = 1;
	for (long k = i-1; k > 0; teni *= 10, k--);
	long which_number = teni + ndigit;	// is to get to the next number
	
	printf("index: %d   left_over: %d  ndigit: %d  teni: %ld   which_number: %ld\n",
		index, left_over, which_digit, teni, which_number);
	
	return getndigit(which_number, which_digit);
}

#define CORRECT(a,b)	(a == b) ? "CORRECT" : "ERROR"

void test(long a, long d)
{
	long ch = champnum(a);
	printf("Champ's digit at %ld is %ld (%ld) %s\n", a, ch, d, CORRECT(ch, d));
}



int main()
{
	init();
	test(12, 1);
	test(38890 + 2345 * 5, 1);
	test(38890 + 2345 * 5 + 1, 2);
	test(38890 + 2345 * 5 + 2, 3);
	test(38890 + 2345 * 5 + 3, 4);
	test(38890 + 2345 * 5 + 4, 5);
	test(38890 + 2345 * 5 + 5, 1);
	test(38890 + 2345 * 5 + 6, 2);
	test(38890 + 2345 * 5 + 7, 3);
	test(38890 + 2345 * 5 + 8, 4);
	test(38890 + 2345 * 5 + 9, 6);
	long dd = champnum(1) * champnum(10) * champnum(100) * champnum(1000) *
			  champnum(10000) * champnum(100000) * champnum(1000000);
	printf("Problem 40 - answer %ld\n", dd);
	
}
