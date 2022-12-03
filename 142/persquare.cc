/*
Problem 142

Find the smallest x + y + z with integers x > y > z > 0 such that 
x + y, x − y, x + z, x − z, y + z, y − z are all perfect squares.
*/


#include "utils.h"
#include "digit.h"
#include <algorithm>
#include "factor.h"
#include <vector>

#define SQR(x)  ((x)*(x))

long generatePythTriple(long  m, long  n, 
						long &a, long &b, long &c)
{
	long n2 = n*n;
	long m2 = m*m;
	a = m2 - n2;
	if (a % 2 == 0)
	{
		b = a;
		a = 2 * m * n;
	}
	else
	    b = 2 * m * n;
	c = n2 + m2;
	if (a > b) std::swap(a, b);
	return a + b + c;
}

#define MAX_P 1000l

typedef struct 
{
	long a;
	long b;
} sqcol;

//
// look for a matching pair::
//        there is some 'a' that matches y;
//        then need to look at x - b and x + b
//        to see if they are both squares

vector<sqcol> vs;
typedef vector<sqcol>::iterator sqit;

long add(long x, long y)
{
	sqcol s={x, y};
	for (sqit it = vs.begin(); it != vs.end(); it++)
	{
		if (it->a == y)
		{
			if (isSquare(x + it->b) && isSquare(x - it->b))
			{
				return x + y + it->b;
			}
		}
	}
	vs.push_back(s);
	return 0;
}

bool check(long x, long y)
{
if (isSquare(x+y) && isSquare(x-y))  return true;
	return false;
}

bool check(long x, long y, long z)
{
	if (isSquare(x+y) && isSquare(x-y) &&
	    isSquare(x+z) && isSquare(x-z) &&
	    isSquare(z+y) && isSquare(y-z) ) return true;
	return false;
}

void generateXY(long m, long n, long k, long &x, long &y)
{
	long D, E, F;	// initial pythagorean triple
	generatePythTriple(m, n, D, E, F);  // D < E < F and D^2 + E^2 = F^2
	while (k % 4 == 0) k /= 4;
	D *= k;
	E *= k;
	F *= k;
	if (D % 2 == 0)
	{
		x = 2 * F;
		y = 2 * E;
	}
	else
	{
		x = 2 * F;
		y = 2 * D;
	}
	if (check(x,y)) printf("GOOD  x: %9ld  y: %9ld  k: %3ld\n", x, y, k);   
	else printf("BAD   x: %9ld  y: %9ld  k: %3ld\n", x, y, k);   

}

void test()
{
	long m, n, k, x, y;
	for (n = 1; n < 100; n++)
	{
		for ( m = n + 1; m < MAX_P; m+=2) // m > n
		{
			if (gcd(m, n) != 1) continue;
			for ( long k1 = 1; k1 < 10; k1+=2)
			{
				k = k1 * k1;
				generateXY(m, n, k, x, y);
				if (check(x, y)) 
					printf("   check\n");
				else 	
					printf("   FAIL\n");
			}
		}
	}
}
			
// returns x+y+z on success, 0 otherwise
//
long generateSOL(long mi, long ni, long ki, long &x, long &y, long &z)
{
	generateXY(mi, ni, ki, y, z);	// x < y < z
	
	printf("m: %ld  n: %ld    y: %ld    z: %ld\n", mi, ni, y, z);
	fflush(stdout);
	long yn;
	for (long n = ni; n < MAX_P; n++)
	{
		for (long m = n + 1; m < MAX_P; m+=2) // m > n
		{
			if (gcd(m, n) != 1) continue;
			for (long k = ki; k < 1000; k++)
			{
				generateXY(m, n, k, x, yn);
				if (yn > y) break;
				printf("--> m: %ld  n: %ld  k: %ld   x: %ld    yn: %ld\n", m, n, k, x, yn);
	//fflush(stdout);
				if (yn == y)
				{
					if (check(x, y, z)) return x+y+z;
					break;
				}
			}
		}
	}
	return 0;
}

// x > y > z > 0
//
// x + y = a^2
// x - y = b^2
// x + z = c^2
// x - z = d^2
// y + z = e^2
// y - z = f^2
//
// clearly 
//         a > b > c > d > e > f

