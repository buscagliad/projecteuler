#ifndef __DIGIT_H__
#define __DIGIT_H__

inline
long	digit(long n, int d)
{
	if (d < 0) return 0;
	while ( (n > 0) && (d-- > 0) ) n /= 10;
	return n % 10;
}


#endif
