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
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

using namespace std;


class BigInt
{
  	friend bool absLess(const BigInt& a, const BigInt& b);
  	friend bool absEqual(const BigInt& a, const BigInt& b);

  	friend BigInt absSum(const BigInt& a, const BigInt& b);
  	friend BigInt absDiff(const BigInt& a, const BigInt& b);
  	
  	friend bool operator<(const BigInt&, const BigInt&);
  	friend bool operator==(const BigInt&, const BigInt&);
  	friend bool operator!=(const BigInt&, const BigInt&);
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
	friend	bool    divide(const BigInt& N, const BigInt& D,
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
		BigInt operator^(long n) const;
		BigInt operator!() const;
		inline BigInt operator*=(const BigInt&);
		inline BigInt operator+=(const BigInt&);
		inline BigInt operator/=(const BigInt&);
		inline BigInt operator%=(const BigInt&);
		int num_digits();
		int get_digit(int n);
		const string & to_string() const;
		const char *c_str() const {to_string(); return out.c_str(); };
		BigInt reverse()	// return number with digits reversed
		{
			string st = to_string();
			//cout << "IN REVERSE: " << st << endl;
			::reverse(st.begin(), st.end());
			BigInt b(st.c_str());
			//cout << "AFTER REVERSE: " << b << endl;
			return b;
		}
		void debug(const char *s = "") const;
		bool isPalindrome() {
			string s = to_string();
			size_t	n = s.size() - 1;
			size_t  end = n / 2;
			for (size_t i = 0; i < end; i++, n--)
			    if (s[i] != s[n]) return false;
			return true;
		}
			
			
    private:
		#define BASE_NUMBER 1000000000000l   // Must be a number of the form 10^N
		#define BASE_NUMBER_ROOT 1000000l   // 10 ^ (BASE_EXPONENT/2)
		#define BASE_EXPONENT  12
		#define DATA_TYPE      long
		#define ZERO		   BigInt(0l)

		DATA_TYPE	operator[](int n) const { if ((n < 0) || (n >= length) ) return 0; 
											return data[n]; };

		void	fix();
		void	newLength(int);
		void	zero();

		enum 	Sign { Positive, Negative, Zero };
		DATA_TYPE* 	data;
		int		length;			// number of elements in data array
		mutable	Sign 	sign;  // made mutable so const versions can be abs valued
		
		mutable string  out;
		
};

inline
int BigInt::num_digits() 
{
	int rv = (length - 1) * BASE_EXPONENT;
	DATA_TYPE  d = data[length - 1];
	while (d > 0)
	{
		d /= 10;
		rv ++;
	}
	return rv;
}

inline
int BigInt::get_digit(int n) { 
	if (n < 0 || n >= num_digits()) return 0; 
	DATA_TYPE d = data[n / BASE_EXPONENT];
	int nd = n % BASE_EXPONENT;
	while (nd > 0) { d /= 10; nd--; }
	return d % 10;
}



inline
void BigInt::debug(const char *s) const
{
	printf("%s  length = %d  ", s, length);
	printf("Sign: %d\n", sign);
	for (int i = 0; i < length; i++)
	    printf("i: %2d    data: %ld\n", i, data[i]);
	printf("NUM: %s\n", c_str());
}		
		
inline
BigInt	avg(BigInt &a, BigInt &b)
{
	BigInt	ans = a + b;
	DATA_TYPE carry = 0;
	bool fd1 = (ans.data[ans.length - 1] == 1);
	for (int i = ans.length - 1; i >= 0; i--)
	{
		if (ans.data[i] % 2) { carry = BASE_NUMBER; ans.data[i]--; }
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
// HELPER functions
//


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
	data = new DATA_TYPE [length];
	for (int i = 0; i < length; i++)data[i] = 0;
// cout << "Nl NEW Data @ " << (void *)data << "  Size = " << length << "\n";

}

//
// zero will set all digits equal to 0
//
inline
void	BigInt::zero()
{	
	for (int i = 0; i < length; i++) data[i] = 0;
	//this->sign = BigInt::Zero;
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
	    tmp_i /= BASE_NUMBER;
	}

//
// if length == 0, set length to 1 to hold the single digit of zero
// 
	if (length == 0) length = 1;
	
	data = new DATA_TYPE [length];	// set data to point to array
// cout << "Ci NEW Data @ " << (void *)data << "  Size = " << length << "\n";

	for(int m = 0; m < length; m++)
	{
	    data[m] = i % BASE_NUMBER;
	    i /= BASE_NUMBER;
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

	newLength(non_zero_digit_count/BASE_EXPONENT + 1);
//	printf("non_zero_digit_count: %d  length: %d\n", non_zero_digit_count, length);
//
// need to use BASE_EXPONENT to determine how to initialize
	const char *ep = ptr + non_zero_digit_count;	// ep points to 'last' char
	int d_index = -1;
	int c_count = 0;
	long mult_10 = 1;
	do
	{
	    ep--;
		if (c_count % BASE_EXPONENT == 0)
		{
			d_index++;
			data[d_index] = 0;
			mult_10 = 1;
		}
			
		data[d_index] += ((*ep) - '0')*mult_10;
		mult_10 *= 10;
		//printf("length: %d d_index: %d   ep: %c   data[%d] : %ld\n", 
		//	length, d_index, *ep, d_index, data[d_index]);
	    c_count++;
	}
	while ( (ep != ptr) && (c_count < non_zero_digit_count) );
	
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
	return false;  //  we get here only when a == b 
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
// returns  a != b
// 
inline
bool operator!= (const BigInt& a, const BigInt& b)
{
	return ( !(a == b) );
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
const string & BigInt::to_string() const
{
	out = "";
	if ( this->sign == BigInt::Zero )
	    out += "0";
	else
	{
	    if ( this->sign == BigInt::Negative ) out += "-";
  
		stringstream ss;
		ss << this->data[this->length - 1];
	    for(int i = this->length - 2; i >= 0; i--)
	    {
			DATA_TYPE d = this->data[i];
			ss << setw(BASE_EXPONENT) << setfill('0') << d;
	    }
	    out += ss.str();
	}
	return out;
}

inline
ostream& operator<< (ostream& os, const BigInt& a)
{
	os << a.to_string();
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
	if ( (a.sign == BigInt::Zero) && (b.sign == BigInt::Zero) ) return c;

	int	carry = 0;
	for (int i = 0; i < c.length; i++)
	{
	    c.data[i] = a[i] + b[i] + carry;
	    if (c.data[i] >= BASE_NUMBER)
	    {
			c.data[i] -= BASE_NUMBER;
			carry = 1;
	    }
	    else
	        carry = 0;
	}
	c.data[c.length-1] += carry;
	c.sign = BigInt::Positive;
	c.fix();
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
	const	BigInt* A = &a;
	const	BigInt* B = &b;
	if ( absLess(a, b) )
	{
 	    A = &b;
	    B = &a;
	}

	C.newLength(max(A->length, B->length));
	C.zero();
	//C.debug();

	if ( A->length < B->length )
	{
	    cerr << "INTERNAL ERROR - A/B length inconsistency\n";
	    exit(1);
	}
	
	int	borrow = 0;
	for (int i = 0; i < A->length; i++)
	{
		DATA_TYPE bvalue = (i < B->length) ? B->data[i] : (DATA_TYPE)0;
	    C.data[i] = A->data[i] - bvalue - borrow;
		if (C.data[i] < 0)
		{
			C.data[i] += BASE_NUMBER;
			borrow = 1;
		}
		else
			borrow = 0;
	}
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
// returns a * b where:    a < D and b < D, and B * B = D
//		if  a = a1 * B + a0
//			b = b1 * B + b0
//
//		then a * b = 
//			a1 * b1 * B^2 +
//			(a1 * b0 + a0 * b1) * B +
//			a0 * b0
//
//     NOTE:  a1, a0, b1 and b0 are all less than B
//				the B factor cannot exceed 2*D, and thus, DATA_TYPE
//				must be able to store 2 * D as a number
//
inline
void	mult64( DATA_TYPE a, DATA_TYPE b,
				DATA_TYPE &h, DATA_TYPE &l)
{
	long a1 = a / BASE_NUMBER_ROOT;
	long a0 = a % BASE_NUMBER_ROOT; 
	long b1 = b / BASE_NUMBER_ROOT;
	long b0 = b % BASE_NUMBER_ROOT; 
	
	l = a1 * b1;
	h = (a1 * b0 + a0 * b1) * BASE_NUMBER_ROOT + a0 * b0;
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
	DATA_TYPE	p0, p1;
	
	for(int i = 0; i < a.length; i++)
	{
		for(int j = 0; j < b.length; j++)
		{
			mult64(a.data[i], b.data[j], p0, p1);   // a * b = p1 * BASE_NUMBER + p0
			c.data[i+j] += p0;  	// 
			c.data[i+j+1] += p1;	// add to the next 'digit'
			if ( c.data[i+j] >= BASE_NUMBER )
			{
				c.data[i+j+1] += c.data[i+j] / BASE_NUMBER;
				c.data[i+j] = c.data[i+j] % BASE_NUMBER;
			}
			if ( c.data[i+j+1] >= BASE_NUMBER )
			{
				c.data[i+j+2] += c.data[i+j+1] / BASE_NUMBER;
				c.data[i+j+1] = c.data[i+j+1] % BASE_NUMBER;
			}
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
// operator^ will raise one BigInt to another
//   x ^ n = x * x * . . . * x  (n times)
//
inline
BigInt BigInt::operator^(long exp) const
{
	BigInt RValue = 1;
	long count = 0;

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
bool divide(const BigInt& N, const BigInt& D,
				BigInt &Q, BigInt &R)
{
	bool Nnegative = false;
	bool Dnegative = false;
	bool rv = false;
	if (D == ZERO) return false;
	if (N < ZERO) { Nnegative = true; N.sign = BigInt::Positive;}
	if (D < ZERO) { Dnegative = true; D.sign = BigInt::Positive;}
	BigInt QP(1l);
	BigInt QN(N);
	Q = avg(QP, QN);
	R = N;
	int step = 1;
	bool done = false;
	if (D > N)
	{
		R = N;
		Q = ZERO;
		done = true;
	}
	//printf("N = %s   D = %s  \n", N.c_str(), D.c_str());
	while (!done)
	{
		Q = avg(QP, QN);
		R = N - Q * D;
		//printf("step: %d\n     Q = %s   R = %s  \n", step, Q.c_str(), R.c_str());
		//printf("     QP = %s   QN = %s  \n", QP.c_str(), QN.c_str());
		
		if ( (R >= ZERO) && (R < D) )
		{
			done = true;
			rv = true;
		}
		else if (R < ZERO) // negative remainder
		{
			QN = Q;
		}
		else // (R > 0)
		{
			QP = Q;
		}
		if (++step > 100000) {
			done = true;
			rv = false;
		}
	}
	// return N/D to correct signs
	if (Dnegative) D.sign = BigInt::Negative;
	if (Nnegative) N.sign = BigInt::Negative;
	if (rv) {
		if (Nnegative) { if (R.sign != BigInt::Zero) R.sign = BigInt::Negative; }
		if (Nnegative ^ Dnegative) { if (Q.sign != BigInt::Zero) Q.sign = BigInt::Negative; }
	}
	return rv;
}

//
// returns a % b
// where a % b = Q where Q * b + R = a, where 0 <= R < b
//
inline
BigInt operator%(const BigInt& a, const BigInt& b)
{
	BigInt Q, R;
	divide(a, b, Q, R);
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
	divide(a, b, Q, R);
	return Q;
}

#endif
