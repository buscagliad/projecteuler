#ifedf 

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

#endif


#include "factor.h"

void check(long n, d)
{
	long q = n / d;
	long r = n % d;
	if (

void getnqr(long n)
{
	factor f(n);
	f.out();
	
