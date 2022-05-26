#ifdef PROBLEM_DESCRIPTION

Powerful digit counts
Problem 63

The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 134217728=8^9, is a ninth power.

How many n-digit positive integers exist which are also an nth power?


1 ^ 1  =  1   has  1 digits
2 ^ 1  =  2   has  1 digits
3 ^ 1  =  3   has  1 digits
4 ^ 1  =  4   has  1 digits
4 ^ 2  =  16   has  2 digits
5 ^ 1  =  5   has  1 digits
5 ^ 2  =  25   has  2 digits
5 ^ 3  =  125   has  3 digits
6 ^ 1  =  6   has  1 digits
6 ^ 2  =  36   has  2 digits
6 ^ 3  =  216   has  3 digits
6 ^ 4  =  1296   has  4 digits
7 ^ 1  =  7   has  1 digits
7 ^ 2  =  49   has  2 digits
7 ^ 3  =  343   has  3 digits
7 ^ 4  =  2401   has  4 digits
7 ^ 5  =  16807   has  5 digits
7 ^ 6  =  117649   has  6 digits
8 ^ 1  =  8   has  1 digits
8 ^ 2  =  64   has  2 digits
8 ^ 3  =  512   has  3 digits
8 ^ 4  =  4096   has  4 digits
8 ^ 5  =  32768   has  5 digits
8 ^ 6  =  262144   has  6 digits
8 ^ 7  =  2097152   has  7 digits
8 ^ 8  =  16777216   has  8 digits
8 ^ 9  =  134217728   has  9 digits
8 ^ 10  =  1073741824   has  10 digits
9 ^ 1  =  9   has  1 digits
9 ^ 2  =  81   has  2 digits
9 ^ 3  =  729   has  3 digits
9 ^ 4  =  6561   has  4 digits
9 ^ 5  =  59049   has  5 digits
9 ^ 6  =  531441   has  6 digits
9 ^ 7  =  4782969   has  7 digits
9 ^ 8  =  43046721   has  8 digits
9 ^ 9  =  387420489   has  9 digits
9 ^ 10  =  3486784401   has  10 digits
9 ^ 11  =  31381059609   has  11 digits
9 ^ 12  =  282429536481   has  12 digits
9 ^ 13  =  2541865828329   has  13 digits
9 ^ 14  =  22876792454961   has  14 digits
9 ^ 15  =  205891132094649   has  15 digits
9 ^ 16  =  1853020188851841   has  16 digits
9 ^ 17  =  16677181699666569   has  17 digits
9 ^ 18  =  150094635296999121   has  18 digits
9 ^ 19  =  1350851717672992089   has  19 digits
9 ^ 20  =  12157665459056928801   has  20 digits
9 ^ 21  =  109418989131512359209   has  21 digits
There are 49 n-digit positive integers which are also an nth power


#endif

#include <cstdio>
#include "bigint.h"


bool	bigdigs(BigInt &a, BigInt &b)
{
	BigInt p = a ^ b;
	long   nd = p.num_digits();
	BigInt bnd(nd);
	if (bnd == b)
	{
	    printf("%s ^ %s  =  %s   has  %s digits\n", 
			a.c_str(), b.c_str(), p.c_str(), bnd.c_str());
		return true;
	}
	return false;
}

bool test(long al, long bl)
{
	BigInt	a(al);
	BigInt  b(bl);
	return bigdigs(a, b);
}

int main()
{
	int	count = 0;
	for (long a = 1; a < 10; a++)
	{
		for (long b = 1; b < 100; b++)
		{
			if (test(a, b)) count ++;
		}
	}
	printf("There are %d n-digit positive integers which are also an nth power\n", count);
}
	
	
