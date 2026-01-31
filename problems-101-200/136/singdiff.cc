/*
The positive integers, x, y, and z, are consecutive terms of an arithmetic progression. 
* Given that n is a positive integer, the equation, x^2 − y^2 − z^2 = n, has exactly one 
* solution when n = 20:

13^2 − 10^2 − 7^2 = 20

In fact there are twenty-five values of n below one hundred for which the equation has 
a unique solution.

How many values of n less than fifty million have exactly one solution?
*/

#include <cstring>
#include <cstdio>

#define DEBUG 0

bool samediff(int x, int y, int z, int n)
{
	if (x*x - y*y - z*z == n) return true;
	return false;
}

bool testab(int a, int b, int n)
{
	return samediff(a + 2*b, a + b, a, n);
}

bool testuv(int u, int v)
{
	int a = (3 * v - u) / 4;
	int b = (u + v) / 4;
	int n = u * v;
	bool sd = samediff(a + 2*b, a + b, a, n);
	printf("[%s]x: %d  y: %d  z: %d   u: %d  v: %d  n: %d\n", 
		(sd?"GOOD":"*BAD"), a + 2*b, a + b, a, u, v, u*v);
	return sd;
}



#define MAXN  50000000
int COUNT[MAXN];

void init()
{
	memset(COUNT, 0, MAXN * sizeof(int));
}

void test()
{
	int u = 1;
	int v = 1;
	for (u = 1; u < MAXN; u++)
	{
		for (v = 1; u * v < MAXN; v++)
		{
			if ( (u + v) % 4 == 0)
			{
				int a = 3 * v - u;
				if ( a > 0 && (a % 4 == 0) )
				{
					//testuv(u, v);
					COUNT[u*v]++;
				}
			}
		}
	}
}

void	result(int numsols, int maxn)
{
	int count = 0;
	for (int i = 1; i < maxn; i++)
	{
		if (COUNT[i] == numsols) count++;
	}
	printf("Number of solutions for a given n: %d   below %d  count: %d\n", 
		numsols, maxn, count);
}

void resone()
{
	for (int i = 1; i < 100; i++)
	{
		if (COUNT[i] == 1) printf("%d has one solution\n", i);
	}
}

int main()
{
	init();
	
	test();
	
	result(10, 1000000);
	result(1, MAXN);
}