// for f = 1 to !!!
//     for e = f+1 to !!!
//         for d = e+1 to !!!//        for d = e+1 to !!!
//            for c = d+1 to !!!
//                for b = c+1 to !!!
//                    for a = b+1 to !!!
//						   a2 = a*a
//						   b2 = b*b
//						   c2 = c*c
//						   d2 = d*d
//						   e2 = e*e
//						   f2 = f*f
//							if ( (a2 + b2 == c2 + d2) &&
//								 (a2 - b2 == e2 + f2) &&
//								 (c2 - d2 == e2 - f2) )
//								x = (a2 + b2) / 2
//								y = (e2 + f2) / 2
//								z = (e2 - f2) / 2
//							    print - return x, y, z
//
#define MAX 1000
void	getxyz(long &x, long &y, long &z)
{
	for (int f = 1; f < MAX; f++)
	{
		int f2 = f * f;
		for (int e = f+2; e < MAX; e++)
		{
			int e2 = e * e;
			for (int d = e+2; d < MAX; d++)
			{
				int d2 = d * d;
				for (int c = d+2; c < MAX; c++)
				{
					int c2 = c * c;
					for (int b = c+2; b < MAX; b++)
					{
						int b2 = b * b;
						for (int a = b+2; a < MAX; a++)
						{
							int a2 = a * a;

							if ( (a2 + b2) == (c2 + d2) &&
								 (a2 - b2) == (e2 + f2) &&
								 (c2 - d2) == (e2 - f2) )
							{
								x = (a2 + b2) / 2;
								y = (e2 + f2) / 2;
								z = (e2 - f2) / 2;
								long sum = x + y + z;
								printf("x: %ld  y: %ld  z: %ld  sum: %ld\n", x, y, z, sum);
							}
						}
					}
				}
			}
		}
	}
}

typedef struct {
	long a, b, c; // a < b < c  a^2 + b^2 = c^2
} pythtrip_t;

int add(long a, long b, vector<pythtrip_t> &p)
{
	for (vector<pythtrip_t>::iterator it = p.begin(); it != p.end(); it++)
	{
		if ( (it->a == a) && (it->b == b) ) return p.size();
	}
	long c2 = a*a + b*b;
	long c;
	if (isSquare(c2, c))
	{
		pythtrip_t t;
		t.a = a;
		t.b = b;
		t.c = c;
		p.push_back(t);
	}
	return p.size();
}

bool	getxyz(vector<pythtrip_t> &p, long &x, long &y, long &z)
{
	for (size_t i = 0; i < p.size(); i++)
	{
		for (size_t j = i+1; j < p.size(); j++)
		{
			pythtrip_t B, C;
			// is p[i].b ^2 - p[j].b^2 a perfect square?
			if (p[i].b > p[j].b) { B = p[i]; C = p[j]; }
			else { B = p[j]; C = p[i]; }
			long sq = SQR(B.b) - SQR(C.b);
			long e;
			if (isSquare(sq, e))
			{
				x = (SQR(B.c) + SQR(e)  ) / 2;
				y = (SQR(C.b) + SQR(B.a)) / 2;
				z = (SQR(C.b) - SQR(B.a)) / 2;
				printf("x: %ld  y: %ld  z: %ld  -- sum is %ld\n", x, y, z, x+y+z);
			}
		}
	}
	return 0;
}

size_t	getabs(long hyp, vector<pythtrip_t> &p)
{
// hyp:: An integer hypotenuse
// Storing (a, b) s.t., a^2+b^2 = c^2
	//vector<long> a;
	//vector<long> b;
	factor	C(hyp);
	vlong_t	kf = C.divisors();
	p.clear();
	for (size_t i = 0; i < kf.size(); i++) // For k in FactorsOf(c):
	{
		long k = kf[i];
		long s = hyp/k;		// s := c / k
		for (long n = 0; n < sqrt(s/2); n++)
		{
			//For n := 0 to Sqrt(s/2): // Local optimization, we know that m >= n
			long mSquare = s - n * n;
			long m = floor(sqrt(mSquare));
			if (m * m == mSquare)
			{
				long ax = m * m - n * n;
				long bx = 2 * m * n;
				if (ax > bx) std::swap(ax, bx);
				ax *= k;
				bx *= k;
				//printf("k: %ld  m: %ld   n: %ld  a: %ld  b: %ld\n", k, m, n, ax, bx);
				add(ax, bx, p);
			}
		}
	}
	
	for (size_t i = 0; i < p.size(); i++)
	{
		printf("a: %ld   b: %ld  c: %ld (%ld)\n", p[i].a, p[i].b, 
		(long)sqrt(p[i].a*p[i].a + p[i].b*p[i].b), hyp);
	}
	return 0;
}


int main()
{
	vector<long> a;
	vector<long> b;
	vector<pythtrip_t> p;
	getabs(2210, p);
	return 1;
	long x, y, z;
	getxyz(x, y, z);
	return 1;
	//test();
	//return 0;
	if (check(2843458,2040642,1761858))
		printf("GOOD\n");
	fflush(stdout);
	//return 0;
	for (long n = 1; n <= MAX_P; n++)
	{
		for (long m = n + 1; m <= MAX_P; m+=2) // m > n
		{
			if (gcd(m, n) != 1) continue;
			for (long k = 1; k < 1000; k++)
			{
				long res = generateSOL(m, n, k, x, y, z);  
				//printf("m: %ld  n: %ld  k: %ld  x: %ld  y: %ld  z: %ld  res: %ld\n",
				//	m, n, k, x, y, z, res);
				if (res > 0) 
				{
					printf("Smallest x+y+z is %ld + %ld + %ld = %ld\n", x, y, z, res);
					return 0;
				}
			}
		}
	}

	printf("Exitting\n");
}

