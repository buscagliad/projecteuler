#ifndef __V_DOUBLE_H__
#define __V_DOUBLE_H__

#include <vector>
#include <math.h>
#include <cstdio>

typedef std::vector<double> vdouble_t;
typedef std::vector<double>::iterator vdouble_it;

class	vdouble : public vdouble_t {
	public:
		vdouble(vdouble_t &v);
		vdouble(double e = 0.0);
		bool exists(double n);
		bool add(double v);
		double sum();
		double product();
		void out();
		double min() { return (*this)[0];};
		double max() { return (*this)[this->size()-1];};
		double median(){ return (*this)[this->size()/2];};
		//double &operator[](int i);
		int  index(double value); // return first index where cv[index] > value;
								// -1 if no such index
		vdouble_it  index_it(double value); // return iterator to place where *it > value
	private:
		double epsilon;
		
};

inline
bool	equals(double a, double b, double e)
{
	if (fabs(a-b) <= e) return true;
	return false;
}

// return first index where cv[index] > value;
// -1 if no such index

inline
int  vdouble::index(double value) 
{
	int	n = 0;
	for (vdouble_it i = this->begin(); i != this->end(); i++, n++)
	    if (*i > value) return n;
	return -1;
}

// return true if value exists in vector
//
inline
bool  vdouble::exists(double value) 
{
	for (vdouble_it i = this->begin(); i != this->end(); i++)
	    if (equals(*i, value, epsilon)) return true;
	return false;
}

inline
vdouble_it  vdouble::index_it(double value)	
{
	for (vdouble_it i = this->begin(); i != this->end(); i++)
	    if (*i > value) return i;
	return this->end();
}
								
//inline double& vdouble::operator[](int i){return cv[i];};

inline
vdouble::vdouble(double e)
{
	epsilon = e;
}

inline
vdouble::vdouble(vdouble_t &b)
{
	//
	for (vdouble_it it = b.begin(); it != b.end(); it++)
	{
		add(*it);
	}
}

inline
bool	vdouble::add(double v)
{
	if (this->size() == 0){this->push_back(v); return true;}
	//
	if (exists(v)) return false;
	for (vdouble_it it = this->begin(); it != this->end(); it++)
	{
		if (*it > v) { this->insert(it, v); return true; }
	}
	this->push_back(v);
	return true;
}



void vdouble::out()
{
	for (size_t i = 0; i < this->size(); i++)
	{
		printf(" %f\n", (*this)[i]);
	}
}

double sum(vdouble_t &v)
{
	double sumv = 0;
	for (size_t i = 0; i < v.size(); i++)
	{
		sumv += v[i];
	}
	return sumv;
}

inline
double vdouble::sum()
{
	return ::sum(*this);
}

#endif
