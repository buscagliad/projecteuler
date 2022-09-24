#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__


inline	// returns n ^ p
long xpower(long n, long p)
{
	long rv = 1;
	while (p >= 1) { rv *= n; p--; }
	return rv;
}


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

// returns the sum of the first n natural numbers to fourth power
inline
long sump4(long n)
{
	return (6 * xpower(n, 5) + 15 * xpower(n, 4) + 10 * xpower(n, 3) - n) / 30;
}


// returns the sum of the first n natural numbers to fifth power
inline
long sump5(long n)
{
	return (2 * xpower(n, 6) + 6 * xpower(n, 5) + 5 * xpower(n, 4) - n * n) / 12;
}


// returns the sum of the first n natural numbers to sixth power
inline
long sump6(long n)
{
	return (6 * xpower(n, 7) + 21 * xpower(n, 6) + 21 * xpower(n, 5) - 7 * xpower(n, 3) + n) / 42;
}


// returns the sum of the first n natural numbers to seventh power
inline
long sump7(long n)
{
	return (3 * xpower(n, 8) + 12 * xpower(n, 7) + 14 * xpower(n, 6) - 7 * xpower(n, 4) + 2 * n * n) / 24;
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
