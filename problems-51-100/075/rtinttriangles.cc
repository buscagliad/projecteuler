#ifdef PROBLEM_DESCRIPTION

Singular integer right triangles

Problem 75

It turns out that 12 cm is the smallest length of wire that can be bent to form an integer sided right angle triangle in exactly one way, but there are many more examples.

12 cm: (3,4,5)
24 cm: (6,8,10)
30 cm: (5,12,13)
36 cm: (9,12,15)
40 cm: (8,15,17)
48 cm: (12,16,20)

In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer sided right angle triangle, and other lengths allow more than one solution to be found; for example, using 120 cm it is possible to form exactly three different integer sided right angle triangles.

120 cm: (30,40,50), (20,48,52), (24,45,51)

Given that L is the length of the wire, for how many values of L ≤ 1,500,000 can exactly one integer sided right angle triangle be formed?
#endif

#include "utils.h"
#include "digit.h"
#include <algorithm>



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

#define MAX_P 1500000l
typedef struct {
	long  a, b, c;
	long  count;  // if > 1, not a unique triple
} pythags;

pythags pyTrips[MAX_P+1];

void	init()
{
	for (long i = 0; i < MAX_P + 1; i++) pyTrips[i].count = 0;
}


int main()
{
	//memset(v, 0, (MAX_P+1)*sizeof(long));
	init();
	long a, b, c;
	long pt = 0;
	for (long n = 1; n <= 2*MAX_P; n++)
	{
		for (long m = n + 1; m <= 2*MAX_P; m+=2) // m > n
		{
			pt = generatePythTriple(m, n, a, b, c);
			if (pt > MAX_P) break;
			if (gcd(m,n) != 1) continue;
			pyTrips[pt].count++;
			pyTrips[pt].a = a;
			pyTrips[pt].b = b;
			pyTrips[pt].c = c;
			long k = 2;
			while (k * pt <= MAX_P)
			{
				pyTrips[k*pt].count++;
				if (pyTrips[k*pt].count == 1)
				{
					pyTrips[k*pt].a = a;
					pyTrips[k*pt].b = b;
					pyTrips[k*pt].c = c;
				}
				k++;
			}	
		}
		pt = 0;
	}
	#ifdef DONT_SKIP
	//
	//  check for k(a+b+c) pyTrips
	for (long i = 0; i<=MAX_P; i++)
	{
		if (pyTrips[i].count==1)
		{
			for (long k = 2; k <= MAX_P; k++)
			{
				long index = k * i;
				if (index > MAX_P) break;
				if (pyTrips[index].count == 0)
				{
					pyTrips[index].a = pyTrips[i].a * k;
					pyTrips[index].b = pyTrips[i].b * k;
					pyTrips[index].c = pyTrips[i].c * k;
				}
				pyTrips[index].count--;	// indicates it was a multiple of a 
			}
		}
	}
	#endif
	// find single pythagoran lenghts :
	long count = 0;
	for (long i = 0; i<=MAX_P; i++)
	{
		if (pyTrips[i].count == 1) {
		    printf("Length: %7ld   Number: %ld  (%ld, %ld, %ld)\n", i, 
				pyTrips[i].count, pyTrips[i].a, pyTrips[i].b,pyTrips[i].c);
			count++; 
		}
		else if (pyTrips[i].count == -1) {
		    printf("Length: %7ld  *Number: %ld  (%ld, %ld, %ld)\n", i, 
				-pyTrips[i].count, pyTrips[i].a, pyTrips[i].b,pyTrips[i].c);
			count++; 
		}
		//if (pyTrips[i].count > 0)
		//    printf("Length: %ld   Number: %ld\n", i, pyTrips[i].count);
	}
	printf("Number of singular right triagles (<= %ld) is %ld\n", MAX_P, count);
	
}

