#ifndef __BASE_10_H__
#define __BASE_10_H__

#include <vector>
#include "sequence.h"
#include "vlong.h"


class base10 {
	public:
		typedef	vlong_t base10i;
		base10(long n);
		~base10();
		bool	unique(); 							// returns true if n has unique digits
		long	reset();							// resets to original number
		long	setDigit(int digit, int dvalue);	// replaces the digit with dvalue
													// and returns new value
		int		cdigits(int dvalue, base10i	&i);	// returns number of digs with dvalue
													// i is index to all of these digits
		long	sdigits(int dvalue, base10i &i);	// set digits reference by i to dvalue
													// and returns new value
		bool	setChoose(base10i	&i, int n);		// creates all combinations of n digit places
													// from the index set i (false is returned if
													// n > i.size() or n < 1
		base10i getNext();							// gets next choice of digit places
													// returns empty base10i object upon completion
		long	value();							// returns value
		int		count(int dv);						// returns number of digits having dv
		int		dvalue(int d);						// returns d-th digit - 0 is ones, etc.
	private:
		char	dig[21];							// dig[0] is ones digit, [1] tens,...
		int		digLen;								// number of digits in dig
		long	v;									// original value
		bool	valid;								// set to false if n <= 0
		vlong	*perm;								// used for setChoose/getNext
};

inline
long	base10::reset()
{
	long n = v;
	digLen = 0;
	while (n > 0)
	{
		dig[digLen++] = n % 10;
		n /= 10;
	}
	return v;
}	

inline
base10::base10(long n) 
{
	v = n;
	valid = (n > 0);
	perm = NULL;
	reset();
}

inline
base10::~base10()
{
	//if (perm) delete perm;
}

inline
bool	base10::unique()
{
	if (digLen > 10) return false;
	for (int i = 0; i < digLen - 1; i++)
		for (int j = i + 1; j < digLen; j++)
		    if (dig[i] == dig[j]) return false;
	return true;
}

// returns number of digits with the value 'dvalue'
// and puts their indexes into 'd'
inline
int		base10::cdigits(int dvalue, base10i &d)
{
	d.clear();
	if (digLen > 10) return false;
	for (int i = 0; i < digLen; i++)
		if (dig[i] == dvalue) d.push_back(i);
	return d.size();
}
//
// need base10i to have a select(n) which when repeatedly
// called will return a NEW order of the array
//
inline
long	base10::sdigits(int dvalue, base10i &d)
{
	if (d.size() == 0) return v;
	for (size_t i = 0; i < d.size(); i++)
		dig[d[i]] = dvalue;
	return value();
}

inline
long	base10::setDigit(int digit, int dvalue)
{
	if (digit < 0 || digit >= digLen) return v;
	dig[digit] = dvalue;
	return value();
}

inline
long	base10::value()
{
	long p10 = 1;
	long rv = 0;
	for (int i = 0; i < digLen; i++)
	{
		rv += p10 * dig[i];
		p10 *= 10;
	}
	return rv;
}

inline	
int		base10::count(int dv)						// returns number of digits having dv
{
	int c = 0;
	for (int i = 0; i < digLen - 1; i++)
		if (dig[i] == dv) c++;
	return c;
}

	

inline
int		base10::dvalue(int d)						// returns d-th digit - 0 is ones, etc.
{
	if (d < 0 || d >= digLen) return 0;
	return dig[d];
}

// creates all combinations of n digit places
// from the index set i (false is returned if
// n > i.size() or n < 1
inline
bool	base10::setChoose(base10i	&i, int n)
{
	if (perm) delete perm;
	perm = new vlong(i);
	return perm->setPermutation(n);
}
	
// gets next choice of digit places
// returns empty base10i object upon completion
inline
base10::base10i base10::getNext()
{
	if (!perm) return base10i();
	return perm->getNextPerm();
}



#endif
