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

#endif
