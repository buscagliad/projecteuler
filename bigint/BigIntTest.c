// test.cpp
#include <iostream.h>
#include "BigInt.h"

void	test()
{
	BigInt a = 11, b = 3, c = -70, d = -9, e;

	cout << "a = " << a << "\n"
	     << "b = " << b << "\n"
	     << "c = " << c << "\n"
	     << "d = " << d << "\n"
	     << "e = " << e << "\n";
 
	cout << "\nTest operator+\n";
	cout << "a + b = " << a + b << "\n"
	     << "a + c = " << a + c << "\n"
	     << "c + b = " << c + b << "\n"
	     << "c + d = " << c + d << "\n";
 
	cout << "\nTest operator-\n";
	cout << "a - b = " << a - b << "\n"
	     << "a - c = " << a - c << "\n"
	     << "c - b = " << c - b << "\n"
	     << "c - d = " << c - d << "\n";
 
	cout << "\nTest operator*\n";
	cout << "a * b = " << a * b << "\n"
	     << "a * c = " << a * c << "\n"
	     << "c * b = " << c * b << "\n"
	     << "c * d = " << c * d << "\n";
 
	cout << "\nTest pre- and post- increment operators\n";
	cout << "a++ = " << a++ << "\n";
	cout << "a = " << a << "\n";
	cout << "++a = " << ++a << "\n";
 
	cout << "\nTest pre- and post- decrement operators\n";
	cout << "a-- = " << a-- << "\n";
	cout << "a = " << a << "\n";
	cout << "--a = " << --a << "\n";
 
	cout << "\nTest compound statement, and assignment operator\n";
	cout << "a = " << a << "\n"
	     << "b = " << b << "\n"
	     << "c = " << c << "\n"
	     << "d = " << d << "\n"
	     << "e = " << e << "\n";
 	cout << "(e = a*b + c*d) = " <<  (e = a*b + c*d) << "\n";
	cout << "e = " << e << "\n";

	cout << "\nTest power operator\n";
	cout << "b ^ 3 = " << (b ^ 3) << "\n";
	cout << "a ^ b = " << (a ^ b) << "\n";

	cout << "\nTest factorial operator\n";
	for (BigInt n = 1; n < 10; n++) 
	    cout << n << "! = " << (!n) << "\n";
}


void	Problem1(BigInt g)
{
	BigInt n = 1;
	BigInt nfac = !n;


	while( nfac < g)
	{
	    ++n;
	    nfac = !n;
//cout << "n = " << n << "    nfac = " << nfac << "\n";
	}

	--n;

	cout << "\nThe value N that makes the statement:  N! < g < (N+1)!, true is: \n";
	cout << "\n     N = " << n;

	cout << "\n     g = " << g;
	cout << "\n    N! = " << !n;
	cout << "\n(N+1)! = " << !(n+1) << endl;
}

void	Problem2(BigInt EarthPop)
{
	BigInt JustHeard = 1;
	BigInt AlreadyKnow ("0");
	BigInt LastSecond(1);
	BigInt LastLastSecond("0");
	int	numSeconds = 0;

//	cout << "Earth Population = " << EarthPop;
//	cout << "\n";

	while (AlreadyKnow < EarthPop)
	{
	    JustHeard = LastSecond + LastLastSecond;
	    LastLastSecond = LastSecond;
	    LastSecond = JustHeard;
	    numSeconds++;
//	    cout << numSeconds << "   " <<  AlreadyKnow << "  " <<
//	                  JustHeard << "   ";   
	    AlreadyKnow += JustHeard;
//	    cout << AlreadyKnow << "\n";
	}

	cout << "In " << numSeconds << " seconds, a total of " << AlreadyKnow;
	cout << "  have heard the rumor, which exceeds the earth's " <<
		"population of\n";
	cout << " " << EarthPop << "\n";
}

void main()
{
	const BigInt googol = BigInt(10)^100;

	test();
	Problem1(googol);
	Problem2("5000000000");
	Problem2(googol);
}


