

#include <cstdio>
#include <cstring>

#define NUM_DIGITS 100

long	C[10][10][NUM_DIGITS+1];
long 	N[NUM_DIGITS+1];		// N[n] is count of number of non-bouncy numbers of n or fewer digits
long 	D[NUM_DIGITS+1];		// D[n] is count of number of non-bouncy numbers of n digits

void	init()
{
	memset(C, 0, 10 * 10 * (NUM_DIGITS + 1) * sizeof(long));
	memset(N, 0, (NUM_DIGITS + 1) * sizeof(long));
	memset(D, 0, (NUM_DIGITS + 1) * sizeof(long));
	for (int s = 1; s <= 9; s++)
	{
		for (int e = 0; e <= 9; e++)
		{
			C[s][e][2] = 1;
		}
	}
	N[1] = 9;
	N[2] = 99;
	D[1] = 9;
	D[2] = 90;
	//if (s != 0) 

}

long	sumc(int s, int e, int n)
{
	long sum = 0;
	//if (s == 0) return 0;
	if (s < e)
	{
		for (int alpha = s; alpha <= e; alpha++)
		    sum += C[alpha][e][n];
	}
	else if (s > e)
	{
		for (int alpha = e+1; alpha <= s; alpha++)
		    sum += C[alpha][e][n];
	}
	else
		sum = 1;
	return sum;
}

void	computeDN(int n)
{
	long sum = 0;
	for (int alpha = 0; alpha <= 9; alpha++)
	{
		for (int beta = 0; beta <= 9; beta++)
		{
			if (alpha == 0 && beta == 0) continue;
			sum += C[alpha][beta][n];
		}
	}
	if (n == 1) { sum = 9; }
	D[n] = sum;
	N[n] = sum + N[n-1];
}

void	build()
{
	for (int n = 3; n <= NUM_DIGITS; n++)
	{
		for (int s = 0; s <= 9; s++)
		{
			for (int e = 0; e <= 9; e++)
			{
				C[s][e][n] = sumc(s, e, n - 1);
				//printf("%d  start: %d   end: %d   count: %ld \n", 
				//	n, s, e, C[s][e][n]);
			}
		}
	}
}

int main()
{
	init();
	build();
	for (int n = 1; n <= NUM_DIGITS; n++)
	{
		//if (n > 2) 
		computeDN(n);
		printf("n: %d   N: %ld   D:%ld\n", n, N[n], D[n]);
	}
}
	
