

#ifdef PROBLEM_DESCRIPTION



#endif

#include <vector>
#include <cmath>
#include <cstdio>
#include "digit.h"

using namespace std;

int	contfrac(int n, int &a0, vector<int> &cf)
{
	double dn = n;
	a0 = sqrt(dn);
	long a = a0;
	long r = a;
	long s = (n - r * r);
	cf.clear();
	bool done = false;
	while (!done)
	{
		a = (double)(r + a0) / (double) s;
		r = a * s - r;
		s = (n - r * r)/s;
		cf.push_back(a);
		done = a == 2 * a0;
	}
		
	return cf.size();
}

void docf(int n, int &odd_periods)
{
	vector<int> v;
	int a0;
	contfrac(n, a0, v);
	printf("Continued fraction for square root of %d is: ", n);
	printf("[%d,(%d", a0, v[0]);
	for (size_t i = 1; i < v.size(); i++)
	    printf(",%d", v[i]);
	printf(")]\n");
	if (v.size() % 2) odd_periods++;
}

#define MAX_NUM 10000
int main()
{
	int odd = 0;
	for (int j = 2; j <= MAX_NUM; j++)
	{
		if (isSquare(j)) continue;
		docf(j, odd);
	}
	printf("Number of odd continued fraction periods <= %d is %d\n",
		MAX_NUM, odd);
	
}
