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

#include <iostream>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

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
  	friend BigInt operator%(const BigInt&, const BigInt&);
  	friend BigInt operator/(const BigInt&, const BigInt&);
	friend BigInt avg(BigInt &a, BigInt &b);
	friend	bool    divide_unsigned(const BigInt& N, const BigInt& D,
				BigInt &Q, BigInt &R);

    public:
 
		BigInt(const char*);
		BigInt(long = 0);
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
		inline BigInt operator/=(const BigInt&);
		inline BigInt operator%=(const BigInt&);
		int num_digits() { return length; };
		int get_digit(int n) { if (n < 0 || n >= length) return 0; return data[n]; };

		enum OutputStyle {OS_Normal, OS_Space, 
			OS_Comma, OS_Period, OS_Underscore};
		enum SignStyle {SS_Normal, SS_ShowPlus};
		
		static	void setOutputStyle(OutputStyle);
			static	void setSignStyle(SignStyle);
			
    private:
    
		int		operator()(int) const;
		int&	operator()(int);
		void	fix();
		void	newLength(int);
		void	zero();

		enum 	Sign { Positive, Negative, Zero };
		int* 	data;
		int		length;
		Sign 	sign;
		
		static	OutputStyle	BI_OutputStyle;
		static	SignStyle	BI_SignStyle;
};

inline
BigInt	avg(BigInt &a, BigInt &b)
{
	BigInt	ans = a + b;
	int carry = 0;
	bool fd1 = (ans.data[ans.length - 1] == 1);
	for (int i = ans.length - 1; i >= 0; i--)
	{
		if (ans.data[i] % 2) { carry = 10; ans.data[i]--; }
		else carry = 0;
		if (i) ans.data[i-1] += carry;
		ans.data[i] /= 2;
	}
	if (fd1) ans.length--;
	return ans;
}

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

 inline BigInt BigInt::operator/=(const BigInt& m)
{
	*this = *this / m;
	return *this;
}

 
inline BigInt BigInt::operator%=(const BigInt& m)
{
	*this = *this % m;
	return *this;
}



//
// static member data
//
	BigInt::OutputStyle	BigInt::BI_OutputStyle = BigInt::OS_Normal;
	BigInt::SignStyle	BigInt::BI_SignStyle = BigInt::SS_Normal;
//
// static functions
//
inline
void	BigInt::setOutputStyle(OutputStyle os)
{
	BI_OutputStyle = os;
}

inline
void	BigInt::setSignStyle(SignStyle ss)
{
	BI_SignStyle = ss;
}


//
// HELPER functions
//

//
// returns nth digit of BigInt, 0 if digit is invalid
//
inline
int	BigInt::operator()(int base_ten_digit) const
{
	if ( (base_ten_digit < 0) || (base_ten_digit >= length) ) 
	    return 0;
	return data[base_ten_digit];
}

//
// in this version, we are returning access to the data structure,
// we throw the exception InternalError
//
inline
int&	BigInt::operator()(int base_ten_digit)
{
	if ( (base_ten_digit < 0) || (base_ten_digit >= length) )
	{
	    cerr << "INTERNAL ERROR - access out of bounds\n";
	    exit(0);
	}
	
	return data[base_ten_digit];
}

//
// fix removes leading zeroes and sets sign if appropriate
//
inline
void	BigInt::fix()
{
	// internal check for length
	if (length < 1)
	{
	    cerr << "Internal ERROR - fix detected non-positive length\n";
	    exit (1);
	}

	// check for 0 element
	if (length == 1)
	{
	    if (data[0] == 0)
	        sign = BigInt::Zero;
	    return;
	}

	// remove leading zeros
	while ( length > 1 && (data[length-1] == 0) ) length--;
	
	if ( (length == 1) && (data[0] == 0) ) sign = BigInt::Zero;

}


//
// newLength will delete old data and assign a new array of specified length
//
inline
void	BigInt::newLength(int l)
{	
	if (l < 1)
	{
	    cerr << "Internal ERROR - request for length < 1\n";
	    exit (1);
	}

	if (data)
	{
// cout << "Nl DEL Data @ " << (void *)data << "  Size = " << length << "\n";
	    delete [] data;
	}
	length = l;
	data = new int[length];
// cout << "Nl NEW Data @ " << (void *)data << "  Size = " << length << "\n";

}

//
// zero will set all digits equal to 0
//
inline
void	BigInt::zero()
{	
	for (int i = 0; i < length; i++) data[i] = 0;
}

