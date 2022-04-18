#ifndef __FACTOR_H__
#define __FACTOR_H__

#include <vector>
#include "prime.h"

using namespace std;

typedef struct {
	long	f;
	int		dup;
} fact_val_t;

typedef vector<fact_val_t> factor_t;
typedef vector<fact_val_t>::iterator factor_it;
typedef std::vector<long> vlong_t;
typedef std::vector<long>::iterator vlong_it;

class	vlong : public vlong_t {
	public:
		vlong(vlong_t &v);
		vlong();
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

//
// three key methods in this class file (no library, all inline)
//
// factor(number);
// 		number is ANY number for which prime factorization is required
// 		factor_t is a vector list of factors
//
// product - this method will return the product of the factor_t vector (should be 'number')
// 			unless a merge has occured.
//
// isPrime - this method will return true if 'number' is a prime - this call will always be 
// 			 false after a merge
//
// merge - this method will combine factors from the passed in argument with 
//         the existing factors, only combining if prime factor does not exist - or -
//         or it has more powers of a factor

class factor {
	public:
		factor(long n);
		void	merge(long n);  // adds new factors 
		void	merge(factor &f);  // adds new factors 
		long	product();		// returns product of factors
		void	out();	// print factors
		bool	isPrime() {if (have_merged) return false;
							if ( (facts.size() == 1) && facts[0].dup == 1) return true;
							return false; };
							// returns true if original number was a prime, not
							// valid after 'merge' is used
		long	num();	// returns number of factors
		vlong_t divisors(bool proper = true);
	private:
		factor();
		fact_val_t	*find(long n);	// returns NULL if n does not exist as a factor
		void	add(long n);
		void	add_merge(long n, int p);
		factor_t	facts;
		bool	have_merged;
		long	orig_number;
};

//
// returns number of divisors of the given number
inline
long   factor::num()
{
	long nf = 1;
	for (size_t i = 0; i < facts.size(); i++)
	{
		nf *= (facts[i].dup + 1);
	}
	return nf;
}

long xpower(long n, long p)
{
	long rv = 1;
	while (p >= 1) { rv *= n; p--; }
	return rv;
}

//
// uadd adds a number to a vlong_t ONLY if it does not currently exist
//
bool	addu(vlong_t &v, long value)
{
	for (size_t i = 0; i < v.size(); i++)
		if (v[i] == value) return false;
	v.push_back(value);
	return true;
}

//
// return all divisors of the given number
// find all prime factors (including powers) and put them in an array
// if there are N such numbers, then there are 2^N possible divisors
vlong_t	factor::divisors(bool proper)
{
	// prime factors need to account for multiple powers
	// when deriving all common divisors, a mutliple prime can
	// only have one of its powers used for any given divisor
	vlong_t pf;
	for (size_t i = 0; i < facts.size(); i++)
	{
		long nf = facts[i].f;
		//printf("Adding value %ld\n", nf);
		pf.push_back(nf);
		for (int j = 1; j < facts[i].dup; j++)
		{
		    pf.push_back(nf);
		    //printf("Adding value %ld\n", nf);
		}
	}
	long numsets = xpower(2, pf.size());
	//printf("Number of sets: %ld (%ld)\n", numsets, pf.size());
	vlong_t rvl;
	//rvl.push_back(1);
	if (proper) numsets--;	// don't include last product if proper divisors
	for (long i = 0; i < numsets; i++)
	{
		long new_factor = 1;
		unsigned long j = i;
		int index = 0;
		//printf("i: %ld   j: %ld\n", i, j);
		while (j != 0)
		{
			if (j & 0x1){
				new_factor *= pf[index];
				//printf("   j: %ld  index: %d  pf: %ld\n", j, index, pf[index]); 
			}
			index++;
			j>>=1;
		}
		addu(rvl, new_factor);
	}
	return rvl;
}
	

//
// out() will output all of the factors, whether these
//       factors have been merged, and the product of the 
//       factors
//
inline
void	factor::out()
{
	printf("%s%ld = ", have_merged?"[merged]":"", product());
	printf("%ld", facts[0].f);
	if (facts[0].dup > 1) printf("^%d", facts[0].dup);
	for (size_t i = 1; i < facts.size(); i++)
	{
		printf(" * %ld", facts[i].f);
		if (facts[i].dup > 1) printf("^%d", facts[i].dup);
	}
	printf("\n");
}

//
// this add is used during prime factorization,
// each factor is added, and if a multiple factor is
// encountered, the power counter is incremented.
inline	
void	factor::add(long n)
{
	fact_val_t	*p = find(n);
	if (p) p->dup++;
	else
	{
		fact_val_t t = {n, 1};
		facts.push_back(t);
	}
}

// compute product of the factors
inline
fact_val_t	*factor::find(long n)
{
	for (factor_it it = facts.begin(); it != facts.end(); it++)
		if ((*it).f == n) return &(*it);
	return NULL;
}

//
// this add (add_merge) is used during merging operations
// new factors are added, and if a multiple factor is
// encountered, if the power (p) is greater than the existing
// factor's power, power is replaced by p, otherwise nothing
// happens.
inline	
void	factor::add_merge(long n, int p)
{
	fact_val_t	*pn = find(n);
	if (pn) {
		if (p > pn->dup) pn->dup = p;
	}
	else
	{
		fact_val_t t = {n, p};
		facts.push_back(t);
	}
}
	

inline
factor::factor(long n)
{
	vector<long> fac;
	prime_factor(n, fac);
	for (vlong_it it = fac.begin(); it != fac.end(); it++)
		add((*it));
	have_merged = false;
	orig_number = n;
}
	
inline
void	factor::merge(long n)
{
	factor fn(n);
	merge(fn);
}
	
inline
void	factor::merge(factor &f)
{
	have_merged = true;
	for (size_t i = 0; i < f.facts.size(); i++)
		add_merge(f.facts[i].f, f.facts[i].dup);
}
		
inline
long	factor::product()		// returns product of factors
{
	long prod = 1;
	for (size_t i = 0; i < facts.size(); i++)
		for (int j = 0; j < facts[i].dup; j++)
			prod *= facts[i].f;
	// test
	if (!have_merged)
	{
		if (prod != orig_number)
		{
			printf("INTERNAL ERROR - prod: %ld  not equal to   orig: %ld\n",
				prod, orig_number);
		}
	}
	return prod;
}

#endif
