//
//  (a - 1)^n + (a + 1)^n mod a^2
//
//  NOTE:  all elements of the polynomials for powers >= 2 are 0 mod a^2, so we
//         only need to look at the first power of a and the constant
//
//
//   (n+1) * a * (-1)^(n-1) + (-1)^n     +   (n + 1) * a + 1
//
//   For n odd:
//       ( (n+1) * a * - 1     +   (n + 1) * a + 1 ) mod a^2
//			==>    2 * a * (n + 1) mod a^2
//
//   For n even:
//       ( (n+1) * a * (-1) + 1     +   (n + 1) * a + 1 ) mod a^2
//          ==>   2 mod a^2
//
//
//   Given a, find the largest value n such that
//            2 a (n + 1) < a ^ 2     or
//            2 (n + 1) < a
//            n < a / 2 - 1
//            maxn = a / 2       for a odd
//            maxn = a / 2 - 1   for a even
//            rmax = 2 * a * (maxn + 1)

#include <cstdio>

int rmax(int a)
{
	int maxn = a / 2;
	if ( a % 2 == 0) maxn--;
	return 2 * a * (maxn);
}

int main()
{
	int  a = 7;
	printf("a: %d  rmax: %d\n", a, rmax(a));
	int  rmsum = 0;
	
	for (a = 3; a <= 1000; a++) rmsum += rmax(a);
	printf("sum of all rmax for a = 3 to 1000 is %d\n", rmsum);
}
