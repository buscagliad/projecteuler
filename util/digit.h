#ifndef __DIGIT_H__
#define __DIGIT_H__

#include <math.h>
#include <algorithm>

#include "vlong.h"

#define DIGIT_DEBUG 0

inline
long	digit(long n, int d)
{
	if (d < 0) return 0;
	while ( (n > 0) && (d-- > 0) ) n /= 10;
	return n % 10;
}

inline
bool isSquare(long n)
{
	double sn = sqrt((double) n) + 0.2;
	long   x = sn;
	if (x * x == n) return true;
	return false;
}

inline
bool isSquare(long n, long &sqrtn)
{
	double sn = sqrt((double) n) + 0.2;
	sqrtn = sn;
	if (sqrtn * sqrtn == n) return true;
	return false;
}

inline
long retSquare(long n)
{
	double sn = sqrt((double) n) + 0.2;
	long   x = sn;
	if (x * x == n) return sn;
	return -1;
}

inline
bool	isDigInNum(long n, int d)
{
	if (d < 0) return 0;
	while (n > 0){
		if (d == n%10) return true;
		n /= 10;
	}
	return false;
}

inline
vlong_t	getDigits(long n, long base = 10)
{
	vlong_t v;
	while ( (n > 0) )
	{
		v.push_back(n%base);
		n /= base;
	}
	return v;
}

inline
bool	isPermutation(long a, long b)	// returns true if a and b are permuations
{										// of one another
	vlong_t	va = getDigits(a);
	vlong_t vb = getDigits(b);
	bool do_return = true;

	if (va.size() != vb.size()) { return false; }
	for (size_t i = 0; i < va.size(); i++)
	{
		do_return = true;
		for (size_t j = 0; j < vb.size(); j++)
		{
			if (vb[j] == va[i]) {
				vb[j] = 10;	// not a valid digit
				do_return = false;
				break;		// go to next va value
			}
		}
		if (do_return) return false;	// if we get here, nothing match va[i]
	}
	return true;		// if we get here - all digits matched
}


inline
bool	repeatDigits(long a)	// returns true if a has a repeat digit
{								// false indicates no repeats (0 - 9)
	vlong_t	va = getDigits(a);

	for (size_t i = 0; i < va.size() - 1; i++)
	{
		for (size_t j = i + 1; j < va.size(); j++)
		{
			if (va[j] == va[i]) {
				return true;
			}
		}
	}
	return false;		// if we get here - no digits matched
}

inline
bool	isPalindrome(vlong_t &v)
{
	size_t	vs = v.size();
	size_t	vsd2 = vs/2;
	for (size_t k = 0; k < vsd2; k++)
	    if (v[k] != v[vs-1-k]) return false;
	return true;
}

int gcd(int x, int y)
{
    while (y > 0)
    {
        x %= y;
        std::swap(x, y);
    }
    return x;
}

#define MAXTENDIGIT     9999999999l
#define MINTENDIGIT     1000000000l
#define MAXNINEDIGIT     999999999l
#define MINNINEDIGIT     100000000l
//                       123456789

inline
bool	isPandigital(long t, bool include_zero = false)
{
	if ( include_zero && ( (t < MINTENDIGIT)  || (t > MAXTENDIGIT) ) ) return false;
	if (!include_zero && ( (t < MINNINEDIGIT) || (t > MAXNINEDIGIT) ) ) return false;
	vlong v;
	while ( (t > 0) )
	{
		long d = t % 10;
		if (!include_zero && d == 0) { 
			if (DIGIT_DEBUG) printf("Found a zero\n"); 
			return false; 
		}
		if (v.exists(d)) { 
			if (DIGIT_DEBUG) printf("%ld is a duplicate digit\n", d); 
			return false;
		}
		v.add(d);
		t /= 10;
	}
	return true;	
}

#endif