//
// constructor from int to BigInt
// 
inline
BigInt::BigInt(long i) : data(0), length(0)
{
	if ( i > 0 )
  	{
	    sign = BigInt::Positive;
	}
	else if ( i < 0 )
	{
	    sign = BigInt::Negative;
	    i = -i;
	}
	else	// special case for 0
	    sign = BigInt::Zero;
	    
//
// determine length required to store number
//
	long tmp_i = i;

	while ( tmp_i )
	{
	    length++;
	    tmp_i /= 10;
	}

//
// if length == 0, set length to 1 to hold the single digit of zero
// 
	if (length == 0) length = 1;
	
	data = new int[length];	// set data to point to array
// cout << "Ci NEW Data @ " << (void *)data << "  Size = " << length << "\n";

	for(int m = 0; m < length; m++)
	{
	    data[m] = i % 10;
	    i /= 10;
	}
}


//
// create a BigInt from a string of character digits, allow for 
// a leading + or -  and terminates at null or non-digit.
//
inline
BigInt::BigInt(const char *s) : data(0), length(0)
{
	const char* ptr = s;

	
	// skip leading +/- and set sign
	if ( ptr[0] == '+' || ptr[0] == '-' )
	{
	    sign = (ptr[0]=='-') ? BigInt::Negative :  BigInt::Positive ;
	    ptr++;
	}
	else 
	    sign = BigInt::Positive;
	    
// determine length
	int	non_zero_digit_count = 0;
	while(isdigit(ptr[non_zero_digit_count])) non_zero_digit_count++;

	newLength(non_zero_digit_count);

	for(int j=0; j < length; j++)
	{
	    data[j] = ptr[length - j - 1] - '0';
	}

	fix();	// removes leading zeroes, sets sign
}

//
// copy constructor  
//
inline
BigInt::BigInt(const BigInt& b) : data(0), length(0)
{
	sign = b.sign;

	newLength(b.length);  // set to size of b

	for (int i=0; i<length; i++)
	    data[i] = b.data[i];

	fix();
}

inline
BigInt::~BigInt()
{
	if (length < 1)
	{
	    cerr << "Internal ERROR - trying to delete invalid object\n";
	    exit (1);
	}

// cout << "Ds DEL Data @ " << (void *)data << "  Size = " << length << "\n";
  	delete [] data;
}
 
 
inline int min(int a, int b)
{
	if (a > b) return b; else return a;
}
 
inline int max(int a, int b)
{
	if ( a > b ) return a; else return b;
}
 
//
// absLess
//      returns true if |a| < |b| 
//
inline
bool absLess(const BigInt& a, const BigInt& b)
{
	if ( a.length > b.length ) return false;
	if ( a.length < b.length ) return true;
	////cout << "Compare " << a << " < " << b << endl;
	for(int i = a.length - 1; i >= 0; i--)
	{
		////printf("absLess(%d)  a(%d) < b(%d)\n", i, a.data[i], b.data[i]);
	    if (a.data[i] < b.data[i]) return true;
	    if (a.data[i] > b.data[i]) return false; 
	}
	////cout << " TRUE" << endl; 
	return true;  // 
}


//
// returns  a < b
// 
inline
bool operator<(const BigInt& a, const BigInt& b)
{
//
// if a and b differ in sign, a check for "<" is easy
//
	if ( a.sign == BigInt::Zero && b.sign == BigInt::Zero ) 
			return false;
	
	if ( a.sign == BigInt::Zero && b.sign == BigInt::Positive ) 
			return true;
	
	if ( a.sign == BigInt::Zero && b.sign == BigInt::Negative ) 
			return false;
	
	if ( b.sign == BigInt::Zero && a.sign == BigInt::Positive ) 
			return false;
	
	if ( b.sign == BigInt::Zero && a.sign == BigInt::Negative ) 
			return true;
	

//
// we'll use absLess to determine truth if a and b are of
// same sign - we get here only if a.sign == b.sign (!= BigInt::Zero)
//
	if ( a.sign == BigInt::Positive)
	    return absLess(a, b);

	if ( a.sign == BigInt::Negative)
	    return absLess(b, a);
	return false;
}

//
// absEqual returns |a| == |b|
// 
inline
bool absEqual(const BigInt& a, const BigInt& b)
{
	if (a.length != b.length) return false;
	
	for (int i = 0; i < a.length; i++)
	    if (a.data[i] != b.data[i] )
	        return false;

	return true;
}
 
//
// returns a == b
// 
inline
bool operator==(const BigInt& a, const BigInt& b)
{
	if ( a.sign == BigInt::Zero && b.sign == BigInt::Zero ) return true;
	if ( a.sign != b.sign ) return false;
	return absEqual(a, b);
}
 
