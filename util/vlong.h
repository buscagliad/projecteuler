#ifndef __V_LONG_H__
#define __V_LONG_H__

#include <vector>
#include <stdio.h>

typedef std::vector<long> vlong_t;
typedef std::vector<long>::iterator vlong_it;

class	vlong : public vlong_t {
	public:
		vlong(vlong_t &v);
		vlong();
		bool exists(long n);
		void add(long v);
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
	private:
		//vlong_t  cv;	// class value list
		
};

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
vlong::vlong()
{
}

inline
vlong::vlong(vlong_t &b)
{
	//
	for (vlong_it it = b.begin(); it != b.end(); it++)
	{
		add(*it);
	}
}

inline
void	vlong::add(long v)
{
	if (this->size() == 0){this->push_back(v); return;}
	//
	for (vlong_it it = this->begin(); it != this->end(); it++)
	{
		if (*it > v) { this->insert(it, v); return; }
	}
	this->push_back(v);
}

void vl_out(vlong_t &v)
{
	long prod = 1;
	long sum = 0;
	printf("Factors: ");
	for (size_t i = 0; i < v.size(); i++)
	{
		prod *= v[i];
		sum += v[i];
		printf(" %ld", v[i]);
	}
	printf("\nSum: %ld   Product: %ld\n", sum, prod);
}
void vlong::out()
{
	for (size_t i = 0; i < this->size(); i++)
	{
		printf(" %ld\n", (*this)[i]);
	}
}

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
