#ifdef PROBLEM_DESCRIPTION

Almost equilateral triangles


  [Show HTML problem content]  
Problem 94

It is easily proved that no equilateral triangle exists with integral length sides and integral area. However, the almost equilateral triangle 5-5-6 has an area of 12 square units.

We shall define an almost equilateral triangle to be a triangle for which two sides are equal and the third differs by no more than one unit.

Find the sum of the perimeters of all almost equilateral triangles with integral side lengths and area and whose perimeters do not exceed one billion (1,000,000,000).

#endif

#include <cstdio>

#include "digit.h"

long persum = 0;

bool isEqu(long A)
{
	//double f = (A - 1) / 4.0;
	bool rv = false;
	long rm1 = (3 * A - 1)*(A + 1);
	long rp1 = (3 * A + 1)*(A - 1);
	long sq1, sq2;
	if (isSquare(rm1, sq1))
	{
		persum += 3 * A - 1;
		rv = true;
	}	
	if (isSquare(rp1, sq2))
	{
		persum += 3 * A + 1;
		rv = true;
	}
	return rv;
}

int main()
{
	for (long A = 3; ; A++)
	{
		if (3*A > 1000000000) break;
	    isEqu(A);
	}
	printf("PerSum = %ld\n", persum);
}

	