//
// returns  a > b
// 
inline
bool operator> (const BigInt& a, const BigInt& b)
{
	return ( !(a == b) && !(a < b) );
}

//
// returns a >= b
//
inline
bool operator>= (const BigInt& a, const BigInt& b)
{
	return (a == b) || (a > b);
}

//
// returns a <= b
//
inline
bool operator<= (const BigInt& a, const BigInt& b)
{
	return (a == b) || (a < b);
}

inline
ostream& operator<< (ostream& os, const BigInt& a)
{
	if ( a.sign == BigInt::Zero )
	    os << "0";
	else
	{
	    if ( a.sign == BigInt::Negative ) 
	        os << "-";
	    else if (a.sign== BigInt::Positive && 
			BigInt::BI_SignStyle == BigInt::SS_ShowPlus)
	        os << "+";
	        
	    for(int i = a.length - 1; i >= 0; i--)
	    {
	        os << a.data[i];
	        //
	        // output separator if required
	        //
	        if ( i && (i / 3) * 3 == i )
	        {
	            switch(BigInt::BI_OutputStyle)
	            {
	            	case BigInt::OS_Normal: break; 		// do nothing
	            	case BigInt::OS_Comma: os << ","; break;
	            	case BigInt::OS_Period: os << "."; break;
	            	case BigInt::OS_Underscore: os << "_"; break;
	            	case BigInt::OS_Space: os << " "; break;
	            }
	        }
	    }
	}
	return os;
}
 
//
//  absSum returns |a| + |b|
//
inline
BigInt absSum(const BigInt& a, const BigInt& b)
{
	BigInt c;
	int c_length = max(a.length, b.length) + 1;

	c.newLength(c_length); // set c to size of a & b plus 1
	c.zero();

	int	carry = 0;
	for (int i = 0; i < c.length; i++)
	{
	    c(i) = a(i) + b(i) + carry;
	    if (c(i) >= 10)
	    {
		c(i) -= 10;
		carry = 1;
	    }
	    else
	        carry = 0;
	}
	c.data[c.length-1] += carry;

	return c;	// copy constructor is called, it will call fix
}
 

//
// absDiff - returns | |a| - |b| |
//
inline
BigInt absDiff(const BigInt& a, const BigInt& b)
{
	BigInt C;	// defaults to zero
	
	if ( absEqual(a, b) )
	    return C;
	    
//
// assign A the bigger of a and b, B the other,
//	making A and B const so correct version of () will be called
//
	BigInt A1 = a, B1 = b;
	if ( absLess(a, b) )
	{
 	    A1 = b;
	    B1 = a;
	}

//
// A and B need to be constants so that the correct version of
//    operator() is called.
//
	const	BigInt& A = A1;
	const	BigInt& B = B1;

	C.newLength(max(A.length, B.length));
	C.zero();

	if ( A.length < B.length )
	{
	    cerr << "INTERNAL ERROR - A/B length inconsistency\n";
	    exit(1);
	}
	
	int	borrow = 0;
	for (int i = 0; i < A.length; i++)
	{
	    C(i) = A(i) - B(i) - borrow;
		if (C(i) < 0)
		{
			C(i) += 10;
			borrow = 1;
		}
		else
			borrow = 0;
	}
	printf("\n");
	C.fix();
	C.sign = BigInt::Positive;
	return C;
}
 
//
// operator+ returns a + b
//
inline
BigInt operator+(const BigInt& a, const BigInt& b)
{

	if (a.sign == BigInt::Zero) return b;
	if (b.sign == BigInt::Zero) return a;

	BigInt c;

	//
	// if signs are the same, add abs values, then assign sign
	//
	if ( a.sign == b.sign )
	{
	    c = absSum(a, b);
	    c.sign = a.sign;
	}
	else if (a.sign == BigInt::Positive && b.sign == BigInt::Negative)
	{
	    c = absDiff(a, b);
	    if ( absLess(a, b) )
	        c.sign = BigInt::Negative;
	    else
	        c.sign = BigInt::Positive;
	}
    else
	{
	    c = absDiff(a, b);
	    if ( absLess(a, b) )
	        c.sign = BigInt::Positive;
	    else
	        c.sign = BigInt::Negative;
	}

	return c;
}

//
// returns the negative of the BigInt object
//
inline
BigInt BigInt::operator-() const
{
	BigInt temp = *this;
	if (temp.sign == BigInt::Negative)
	    temp.sign = BigInt::Positive;
	else if (temp.sign == BigInt::Positive)
	    temp.sign = BigInt::Negative;
	return temp;
}

