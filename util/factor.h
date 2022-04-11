#ifndef __FACTOR_H__
#define __FACTOR_H__

#include <vector>
#include "prime.h"

using namespace std;

typedef struct {
	long	f;
	int		power;
} fact_val_t;

typedef vector<fact_val_t> factor_t;
typedef vector<fact_val_t>::iterator factor_it;
typedef std::vector<long> vlong_t;
typedef std::vector<long>::iterator vlong_it;

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
							if ( (facts.size() == 1) && facts[0].power == 1) return true;
							return false; };
							// returns true if original number was a prime, not
							// valid after 'merge' is used
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
// out() will output all of the factors, whether these
//       factors have been merged, and the product of the 
//       factors
//
inline
void	factor::out()
{
	printf("%s%ld = ", have_merged?"[merged]":"", product());
	printf("%ld", facts[0].f);
	if (facts[0].power > 1) printf("^%d", facts[0].power);
	for (size_t i = 1; i < facts.size(); i++)
	{
		printf(" * %ld", facts[i].f);
		if (facts[i].power > 1) printf("^%d", facts[i].power);
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
	if (p) p->power++;
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
		if (p > pn->power) pn->power = p;
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
		add_merge(f.facts[i].f, f.facts[i].power);
}
		
inline
long	factor::product()		// returns product of factors
{
	long prod = 1;
	for (size_t i = 0; i < facts.size(); i++)
		for (int j = 0; j < facts[i].power; j++)
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
