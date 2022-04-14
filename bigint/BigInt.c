//
// File: BigInt.c
//
// Description:
//	This file supports the methods of the class BigInt.  This
//	class provides the user with infinite precision integer
//	arithmetic.
//
// Author: Dave Buscaglia	Nov 1, 1997
//	
//

#include <iostream.h>

#include "BigInt.h"

//
// static member data
//
	BigInt::OutputStyle	BigInt::BI_OutputStyle = BigInt::OS_Comma;
	BigInt::SignStyle	BigInt::BI_SignStyle = BigInt::SS_Normal;
//
// static functions
//
void	BigInt::setOutputStyle(OutputStyle os)
{
	BI_OutputStyle = os;
}

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
void	BigInt::zero()
{	
	for (int i = 0; i < length; i++) data[i] = 0;
}

//
// constructor from int to BigInt
// 
BigInt::BigInt(int i) : data(0), length(0)
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
	int tmp_i = i;

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
BigInt::BigInt(char *s) : data(0), length(0)
{
	char* ptr = s;

	
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
BigInt::BigInt(const BigInt& b) : data(0), length(0)
{
	sign = b.sign;

	newLength(b.length);  // set to size of b

	for (int i=0; i<length; i++)
	    data[i] = b.data[i];

	fix();
}

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
bool absLess(const BigInt& a, const BigInt& b)
{
	if ( a.length > b.length ) return false;
	if ( a.length < b.length ) return true;

	for(int i = a.length - 1; i >= 0; i--)
	{
	    if (a.data[i] < b.data[i]) return true;
	}
	return false;
}


//
// returns  a < b
// 
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
}

//
// absEqual returns |a| == |b|
// 
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
bool operator==(const BigInt& a, const BigInt& b)
{
	if ( a.sign == BigInt::Zero && b.sign == BigInt::Zero ) return true;
	if ( a.sign != b.sign ) return false;
	return absEqual(a, b);
}
 
//
// returns  a > b
// 
bool operator> (const BigInt& a, const BigInt& b)
{
	return ( !(a == b) && !(a < b) );
}

//
// returns a >= b
//
bool operator>= (const BigInt& a, const BigInt& b)
{
	return (a == b) || (a > b);
}

//
// returns a <= b
//
bool operator<= (const BigInt& a, const BigInt& b)
{
	return (a == b) || (a < b);
}

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
BigInt absDiff(const BigInt& a, const BigInt& b)
{
	BigInt C;	// defaults to zero
	
	if ( absEqual(a, b) )
	    return C;
	    
//
// assign A the bigger of a and b, B the other,
//	making A and B const so corrent version of () will be called
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
	return C;
}
 
//
// operator+ returns a + b
//
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
BigInt operator-(const BigInt& a, const BigInt& b)
{

	if (b.sign == BigInt::Zero) return a;

	return a + (-b);
}
 
//
// returns a * b
//
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
BigInt& BigInt::operator++()
{
	*this = *this + 1;
	return *this;
}


//
// postfix increment operator
//
BigInt BigInt::operator++(int)
{
	BigInt d = *this;
	*this = *this + 1;
	return d;
}


//
// prefix decrement operator
//
BigInt& BigInt::operator--()
{
	*this = *this - 1;
	return *this;
}


//
// postfix decrement operator
//
BigInt BigInt::operator--(int)
{
	BigInt d = *this;
	*this = *this - 1;
	return d;
}