//
// returns a - b
// 
inline
BigInt operator-(const BigInt& a, const BigInt& b)
{

	if (b.sign == BigInt::Zero) return a;

	return a + (-b);
}
 
//
// returns a * b
//
inline
BigInt operator*(const BigInt& a, const BigInt& b)
{
	if (a.sign == BigInt::Zero) return BigInt();
	if (b.sign == BigInt::Zero) return BigInt();

	BigInt c;

	if (a.sign != b.sign) c.sign = BigInt::Negative;
	else c.sign = BigInt::Positive;
	
	c.newLength(a.length + b.length);
	c.zero();	// set all digits to zero

	for(int i = 0; i < a.length; i++)
	    for(int j = 0; j < b.length; j++)
	    {
	        c(i+j) += a(i) * b(j);
	        if ( c(i+j) >= 10 )
	        {
	            c(i+j+1) += c(i+j) / 10;
	            c(i+j) = c(i+j) % 10;
		}
	    }

	return c;
}

//
// assignment operator
//
inline
const BigInt& BigInt::operator=(const BigInt& a)
{
	if (this != &a)  // check for self-assignment
	{
	    if (this->length != a.length)   // re-use area if possible
	        this->newLength(a.length);
	    for(int i = 0; i < a.length; i++)
		this->data[i] = a.data[i];
	    this->length = a.length;
	    this->sign = a.sign;
	}
	return *this;
}


//
// operator^ will raise one BigInt to another
//   x ^ n = x * x * . . . * x  (n times)
//
inline
BigInt BigInt::operator^(const BigInt& exp) const
{
	BigInt RValue = 1;
	BigInt count;

	while (count < exp)
	{
	    RValue *= *this;
	    count ++;
	}

	return RValue;
}


//
// operator! will the factorial of a BigInt
//  ! n = n * (n - 1) * . . . * 2 * 1
//  if (n is negative) return 1
//
inline
BigInt BigInt::operator!() const
{
	BigInt count = *this;
	BigInt RValue = 1;

	while (count > 1)
	{
	    RValue *= count;
	    count --;
	}

	return RValue;
}


//
// prefix increment operator
//
inline
BigInt& BigInt::operator++()
{
	*this = *this + 1;
	return *this;
}


//
// postfix increment operator
//
inline
BigInt BigInt::operator++(int)
{
	BigInt d = *this;
	*this = *this + 1;
	return d;
}


//
// prefix decrement operator
//
inline
BigInt& BigInt::operator--()
{
	*this = *this - 1;
	return *this;
}


//
// postfix decrement operator
//
inline
BigInt BigInt::operator--(int)
{
	BigInt d = *this;
	*this = *this - 1;
	return d;
}


//
// remainder ...
inline
bool divide_unsigned(const BigInt& N, const BigInt& D,
				BigInt &Q, BigInt &R)
{
	BigInt ZERO(0l);
	if (D == ZERO) return false;
	if (N < ZERO) return false;
	if (D < ZERO) return false;
	BigInt QP(1l);
	BigInt QN(N);
	Q = avg(QP, QN);
	R = N;
	int step = 1;
	////cout << "N = " << N << endl;
	////cout << "D = " << D << endl;
	////cout << "    Step " << step << ":" << endl;
	////cout << "        R  = " << R << endl;
	////cout << "        Q  = " << Q << endl;
	////cout << "        QP = " << QP << endl;
	////cout << "        QN = " << QN << endl;
	bool done = false;
	while (!done)
	{
		Q = avg(QP, QN);
		R = N - Q * D;
		////cout << "    Step " << ++step << ":" << endl;
		////cout << "        R  = " << R << endl;
		////cout << "        Q  = " << Q << endl;
		////cout << "        QN = " << QN << endl;
		////cout << "        QP = " << QP << endl;
		if ( (R >= ZERO) && (R < D) )
		{
			done = true;
		}
		else if (R < ZERO) // negative remainder
		{
			QN = Q;
		}
		else // (R > 0)
		{
			QP = Q;
		}
		if (step > 1000) done = true;
	}
	return true;
}

//
// returns a % b
// where a % b = Q where Q * b + R = a, where 0 <= R < b
//
inline
BigInt operator%(const BigInt& a, const BigInt& b)
{
	BigInt Q, R;
	divide_unsigned(a, b, Q, R);
	return R;
}
//
// returns a / b
// where a / b = Q where Q * b + R = a, where 0 <= R < b
//
inline
BigInt operator/(const BigInt& a, const BigInt& b)
{
	BigInt Q, R;
	divide_unsigned(a, b, Q, R);
	return Q;
}

#endif
