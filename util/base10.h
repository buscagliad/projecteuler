#ifndef __BASE_10_H__
#define __BASE_10_H__

#include <vector>
#include <cstring>
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
		bool	sameDigits(const base10 &v);		// returns true if v has same digits as *this
		long	map(const base10 &v);				// returns the map from this -> v (if they have
													// the same digits) returns 0 if not
		bool    canorder(const char *s);			// returns true if there is a mapping from s to base10
		long    reverse();							// reverses digits of base10 object
		bool    isPalindrome();						// returns true if number is a palindrome
		bool    isBouncy(bool &inc, bool &dec, bool &eq);		// returns true if number has digits that are both less and 
		bool    isBouncy();							// greater than the one that precedes them
		base10	digfac();							// returns sum of factorials of digits
	private:
		char	dig[21];							// dig[0] is ones digit, [1] tens,...
		int		digLen;								// number of digits in dig
		long	v;									// original value
		bool	valid;								// set to false if n <= 0
		vlong	*perm;								// used for setChoose/getNext
};

// inc is set to true if all digits are same
inline
bool    base10::isBouncy(bool &inc, bool &dec, bool &eq)							// returns true if number has digits that are both less and 
{
	inc = false;
	dec = false;
	eq = false;
	int neq = 1;
	if (digLen < 2) {
		eq = true;
		return false;
	}
	if (digLen < 3)
	{
		inc = dig[1] < dig[0];					// no bouncy numbers possible until three digits
		dec = dig[1] > dig[0];
		eq = dig[1] == dig[0];
		return false;
	}
	for (int i = 0; i < digLen - 1; i++)
	{
		int	delta = (dig[i+1] - dig[i]);
		if (delta < 0) { inc = true; }
		else if (delta > 0) { dec = true;  }
		else neq ++;
	}
	if (neq == digLen) eq = true;
	if (inc && dec)
	{
		inc = false;
		dec = false;
	}
	return (!(inc || dec || eq));
}


inline
bool    base10::isBouncy()							// returns true if number has digits that are both less and 
{
	bool inc = false;
	bool dec = false;
	bool eq = false;
	return isBouncy(inc, dec, eq);
}
	


inline
long charmap (const char *s1, const char *s2, int len)
{
	int isset[len];
	bool charfound = false;

	for (int i = 0; i < len; i++) isset[i] = -1;
	for (int i = 0; i < len; i++)
	{
		charfound = false;
		for (int j = 0; j < len; j++)
		{
			if (s1[i] == s2[j] && isset[j]<0)
			{
				isset[j] = i;
				charfound = true;
				break;
			}
		}
		if (!charfound) return 0;
	}
	long rv = 0;
	for (int i = 0; i < len; i++)
	{
		if (isset < 0) return 0;
		rv = 10*rv + isset[i];
	}
	//printf("charmap::  s1: %s  s2: %s   map: %ld\n", s1, s2, rv);
	return rv;
	
}

//
// can map looks at if there are the same pattern of repeating
// characters in s and there are repeating digits in this
//  ex:  6931604 and XWABXGD are mappable X->6, W-> 9, etc.
//  

inline
bool  base10::canorder(const char *s)
{
	if ((int)strlen(s) != digLen) return false;

	for (int i = 0; i < digLen - 1; i++)
	{
		for (int j = i + 1; j < digLen; j++)
		{
			//printf("canorder:: s[%d] = %c s[%d] = %c d[%d] = %d d[%d] = %d\n",
			//    i, s[i], j, s[j], i, dig[i], j, dig[j]);
			if ( (s[i] == s[j]) && (dig[i] != dig[j]) ) return false;
			if ( (s[i] != s[j]) && (dig[i] == dig[j]) ) return false;
		}
	}
	return true;
}

inline
bool	base10::sameDigits(const base10 &v)				// returns true if v has same digits as *this
{
	if (v.digLen != this->digLen) return false;

	std::vector<char> vdig (v.dig, v.dig+digLen);               
	std::vector<char> tdig (this->dig, this->dig+digLen);       

	// sort digits of passed in object
	std::sort (vdig.begin(), vdig.end());      

	// sort digits of this-> number
	std::sort (tdig.begin(), tdig.end()); 

	if (vdig == tdig) return true;	// if sorted arrays are equal, then they have the same digits
	return false;
}

inline
long	base10::map(const base10 &v)				// returns true if v has same digits as *this
{
	if (v.digLen != digLen) return 0;
	char s1[digLen+1];
	char s2[digLen+1];
	for (int i = 0; i < digLen; i++)
	{
		s1[digLen-i-1] = dig[i] + '0';
		s2[digLen-i-1] = v.dig[i] + '0';
	}
	s1[digLen] = 0;
	s2[digLen] = 0;
	return charmap(s1, s2, digLen);
}

static
long    DigFactors[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};


// sum each digit factorial - x = d1 d2 d3 ... dn
// return d1! + d2! + d3! + ... + dn!
inline
base10	base10::digfac()
{
	long sum = 0;
	for (int n = 0; n < digLen; n++)
	{
		sum += DigFactors[(int)dig[n]];
	}
	return base10(sum);
}	
	

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
	if (perm) delete perm;
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

// reverses a base10 objects digits
inline
long		base10::reverse()
{
	char  s;
	for (int i = 0; i < digLen/2; i++)
	{
		s = dig[digLen - i - 1];
		dig[digLen - i - 1] = dig[i];
		dig[i] = s;
	}
	return value();
}

// reverses a base10 objects digits
inline
bool		base10::isPalindrome()
{
	for (int i = 0; i < digLen/2; i++)
	{
		if (dig[digLen - i - 1] != dig[i]) return false;
	}
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
