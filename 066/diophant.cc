#ifdef PROBLEM_DESCRIPTION


Solutions
Fundamental solution via continued fractions

Let h i / k i {\displaystyle h_{i}/k_{i}} {\displaystyle h_{i}/k_{i}} denote the sequence of convergents to the regular continued fraction for n {\displaystyle {\sqrt {n}}} {\sqrt {n}}. This sequence is unique. Then the pair ( x 1 , y 1 ) {\displaystyle (x_{1},y_{1})} (x_{1},y_{1}) solving Pell's equation and minimizing x satisfies x1 = hi and y1 = ki for some i. This pair is called the fundamental solution. Thus, the fundamental solution may be found by performing the continued fraction expansion and testing each successive convergent until a solution to Pell's equation is found.[16]

The time for finding the fundamental solution using the continued fraction method, with the aid of the Schönhage–Strassen algorithm for fast integer multiplication, is within a logarithmic factor of the solution size, the number of digits in the pair ( x 1 , y 1 ) {\displaystyle (x_{1},y_{1})} (x_{1},y_{1}). However, this is not a polynomial-time algorithm because the number of digits in the solution may be as large as √n, far larger than a polynomial in the number of digits in the input value n.[17] 

#endif

#include <cstdio>
#include "digit.h"

#include "bigint.h"


typedef BigInt INT;
//typedef long INT;

// contfrac returns continued fraction for square root of n
int	contfrac(int n, int &a0, vector<int> &cf)
{
	double dn = n;
	a0 = sqrt(dn);
	int a(a0);
	int r(a);
	int s(n - r * r);
	cf.clear();
	bool done = false;
	while (!done)
	{
		//a = (double)(r + a0) / (double) s;
		a = (r + a0) / s;
		r = a * s - r;
		s = (n - r * r)/s;
		cf.push_back(a);
		done = a == 2 * a0;
	}
		
	return cf.size();
}

int	g_a0;
int	g_D;
vector<int> g_an;

void cf_out()
{
	printf("Continued fraction for square root of %d is: ", g_D);
	printf("[%d,(%d", g_a0, g_an[0]);
	for (size_t i = 1; i < g_an.size(); i++)
	    printf(",%d", g_an[i]);
	printf(")]\n");
}

INT an(int n)
{
	if (n == 0) return g_a0;
	int index = (n - 1) % g_an.size();
	return g_an[index];
}

INT hNext(bool init=false)
{
	static INT hnm2(0l);
	static INT hnm1(1l);
	static int n(-1);
	if (init)
	{
		hnm2 = 0l;
		hnm1 = 1l;
		n = -1;
		return 0l;
	}
	n++;
	INT hn = an(n) * hnm1 + hnm2;
	hnm2 = hnm1;
	hnm1 = hn;
	return hn;
}

INT kNext(bool init=false)
{
	static INT knm2(1l);
	static INT knm1(0l);
	static int k(-1);
	if (init)
	{
		knm2 = 1l;
		knm1 = 0l;
		k = -1;
		return 0l;
	}
	k++;
	INT kn = an(k) * knm1 + knm2;
	knm2 = knm1;
	knm1 = kn;
	return kn;
}

void	next(INT &h, INT &k)
{
	h = hNext();
	k = kNext();
}

INT	dioph(long D)
{
	g_D = D;
	contfrac(g_D, g_a0, g_an);
	cf_out();
	hNext(true);
	kNext(true);
	bool done = false;
	INT x, y;
	while (!done)
	{
		next(x, y);
		INT ls = D * y * y + 1;
		INT rs = x * x;
	    if (ls == rs)
	    {
			printf("D: %ld   x: %s   y: %s\n", D, x.c_str(), y.c_str());
			return x;
		}
	}
	return 0l;
}

long   minD(long maxValue)
{
	INT maxdio = 0l;
	long maxd = 0;
	for (long D = 2; D <= maxValue; D++)
	{
		printf("D = %ld\n", D);
		if (isSquare(D)) continue;
		INT dio = dioph(D);
		if (dio > maxdio) {
			maxdio = dio;
			maxd = D;
		}
	}
	return maxd;
}

int main()
{
	printf("D <= 7::   %ld\n", minD(7));
	printf("D <= 1000::   %ld\n", minD(1000));
}
