#ifndef __V_LONG_H__
#define __V_LONG_H__

#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>

#include "sequence.h"

typedef std::vector<long> vlong_t;
typedef std::vector<long>::iterator vlong_it;

class	vlong : public vlong_t {
	public:
		vlong(vlong_t &v, bool ord = true);
		vlong(bool ord = true);
		vlong(long v1, long size);
			
		bool exists(long n);
		void add(long v);
		int  find(long n);	// returns index to element containing n, -1 if not found
		long sum();
		long product();
		void out();
		long min() { return (*this)[0];};
		long max() { return (*this)[this->size()-1];};
		long median(){ return (*this)[this->size()/2];};
		//long &operator[](int i);
		int  index(long value); // return first index where cv[index] > value;
								// -1 if no such index
		vlong_it  index_it(long value); // return iterator to place where *it > value
		
		bool	  setPermutation(int n);	// sets up all permuations of n entris from this vlong
										// false is returned if n < 1 or n > size()
		vlong_t  getNextPerm();
		// return next n-touple from list set by setPermuation subsequent calls return a differnt
		//				list - until you exhaust combinations
		 
	private:
		//vlong_t  cv;	// class value list
		int	choose;	// if > -1, we are in the middle of subChoose(), it will indicate which
					// subchoose selection will be filled int
		vlong_t		*ch;
		int          ch_size;
		bool		ordered;	// if true, add will insert into ordered list
};

// if n > size() - return null list
// if n == size() = return full list
// if n < size() = return first n-touple from list, subsequent calls return a differnt
//				list - until you exhaust combinations
inline
bool	vlong::setPermutation(int n)
{
	choose = 0;
	if (ch) delete [] ch;
	if (n < 1 || n > (int)size()) return false;
	ch_size = NchooseM(size(),n);
	ch = new vlong_t[ch_size];
	long k = 0;
	// create a string with n 1's nad k 0's, where k = size() - n;
	// if k == 0, then only 1 premutation
	std::string s(n, '1');
	for (size_t i = 0; i < size() - n; i++) s += '0';
	std::sort(s.begin(), s.end());
	do {
		for (size_t j = 0; j < s.size(); j++)
		{
			if (s[j] == '1') ch[k].push_back((*this)[j]);
		}
		k++;
	} while(std::next_permutation(s.begin(), s.end()));
	if (k != ch_size)
	{
		printf("setPermutations - INTERNAL ERROR - s = %s  k = %ld  ch_size = %d\n", s.c_str(),
												k, ch_size);
		return false;
	}
	return true;
}

// return next n-touple from list set by setPermuation subsequent calls return a differnt
//				list - until you exhaust combinations
inline
vlong_t  vlong::getNextPerm()
{
	vlong_t rv;
	if (!ch) return rv;
	if (choose >= ch_size)
	{
		delete [] ch;
		ch = NULL;
		return rv;
	}
	return ch[choose++];
}

// return first index where cv[index] > value;
// -1 if no such index

inline
int  vlong::index(long value) 
{
	int	n = 0;
	for (vlong_it i = this->begin(); i != this->end(); i++, n++)
	    if (*i > value) return n;
	return -1;
}

// return first index where cv[index] == value;
// -1 if no such index

inline
int  vlong::find(long value) 
{
	int	n = 0;
	for (vlong_it i = this->begin(); i != this->end(); i++, n++)
	    if (*i == value) return n;
	return -1;
}

// return true if value exists in vector
//
inline
bool  vlong::exists(long value) 
{
	for (vlong_it i = this->begin(); i != this->end(); i++)
	    if (*i == value) return true;
	return false;
}

inline
vlong_it  vlong::index_it(long value)	
{
	for (vlong_it i = this->begin(); i != this->end(); i++)
	    if (*i > value) return i;
	return this->end();
}
								
//inline long& vlong::operator[](int i){return cv[i];};

inline
vlong::vlong(long v, long size)
{
	ordered = false;
	ch = NULL;
	while (size--) add(v);
}


inline
vlong::vlong(bool ord)
{
	ordered = ord;
	ch = NULL;
}

inline
vlong::vlong(vlong_t &b, bool ord)
{
	//
	ch = NULL;
	ordered = ord;
	for (vlong_it it = b.begin(); it != b.end(); it++)
	{
		add(*it);
	}
}

inline
void	vlong::add(long v)
{
	if (!ordered || this->size() == 0){this->push_back(v); return;}
	//
	for (vlong_it it = this->begin(); it != this->end(); it++)
	{
		if (*it > v) { this->insert(it, v); return; }
	}
	this->push_back(v);
}

inline
void vl_out(vlong_t &v)
{
	printf("Elements: ");
	for (size_t i = 0; i < v.size(); i++)
	{
		printf(" %ld", v[i]);
	}
	printf("\n");
}

inline
void vlong::out()
{
	for (size_t i = 0; i < this->size(); i++)
	{
		printf(" %ld\n", (*this)[i]);
	}
}

inline
long sum(vlong_t &v)
{
	long sumv = 0;
	for (size_t i = 0; i < v.size(); i++)
	{
		sumv += v[i];
	}
	return sumv;
}

inline
long vlong::sum()
{
	return ::sum(*this);
}

// prodf will return the product of the long vector
//
inline
long product(vlong_t &v)
{
	long p = 1;
	for (size_t i = 0; i < v.size(); i++)
	{
		p *= v[i];
	}
	return p;
}

inline
long vlong::product()
{
	return ::product(*this);
}


#endif
