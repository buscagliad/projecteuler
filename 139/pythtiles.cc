#ifdef PROBLEM_DESCRIPTION


Let (a, b, c) represent the three sides of a right angle triangle with integral length sides. 
It is possible to place four such triangles together to form a square with length c.

For example, (3, 4, 5) triangles can be placed together to form a 5 by 5 square with a 1 by 1 hole 
in the middle and it can be seen that the 5 by 5 square can be tiled with twenty-five 1 by 1 squares.

However, if (5, 12, 13) triangles were used then the hole would measure 7 by 7 and these could not 
be used to tile the 13 by 13 square.

Given that the perimeter of the right triangle is less than one-hundred million, how many 
Pythagorean triangles would allow such a tiling to take place?

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

#define MAX_P 100000000l


int main()
{
	//memset(v, 0, (MAX_P+1)*sizeof(long));
	long a, b, c;
	long pt = 0;
	long count = 0;	
#define PRINT printf("(a,b,c) = {%ld,%ld,%ld)\n", a, b, c);
	for (long n = 1; n <= 2*MAX_P; n++)
	{
		for (long m = n + 1; m <= 2*MAX_P; m+=2) // m > n
		{
			pt = generatePythTriple(m, n, a, b, c);
			if (pt > MAX_P) break;
			if (b - a == 1) { count += MAX_P / (a + b + c); 
				PRINT;
			}
			else if ( (b - a ) / c * c == b - a) { count += MAX_P / (a + b + c);
				PRINT;
			}
		}
		pt = 0;
	}

	printf("Number of singular right triagles (<= %ld) is %ld\n", MAX_P, count);
	
}

