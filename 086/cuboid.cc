#ifdef PROBLEM_DESCRIPTION



A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3, and a fly, F, sits in the opposite corner. By travelling on the surfaces of the room the shortest "straight line" distance from S to F is 10 and the path is shown on the diagram.

However, there are up to three "shortest" path candidates for any given cuboid and the shortest route doesnt always have integer length.

It can be shown that there are exactly 2060 distinct cuboids, ignoring rotations, with integer dimensions, up to a maximum size of M by M by M, for which the shortest route has integer length when M = 100. This is the least value of M for which the number of solutions first exceeds two thousand; the number of solutions when M = 99 is 1975.

Find the least value of M such that the number of solutions first exceeds one million.

Solution:   d(x) = sqrt(b^2 + x^2) + sqrt(a^2 + (a - x)^2)

taking derivative and setting to zero, yields:

                   a * b
              x = -------
                   b + c

plugging into d(x) yields:

				sqrt((b + c)^2 + a^2)
				
By symmetry, going on surface "bc" first, yields 

                sqrt((a + c)^2 + b^2)
                
and going on surface "ac" first, yields

                sqrt((a + b)^2 + c^2)
                
                
if any of these are integers (e.g. (b + c)^2 + a^2 is a perfect square)
then the cuboid minimum is an integer.


We know how to generate pythagorean triples, A, B and C such that
      A^2 + B^2 = C^2
      
we can then find a, b and c that will resolve the solution

For example, 6, 8, 10 form a pyth triple
      if we set a = 6, and b + c = 8, st. a >= b >= c, then
      we can see that b = 5, c = 3 yiels this result
      Note that b = 4, c = 4  and b = 6, c = 2 also produces a solution


In this case, M <= max(a, b, c) = a (by definition)

so we will find all pythorean triples, A, B and C, then set a = A, and find b, c
such that b+c = B with a>=b>=c

#endif

#include <cstdio>

#include "digit.h"

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

#define SQ(n)	 ((n)*(n))
bool cuboid(long a, long b, long c)
{
	if ( (a > b) || (b > c) ) printf("ERROR: a: %ld  b: %ld  c: %ld\n", a, b, c);
	long ac = SQ(a+c) + SQ(b);
	long bc = SQ(b+c) + SQ(a);
	long ab = SQ(a+b) + SQ(c);
	if (ab <= bc && ab <= ac) {
		if (isSquare(ab))
		{
			return true;
		}
		//printf("(%ld,%ld,%ld) NOT A SQUARE: %ld\n", a, b, c, ab);
		return false;
	}
	if ( (ac <= bc) && (ac <= ab) )
	{
		printf("ERROR ac :: %ld < %ld < %ld\n", ac, bc, ab);
		return isSquare(ac);
	}
	else if ( (bc <= ac) && (bc <= ab) )
	{
		printf("ERROR bc\n");
		return isSquare(bc);
	}
	printf("ERROR ab\n");
	return isSquare(ab);
}


long cubaloids(long MAX_P)
{
	//memset(v, 0, (MAX_P+1)*sizeof(long));
	long A, B, C;
	long cnt = 0;
	for (long n = 1; n <= 200*MAX_P; n++)
	{
		for (long m = n + 1; m <= 200*MAX_P; m+=2) // m > n
		{
			generatePythTriple(m, n, A, B, C);
			if (A > MAX_P) break;
			if (gcd(m,n) != 1) continue;
			//if (B/2 + 1 >= A) continue;
			long k = 1;
			if (0) printf("A: %ld  B: %ld \n", A, B);
			bool done = false;
			// minimum occurs for a <= b <= c
			// a+b <= c produces (a+b)/2 solutions
			// if (a+b >= c, then we have c - (a + b)/2 +
			
			while (!done)
			{
				done = true;
				long a, b, c;

				// Either a + b <= c

				b = k*A - 1;
				c = k*B;
				for (a = 1; a <= b && c <= MAX_P; a++, b--)
				{
					done = false;
					if (cuboid(a,b,c))
					{
						cnt ++;
						if (0) printf("k: %ld  kA: %ld  kB: %ld  a: %ld  b: %ld  c: %ld  YYY\n", k, k*A, k*B, a, b, c);
					}
				}
				// or a + b > c
				c = k*A;
				a = k*B/2;
				b = k*B-a;
				for (; a <= b  && b <= c && c <= MAX_P; a--, b++)
				{
					done = false;
					if (cuboid(a,b,c))
					{
						cnt ++;
						if (0) printf("k: %ld  kA: %ld  kB: %ld  a: %ld  b: %ld  c: %ld  ZZZ\n", k, k*A, k*B, a, b, c);
					}
				}
				k++;
			}	
		}
	}
	return cnt;
}

int main()
{
	long numc = 0;
	for (long k = 3; numc < 1000000 ; k ++)
	{
		numc = cubaloids(k);
		printf("For M + %ld  count is %ld \n", k, numc);
	}
}

