#ifdef PROBLEM_DESCRIPTION

Counting summations


Problem 76

It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two positive integers?
#endif

#include <cstdio>
#include <cstring>

int F(int n);

int carray(int N, int k)
{
	if (k == 0) return 0;
	if (k == 1) return 1;
	if (k >= N) return F(k);
	int ret = (N - k)/k;
	return ret * F(k) + carray(k, k - ret);
}

int F(int n)
{
	int sum = 0;
	if (n == 1) return 1;
	if (n == 2) return 2;
	if (n == 3) return 2;
	if (n == 4) return 4;
	if (n == 5) return 6;
	if (n % 2 == 1) // n is odd
	{
		for (int k = 1; k < n/2; k++)
		{
			sum += F(k);
		}
		for (int k = n/2; k < n-1; k++)
		{
			sum += carray(n, k);
		}
	}
	else
	{
		for (int k = 1; k < n/2; k++)
		{
			sum += F(k);
		}
		for (int k = n/2; k < n-1; k++)
		{
			sum += carray(n, k);
		}
	}
	return sum;
}

#define MAXDIM 1000
long    precomp[MAXDIM][MAXDIM];

long	ways(long total, long max)
{
	if (max <= 1) return 1;
	// by defintion
	long res = 0;
	while (total >= 0)
	{
		long w;
		if ( (total < MAXDIM) && (precomp[total][max-1] > 0) )
		{
			w = precomp[total][max-1];
		}
		else
		{
			w = ways(total, max-1);
			precomp[total][max-1] = w;
		}
		res = res + w;
		total = total - max;
	}
	return res;
}




int main()
{
	long	total = 8;	// desired total
	memset(precomp, 0, MAXDIM * MAXDIM * sizeof(long));
	for (total = 5; total <= 100; total+=5)
	{
		printf("Number of ways to add to %ld is %ld\n", total, 
			ways(total, total) - 1);
	}
}


