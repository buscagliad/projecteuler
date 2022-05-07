#ifdef PROBLEM_DESCRIPTION

Integer right triangles


Problem 39

If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised?

#endif

#include "utils.h"

typedef struct triple {
	int a, b, c;
} triple;

typedef struct pythtrip {
	int				N;
	vector<triple> 	t;
} pythtrip;



bool validRightTriangle(int a, int b, int c)
{
	return a*a + b*b == c*c;
}

bool validPerim(int a, int b, int N)
{
	int c = N - a - b;
	return validRightTriangle(a, b, c);
}

long generatePythTriple(long  m, long  n, long  k,
						long &a, long &b, long &c)
{
	long n2 = n*n;
	long m2 = m*m;
	a = n2 - m2;
	b = 2 * m * n;
	c = n2 + m2;
	a *= k;	
	b *= k;	
	c *= k;	
	return a + b + c;
}

#define MAX_P 1000
pythtrip p[MAX_P+1];

bool exists(int a, int n)
{
	for (size_t k = 0; k < p[n].t.size(); k++)
	{
		if (p[n].t[k].a == a) return true;
	}
	return false;
}
	

void	addTrip(int a, int b, int c)
{
	int n = a + b + c;
	if (exists(a, n)) return;
	triple t = {a, b, c};
	p[n].t.push_back(t);
	p[n].N = n;
}

void tripOut(int n)
{
	printf("N = %d\n", p[n].N);
	for (size_t i = 0; i < p[n].t.size(); i++)
		printf("%5lu : (%3d, %3d, %3d)\n", i+1, p[n].t[i].a, p[n].t[i].b, p[n].t[i].c); 
}

int main()
{
	//memset(v, 0, (MAX_P+1)*sizeof(long));
	long a, b, c;
	for (long m = 1; m < MAX_P; m++)
	{
		for (long n = m + 1; n < MAX_P; n++)
		{
			long k = 1;
			long pt = generatePythTriple(m, n, k, a, b, c);
			while (pt < MAX_P)
			{
				addTrip(a, b, c);
				k++;
				pt = generatePythTriple(m, n, k, a, b, c);
			}
		}
	}
	// find max value:
	long max_p = 0;
	for (int i = 0; i<=MAX_P; i++)
	{
		if (p[i].t.size() > p[max_p].t.size()) max_p = i;
	}
	printf("Max number of triples formed from sums <= %d is from %ld with %lu triplets\n", MAX_P, max_p, p[max_p].t.size());
	tripOut(max_p);
	
}
