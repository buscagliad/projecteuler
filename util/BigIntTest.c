// test.cpp
#include <iostream>
#include <math.h>
#include "bigint.h"
#include <string.h>

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

#define DO(op)	printf("a %s b = %ld\n", #op, a op b); \
				printf("A %s B = %s\n", #op, (A op B).c_str());

#define AVG		printf("(a + b)/2 = %ld\n",(a + b)/2); \
				printf("(A + B)/2 = %s\n", avg(A,B).c_str());

void test2(long a, long b) // test against long ints
{
	BigInt A(a);
	BigInt B(b);
	printf("a = %ld  ", a);
	printf("b = %ld\n", b);
	printf("A = %s  ", A.c_str());
	//A.debug();
	printf("B = %s\n", B.c_str());
	//B.debug();
	//BigInt C = absSum(a, b);
	//printf("| |a| + |b| | = %ld\n", abs(a) + abs(b));

	//printf("| |A| + |B| | = %s\n", C.c_str());
	//C = absDiff(a, b);
	//printf("| |a| - |b| | = %ld\n", abs(abs(a) - abs(b)));
	//printf("| |A| - |B| | = %s\n", C.c_str());
	//return;
	//long x = 124;
	//BigInt X(x);
	//BigInt Y = A - B * X;
	//X.debug();
	//Y.debug();
	//printf("a - b * %ld = %ld\n",  x, a - b * x);
	//printf("A - B * %s = %s\n",  X.c_str(), Y.c_str());
	DO(+);
	DO(*); 
	DO(-);
	AVG;
	DO(/);
	DO(%);
	if ( ((a/b)*b + a%b) != a)
		printf("LONG ERROR\n");
	if ( ((A/B)*B + A%B) != A)
		printf("BIGINT ERROR\n");
	printf("\n\n");
}

#define ERROR(s) printf("ERROR - %s - i = %ld  j = %ld\n", s, i, j)
#define TEST3_LOOP_SIZE 100
void	test3()
{
	BigInt	Ten(10l);
	BigInt	A;
	BigInt	B;
	char	str[100000];
	long	errcnt = 0;
	for (long i = 0; i < TEST3_LOOP_SIZE; i++)
	{
		A = Ten ^ i;
	    for (long j = 0; j < TEST3_LOOP_SIZE; j++)
	    {
			B = Ten ^ BigInt(j);
			sprintf(str, "%s", (A*B).c_str());
			long index = i + j;
			if (str[0] != '1') {
				printf("ERROR - NOT a 1 - i = %ld  j = %ld\n", i, j); errcnt++; }
			for (int k = 1; k < index; k++) if (str[k] != '0') { printf("ERROR - NOT A ZERO - i = %ld  j = %ld  str=%c\n", i, j, str[k]); errcnt++; }
		}
	}
	if (errcnt == 0)
		printf("TEST 3 - Powers of ten's test - successful!!\n");
	else
	    printf("TEST 3 - Powers of ten's test - ERROR - error count: %ld\n", errcnt);
}

bool test4(long prime, long nnines)
{
	BigInt	p(prime); 
	char nn[nnines+6];
	memset(nn, '9', nnines);
	nn[nnines] = 0;

	BigInt Nines(nn);
	printf("Nines: %s\n", Nines.c_str());
	BigInt Q = Nines / p;
	BigInt R = Nines % p;
	printf("Q: %s\n", Q.c_str());
	printf("R size: %lu\n", strlen(nn));
	printf("R: %s\n", R.c_str());
	printf("D*Q + R = %s\n", (p * Q + R).c_str());
	if (R == BigInt(0l)) return true;
	return false;
}

void test5()
{
	BigInt v(2);
	BigInt g(2);
	if (g < v) printf("BAD <\n");
	if (g > v) printf("BAD >\n");
	if (g == v) printf("GOOD!!!\n");
	for (long n = 0; n < 10; n++)
	{
		BigInt	x(n);
		BigInt	a = v ^ x;
		BigInt  b = v ^ n;
		printf("v: %s   n: %ld   v^n: %s   v^N: %s\n", v.c_str(), n, b.c_str(), a.c_str());
	}
}

int main()
{
	test5();
	return 1;
	test4(31, 15);
	return 1;
	test4(79, 13); 
	test4(227, 226);
	for (long i = 10; i < 1000; i++)
	{
		if (test4(i, i-1)) printf("Good number is: %ld\n", i);
	}
	return 1;
	test3();
	test2(-4626987331561, 51);
	test2(4626987331561, 51);
	test2(4626987331561, -51);
	test2(4626987331561, -51);
	test2(4626987331561, -51);
	test2(4626987331561, -51);
	test2(4626987331561, -51);
	test2(-4626987331561, -51);
	test2(9, 11);
	const BigInt googol = BigInt(10)^100;

	test();
	Problem1(googol);
	Problem2("5000000000");
	Problem2(googol);
}


