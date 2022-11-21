#ifdef PROBLEM

A positive integer, n, is divided by d and the quotient and remainder are q and r respectively. In addition d, q, and r are consecutive positive integer terms in a geometric sequence, but not necessarily in that order.

For example, 58 divided by 6 has quotient 9 and remainder 4. It can also be seen that 4, 6, 9 are consecutive terms in a geometric sequence (common ratio 3/2).
We will call such numbers, n, progressive.

Some progressive numbers, such as 9 and 10404 = 102^2, happen to also be perfect squares.
The sum of all progressive perfect squares below one hundred thousand is 124657.

Find the sum of all progressive perfect squares below one trillion (10^12).

Given N (a perfect square, say n^2), we have for a given d, 

q = N / d;
r = N % d;

and N = n^2 = q d + r;

where q, d and r form a geometric sequence.  We know r < d, and so, only three possible orderings:
1. q < r < d
2. r < q < d
3. r < d < q

Case 1:

	q = r * t, r = t * d  for some t < 1, and t rational
	also, q = r^2 * d

	q * d + r = t^2 * d * d + t * d = (td) ^ 2 + td,
	set X = td
	then
	n^2 = X^2 + X, solving for X we get

	X = {-1 +/- sqrt(4*N^2 + 1) } / 2
		
	In order for X to be an integeger, (2n)^2 + 1 would need to be a perfect square,
	and there are not perfect squares 1 above another

	Case 1 is not possible.

Case 2: r < q < d


n = 9  a = 2  b = 1  r = 1  d = 2  q = 4
n = 10404  a = 2  b = 1  r = 36  d = 72  q = 144
n = 16900  a = 3  b = 1  r = 25  d = 75  q = 225
n = 97344  a = 23  b = 2  r = 8  d = 92  q = 1058
n = 576081  a = 40  b = 9  r = 81  d = 360  q = 1600
n = 6230016  a = 23  b = 8  r = 512  d = 1472  q = 4232
n = 7322436  a = 5  b = 4  r = 1936  d = 2420  q = 3025
n = 12006225  a = 2  b = 1  r = 1225  d = 2450  q = 4900
n = 36869184  a = 10  b = 9  r = 5184  d = 5760  q = 6400
n = 37344321  a = 4  b = 3  r = 3969  d = 5292  q = 7056
n = 70963776  a = 23  b = 18  r = 5832  d = 7452  q = 9522
n = 196112016  a = 61  b = 6  r = 432  d = 4392  q = 44652
n = 256160025  a = 6  b = 1  r = 1089  d = 6534  q = 39204
n = 1361388609  a = 10  b = 7  r = 21609  d = 30870  q = 44100
n = 1380568336  a = 33  b = 16  r = 12544  d = 25872  q = 53361
n = 13855173264  a = 2  b = 1  r = 41616  d = 83232  q = 166464
n = 16394241600  a = 3  b = 2  r = 69696  d = 104544  q = 156816
n = 123383587600  a = 3  b = 1  r = 67600  d = 202800  q = 608400
n = 547674002500  a = 24  b = 19  r = 521284  d = 658464  q = 831744
Sum is 704672670646



#endif

#include "fract.h"

#include "factor.h"
#include "digit.h"

