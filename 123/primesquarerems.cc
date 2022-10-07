//
//  (pn - 1)^n + (pn + 1)^n mod pn^2
//
//  NOTE:  pn is the nth prime, i.e. p3 = 5
//			all elements of the polynomials for powers >= 2 
//			are 0 mod p^2, so we
//         only need to look at the first power of pn and the constant
//	Below, p is pn
//
//
//     n * p * (-1)^(n-1) + (-1)^n     +     n * p + 1
//
//   For n odd:
//       ( n * p * - 1     +   (n * p + 1 ) mod p^2
//			==>    2 * p * n  mod p^2
//
//   For n even:
//       ( n * p * (-1) + 1   +   n * p + 1 ) mod p^2
//          ==>   2 mod p^2
//
//
//   Find the least value n such that the remainder first exceeds 10^10
//
//	 we know it is an odd value of n - so we only need to consider
//   p(2j+1)
//        

#include <cstdio>
#include "prime.h"

Prime p;	// will read in first million primes
			// note: prime_list is the list of the first 10^6 primes,
			// indexed at 0 - so p1 = prime_list[0], p5 = prime_list[4]

long rem(long n)
{
	long  pn = prime_list[n-1];
	return 2 * n * pn % (pn * pn);
}

long psqrem(long n)
{
	long rm = rem(n);
	printf("p(%ld) = %ld, rem: %ld\n", n, prime_list[n-1], rm);
	return rm;
}

void findn(long n)
{
	while (psqrem(n) < 10000000000l) n+=2;
}

int main()
{
	psqrem(3);
	psqrem(7037);
	findn(7039);
	
}
