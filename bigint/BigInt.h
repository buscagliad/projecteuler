//
// File: BigInt.h
//
// Description:
//	This file declares the methods of the class BigInt.  This
//	class provides the user with infinite precision integer
//	arithmetic.
//
// Author: Dave Buscaglia	Nov 1, 1997
//	
//

#ifndef BIGINT_H
#define BIGINT_H

#include <iostream.h>
#include <stdlib.h>
#include <ctype.h>

class BigInt
{
  	friend bool absLess(const BigInt& a, const BigInt& b);
  	friend bool absEqual(const BigInt& a, const BigInt& b);

  	friend BigInt absSum(const BigInt& a, const BigInt& b);
  	friend BigInt absDiff(const BigInt& a, const BigInt& b);
  	
  	friend bool operator<(const BigInt&, const BigInt&);
  	friend bool operator==(const BigInt&, const BigInt&);
  	friend bool operator<=(const BigInt&, const BigInt&);
  	friend bool operator>(const BigInt&, const BigInt&);
  	friend bool operator>=(const BigInt&, const BigInt&);

  	friend ostream& operator<<(ostream&, const BigInt&);

  	friend BigInt operator+(const BigInt&, const BigInt&);
  	friend BigInt operator-(const BigInt&, const BigInt&);
  	friend BigInt operator*(const BigInt&, const BigInt&);

    public:
 
   	BigInt(char*);
  	BigInt(int = 0);
  	BigInt(const BigInt&);
  	const BigInt& operator=(const BigInt&);
  	
  	~BigInt();
  
  	BigInt& operator++();
  	BigInt operator++(int);
  	BigInt& operator--();
  	BigInt operator--(int);
  	BigInt operator-() const;
  	BigInt operator^(const BigInt&) const;
  	BigInt operator!() const;
  	inline BigInt operator*=(const BigInt&);
  	inline BigInt operator+=(const BigInt&);
  	
	enum OutputStyle {OS_Normal, OS_Space, 
		OS_Comma, OS_Period, OS_Underscore};
	enum SignStyle {SS_Normal, SS_ShowPlus};
	
  	static	void setOutputStyle(OutputStyle);
        static	void setSignStyle(SignStyle);
        
    private:
    
	int	operator()(int) const;
	int&	operator()(int);
	void	fix();
	void	newLength(int);
	void	zero();

  	enum 	Sign { Positive, Negative, Zero };
  	int	length;
  	Sign 	sign;
  	int* 	data;
  	
  	static	OutputStyle	BI_OutputStyle;
  	static	SignStyle	BI_SignStyle;
};
 
 

inline BigInt BigInt::operator*=(const BigInt& m)
{
	*this = *this * m;
	return *this;
}

 
inline BigInt BigInt::operator+=(const BigInt& m)
{
	*this = *this + m;
	return *this;
}

 
#endif