void listem(long nstart, long nend)
{
	long sum = 0;
	while (nstart < nend)
	{
		bool found = false;
		//factor f(nstart*nstart);
		//f.out();
		for (long m = 1;  !found && m < 1000; m++)
		{
			long b = m * m;
			long b3 = b * b * b;
			for (long a = 1; !found && a < 1000; a ++)
			{
				if (gcd(a, b) != 1) continue;
				fract t(a, b);
				long rad = (4 * nstart * nstart * a * a * a + m * m);
				if (rad < 0) printf("ERROR\n");
				long sqrtrad = 0;
				//printf("rad = %ld\n", retSquare(rad));
				if (isSquare(rad, sqrtrad))
				{
					long num = (m * m * m * sqrtrad - b3);
					if (num < 0) continue;
					long den = (2 * a * a * a);
					long r = num / den;
					//printf("A n = %ld   t = %s  r = %ld = %ld/%ld\n", nstart*nstart, 
						//t.to_str().c_str(), r, num, den);
					if (num % den == 0)
					{
					  printf("B a = %ld  b = %ld  n = %ld   t = %s  r = %ld\n", a, b, nstart*nstart, 
						t.to_str().c_str(), r);
					  sum += nstart * nstart;
					  found = true;
					}
				}
			}
		}
		nstart++;
	}
	printf("Sum is %ld\n", sum);
}

bool check(long n, long a, long b)
{
	if (b != 1 && b != 2)
	{
		if (n % b != 0) return false;
	}
	long den = 2 * a * a * a;
	long rad = b * (b * b * b + 4 * a * a * a * n);
	//printf("n = %ld  a = %ld  b = %ld  rad = %ld\n",
	//	n, a, b, rad);
	long rtrad = retSquare(rad);
	if (rtrad < 0) return false;
	long num = b * b * b + b * rtrad;
	if (num < den) return false;
	//if (num % den != 0) return false;
	long r = num / den;
	if ( r % b != 0) return false;
	long d = r * a / b;
	if ( d % b != 0) return false;
	long q = d * a / b;
	if (d * q + r != n) return false;
	printf("n = %ld  a = %ld  b = %ld  r = %ld  d = %ld  q = %ld\n",
		n, a, b, r, d, q);
	fflush(stdout);
	return true;
}
typedef struct {
	long a, b, k, n;
} abc;
vector<abc> va;

void add(long a, long b, long k, long n)
{
	abc v = {a,b,k,n};
	va.push_back(v);
	size_t i = va.size() - 1;
	printf("n = %ld  a = %ld  b = %ld  k = %ld \n",
			va[i].n, va[i].a, va[i].b, va[i].k);
	fflush(stdout);
}

void out()
{
	long sum = 0;
	for (size_t i = 0; i < va.size(); i++)
	{
		long b3 =  va[i].b * va[i].b * va[i].b;
		long r = va[i].k * b3;
		long d = r * va[i].a / va[i].b;
		long q = d * va[i].a / va[i].b;
		sum += va[i].n;
		printf("n = %ld  a = %ld  b = %ld   r = %ld  d = %ld  q = %ld  k = %ld \n",
			va[i].n, va[i].a, va[i].b, r, d, q, va[i].k);
	}
}

void trythis()
{
	const long maxn = 1000000000000;	// 10^12
	const long maxk = 1000000;			// 10^6
	const long maxab = 10000;		// 10^4
	long n2, k, a, b;
	vlong ns;
	for (k = 1; k < maxk; k++)
	{
		for (b = 1; b < maxab; b++)
		{
			long b3 = b*b*b;
			for (a = b; a < maxab; a++)
			{
				long a3 = a*a*a;
				if (gcd(a,b) != 1) continue;
				n2 = b3*k*(a3*k+1);
				if (n2 > maxn) break;
				if (isSquare(n2)) add(a, b, k, n2);
			}
		}
	}
}

int mainz()
{
	//check(9, 2, 1);
	//check(10404, 2, 1);
	//check(16900, 3, 1);
	//check(97344, 23, 2);
	long sum = 0;
	for (long n = 2; n < 1000000; n++)
	{
		bool found = false;
		for (long b = 1; b <= 300; b++)
		{
			for (long a = b; a <= 300; a++)
			{
				if (gcd(a,b) != 1) continue;
				if (check(n*n, a, b)) 
				{
					sum+= n*n;
					found = true;
					break;
				}
			}
			if (found) break;
		}
	}
	printf("Sum is %ld\n", sum);
	return 1;
}

int main()
{
	trythis();
	out();
}
