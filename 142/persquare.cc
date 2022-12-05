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
// NOTE:  B and C are such that B.a^2 + B.b^2 = B.c^2 and
//                              C.a^2 + C.b^2 = C.c^2
//  with B.c == C.c
//
// x y and z are generated from the pythagorean triples in p, all of whom have the same 
//  hypotenuse.  For each distinct PT B and C, we can compute x, y and z as follows:
//       e^2 = B.b^2 - C.b^2
//       if e is a perfect square, then we have:
//				x = (B.c^2 + e^2 ) / 2;
//				y = (C.b^2 + B.a^2) / 2;
//              z = (C.b^2 - B.a^2) / 2;
//
//    and x + y = 1/2 * (B.c^2 + e^2 + C.b^2 + B.a^2) 
//              = 1/2 * (B.c^2 + B.b^2 + B.a^2)
//              = 1/2 * (B.c^2 +     B.c^2)
//              = B.c^2 (which is a perfect square)
//    The rest of the calculations follow, so that x-y, y-z, x-z, x+z and y+z are all
//              perfect squares.
//
bool	getxyz(vector<pythtrip_t> &p, long &x, long &y, long &z)
{
	bool rv = false;
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
				if ( (x > y && y > z) && check(x, y, z))
				{
					printf("B.a = %ld   B.b = %ld   B.c = %ld  \n", B.a, B.b, B.c);
					printf("C.a = %ld   C.b = %ld   C.c = %ld  \n", C.a, C.b, C.c);
					printf("x: %ld  y: %ld  z: %ld  -- sum is %ld\n", x, y, z, x+y+z);
					rv = true;
				}
			}
		}
	}
	return rv;
}

// getabs will, given an hypotenuse, produce all of the triples with
// that have that hypotenuse
//
// if there are more than 1, we have:
//    s^2 + r^2 = hyp^2
//    q^2 + q^2 = hyp^2
//
//    Note that if: (b, f, hyp) and (
//      x + y = a^2  (1)
//      x + z = b^2  (2)
//      y + z = c^2  (3)
//      x - z = d^2  (4)
//      x - y = e^2  (5)
//      y - z = f^2  (6)
//
//    Adding equations (2) and (6) yield
//      x + y = b^2 + f^2 = a^2
//    Adding equations (3) and (4) yield
//      x + y = c^2 + d^2 = a^2
//
//    Thus if a is our hyp in the algorithm, then the two solutions (b,f,a) and (c,d,a)
//    yield two pyth triples with the same hypotenuse a.  We only need to verify that
//    x - y is a perfect square (e^2).  But computing (2) - (3) we have
//      x - y = b^2 - c^2, so if this is a perfect square, we have found our x, y and z:
//    (see getxyz above for explanation)
// https://www.quora.com/Trigonometry-mathematics-How-can-I-get-a-Pythagorean-triple-from-a-given-hypotenuse-if-it-exists
//       that will produce all pyth triples for a given hypotenuse

bool	getabs(long hyp, vector<pythtrip_t> &p)
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
	#ifdef DO_DEBUG
	for (size_t i = 0; i < p.size(); i++)
	{
		printf("a: %ld   b: %ld  c: %ld (%ld)\n", p[i].a, p[i].b, 
		(long)sqrt(p[i].a*p[i].a + p[i].b*p[i].b), hyp);
	}
	#endif
	long x, y, z;
	return getxyz(p, x, y, z);
}


int main()
{
	vector<pythtrip_t> p;
	for (long c = 2; c <= 2210; c++) 
	    if (getabs(c, p)) break;
	return 0;
}

