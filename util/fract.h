#ifndef __FRACT_H__
#define __FRACT_H__

#include <iostream>
#include "factor.h"
#include "vlong.h"
#include "digit.h"

using namespace std;



class fract {
	
	friend bool operator<(const fract&, const fract&);
  	friend bool operator==(const fract&, const fract&);
  	friend bool operator!=(const fract&, const fract&);
  	friend bool operator<=(const fract&, const fract&);
  	friend bool operator>(const fract&, const fract&);
  	friend bool operator>=(const fract&, const fract&);

  	friend ostream& operator<<(ostream&, const fract&);

  	friend fract operator+(const fract&, const fract&);
  	friend fract operator-(const fract&, const fract&);
  	friend fract operator*(const fract&, const fract&);
  	friend fract operator%(const fract&, const fract&);
  	friend fract operator/(const fract&, const fract&);
	
	public:
		fract(long n, long d);
		long	reduced_numerator() {return red_numerator;};
		long	reduced_denominator(){return red_denominator;};
		long	original_numerator(){return orig_numerator;};
		long	original_denominator(){return orig_denominator;};
		void	out(bool with_original = false);

		fract operator-() const;
		fract operator*=(const fract&);
		fract operator+=(const fract&);
		fract operator/=(const fract&);
		fract operator%=(const fract&);
		
	private:
		long	orig_numerator;
		long    orig_denominator;
		long    red_numerator;
		long    red_denominator;
		long    common_factor;
		vlong_t	common_factors;
};

inline
fract::fract(long n, long d) : orig_numerator(n), orig_denominator(d)
{
	//factor nf(n);
	//factor nd(d);
	//common_factors = nf.common(nd);
	//printf("common factors: "); vl_out(common_factors);
	//long  common_factor = product(common_factors);
	long  common_factor = gcd(orig_numerator, orig_denominator);
	//common_factor = 1;
	red_numerator = orig_numerator / common_factor;
	red_denominator = orig_denominator / common_factor;
}


inline fract fract::operator*=(const fract& m)
{
	*this = *this * m;
	return *this;
}

 
inline fract fract::operator+=(const fract& m)
{
	*this = *this + m;
	return *this;
}

 inline fract fract::operator/=(const fract& m)
{
	*this = *this / m;
	return *this;
}

 
inline fract fract::operator%=(const fract& m)
{
	*this = *this % m;
	return *this;
}



//
// HELPER functions
//

void	fract::out(bool with_original)
{
	if (with_original) printf("%ld / %ld  ", orig_numerator, orig_denominator);
	printf("%ld / %ld  ", red_numerator, red_denominator);
}

//
// copy constructor - use default
//

//
// returns  a < b
// 
inline
bool operator<(const fract& a, const fract& b)
{
//
// may need to deal with signs later
//
	if ( a.red_numerator * b.red_denominator <
		 a.red_denominator * b.red_numerator ) return true;
	
	return false;
}


 
//
// returns a == b
// 
inline
bool operator==(const fract& a, const fract& b)
{
	if ( ( a.red_numerator == b.red_numerator ) && 
	     ( a.red_denominator == b.red_denominator) )
	     return true;
	return false;
}

//
// returns  a != b
// 
inline
bool operator!= (const fract& a, const fract& b)
{
	return ( !(a == b) );
} 
//
// returns  a > b
// 
inline
bool operator> (const fract& a, const fract& b)
{
	return ( !(a == b) && !(a < b) );
}

//
// returns a >= b
//
inline
bool operator>= (const fract& a, const fract& b)
{
	return (a == b) || (a > b);
}

//
// returns a <= b
//
inline
bool operator<= (const fract& a, const fract& b)
{
	return (a == b) || (a < b);
}


inline
ostream& operator<< (ostream& os, const fract& a)
{
	os << a.red_numerator << " / " << a.red_denominator;

	return os;
}
 

//
// operator+ returns a + b
//
inline
fract operator+(const fract& a, const fract& b)
{

	
	// need to find gcd between a denominator and b denominator
	// then create return franction
	//
	//  a.n      b.n      a.n * b.d + a.d * b.n
	//  ---   +  ---   =  ---------------------
	//  a.d      b.d          a.d * b.d
	//
	 // find gcd of cb+ad and bd, divide and return
	 
	 return fract(a.red_numerator * b.red_denominator + a.red_denominator * b.red_numerator, 
					a.red_denominator * b. red_denominator);

	return a;
}

//
// returns the negative of the fract object
//
inline
fract fract::operator-() const
{
	// need to find gcd between a denominator and b denominator
	// then create return franction
	return *this;
}

//
// returns a - b
// 
inline
fract operator-(const fract& a, const fract& b)
{
	return a + (-b);
}
 
//
// returns a * b
//
inline
fract operator*(const fract& a, const fract& b)
{
	return fract(a.red_numerator * b.red_numerator, 
				a.red_denominator * b. red_denominator);
}

//
// assignment operator
//

#endif
