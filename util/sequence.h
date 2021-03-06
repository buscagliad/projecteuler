#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

// returns the sum of the first n natural numbers
inline
long sumint(long n)
{
	return n * (n + 1) / 2;
}

// returns the sum of the first n natural numbers squared
inline
long sumsq(long n)
{
	return n * (n + 1) * ( 2 * n + 1) / 6;
}

// returns the sum of the first n natural numbers cubed
inline
long sumcu(long n)
{
	return n * n * (n + 1) *(n + 1) / 4;
}

// returns n * (n-1) * (n-2) * ... * 2 * 1
inline
long  fact(long n)
{
	long rv = 1;
	while (n > 1) rv *= n--;
	return rv;
}

// returns number of ways of choosing m things from a set of n items
inline
long	NchooseM(long n, long m)
{
    if (m == 0) return 1;
    return (n * NchooseM(n - 1, m - 1)) / m;
}
#endif
