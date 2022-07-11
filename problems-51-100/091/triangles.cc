#ifdef PROBLEM_DESCRIPTION


The points P (x1, y1) and Q (x2, y2) are plotted at integer co-ordinates and are joined to the origin, O(0,0), to form ΔOPQ.

There are exactly fourteen triangles containing a right angle that can be formed when each co-ordinate lies between 0 and 2 inclusive; that is,
0 ≤ x1, y1, x2, y2 ≤ 2.

Given that 0 ≤ x1, y1, x2, y2 ≤ 50, how many right triangles can be formed?


Two types of right triangles, 1 with the right angle at the origin:   (a, 0), (0, b), (0, 0)
And right triangles with the right angle interior to the grid:   (a, b)  (c, d), (0, 0)

For type 1:  there are N^2 ways of creating those triangles, where NxN is the grid size.

For type 2:  using pythagorean`s theorem, the relationship between a, b, c and d for a right triangle must be
             (assuming the right angle is at (a, b))  (NOTE: whatever number we get, we`ll double it by symmetry
             and assuming (c,d) contains the right angle)
             a^2 + b^2 = ac + bd (1)
             
             Process:  for each (a, b) a: 1..N, b: 1..N
                 compute a^2 + b^2 and find all c, d s.t equation (1) holds

#endif

#include <cstdio>


int  raw(int N)
{
	int a, b, c, d;
	int cnt = 0;
	for (a = 0; a <= N; a++)
	{
		for (b = 0; b <= N; b++)
		{
			if ( (a == 0) && (b == 0) ) continue;
			int s1 = a*a + b*b;
			for (c = 0; c <= N; c++)
			{
				for (d = 0; d <= N; d++)
				{
					if ( (c == 0) && (d == 0) ) continue;
					if ( (a == c) && (b == d) ) continue;
					int s2 = c*c + d*d;
					int s3 = (c - a) * (c - a) + (b - d) * (b - d);
					if (s1 + s2 == s3) cnt++;
					else if (s1 + s3 == s2) cnt++;
					else if (s3 + s2 == s1) cnt++;
				}
			}
		}
	}
	return cnt/2; // we have counted twice
}

int main()
{
	printf("2 x 2 grid has %d right triangles\n", raw(2));
	printf("50 x 50 grid has %d right triangles\n", raw(50));
}
