#ifdef PROBLEM_DESCRIPTION

Sub-string divisibility


Problem 43

The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

    d2d3d4=406 is divisible by 2
    d3d4d5=063 is divisible by 3
    d4d5d6=635 is divisible by 5
    d5d6d7=357 is divisible by 7
    d6d7d8=572 is divisible by 11
    d7d8d9=728 is divisible by 13
    d8d9d10=289 is divisible by 17

Find the sum of all 0 to 9 pandigital numbers with this property.

#endif

#include <stdio.h>
#include "digit.h"

int getDigit(int n, int d)
{
	int d1 = n % 10; n /= 10;
	int d2 = n % 10; n /= 10;
	int d3 = n % 10;
	
	if ( d == 1 ) return d1;
	if ( d == 2 ) return d2;
	if ( d == 3 ) return d3;
	return -1;
}

bool isDigit(int n, int d, int dval)
{
	if (getDigit(n, d) == dval) return true;
	return false;
}

int m17[100];	// -1 indicates last element of 3 - digit numbers div by 17
				// with other rules - no digit repeats, no fives
int m17_count = 0;
int m13[100];	// -1 indicates last element of 3 - digit numbers div by 13
				// with other rules - no digit repeats, no fives
int m13_count = 0;
int m11[300];	// -1 indicates last element of 3 - digit numbers div by 11
				// with other rules - no digit repeats, number in the 500's
int m11_count = 0;
int m7[300];	// -1 indicates last element of 3 - digit numbers div by 7
				// with other rules - no digit repeats, five is tens digit
int m7_count = 0;
// digit 5 is always a 5, 0 is excluded as the next two digits would have to 
// be divisible by 11, which means the digits would repeat.

int m3_count = 0;
int m3[300];	// -1 indicates last element of 3 - digit numbers div by 3
				// with other rules - no digit repeats, no fives, tens digit is
				// even, and m3 divisible by 3

bool
NoFive(int n)
{
	//printf("NOFIVE Checking %d\n", n);
	int d0 = n % 10; n /= 10;
	int d1 = n % 10; n /= 10;
	int d2 = n % 10;
	if ( (d0 == d1) || (d0 == d2) || (d1 == d2) ) return false;
	if ( (d0 == 5)  || (d1 == 5)  || (d2 == 5)  ) return false;
	return true;
}
	
bool
HundFive(int n)
{
	//printf("HundFIVE Checking %d\n", n);
	int d0 = n % 10; n /= 10;
	int d1 = n % 10; n /= 10;
	int d2 = n % 10;
	
	if ( (d0 == d1) || (d0 == d2) || (d1 == d2) ) return false;
	if ( (d2 != 5)  ) return false;
	return true;
}	
	
bool
TenFive(int n)
{
	//printf("TenFIVE Checking %d\n", n);
	int d0 = n % 10; n /= 10;
	int d1 = n % 10; n /= 10;
	int d2 = n % 10;
	
	if ( (d0 == d1) || (d0 == d2) || (d1 == d2) ) return false;
	if ( (d1 != 5)  ) return false;
	return true;
}	


bool
Three(int gn)
{
	int n = gn;
	int d0 = n % 10; n /= 10;
	int d1 = n % 10; n /= 10;
	int d2 = n % 10;
	//printf("THREE Checking %d - %d%d%d\n", gn, d2, d1, d0);
	
	if ( (d0 == 5) || (d1 == 5) || (d2 == 5) ) { 
		//printf("Fives digits\n"); 
		return false;
	}
	if ( (d0 == d1) || (d0 == d2) || (d1 == d2) ) { 
		//printf("Multiple digits\n"); 
		return false;
	}
	if ( (gn % 3 != 0)  ) { 
		//printf("Not divisible by three\n"); 
		return false;
	}
	if ( ( d1 % 2 != 0) ) { 
		//printf("Second digit not even\n"); 
		return false;
	}
	return true;
}	
void fill(int *td, int &n, int mult, bool valid(int))
{
	td[0] = mult;
	int	v = mult;
	while(v < 999)
	{
		if (valid(v)) { td[n] = v; n++; }
		v += mult;
	}
	td[n] = -1;
}

void init()
{
	fill (m17, m17_count, 17, NoFive);
	fill (m13, m13_count, 13, NoFive);
	fill (m11, m11_count, 11, HundFive);
	fill (m7, m7_count, 7, TenFive);
	fill (m3, m3_count, 3, Three);
}

void o3d(int *m, int mc, int mv)
{
	printf("Multiplier: %d  -  Count: %d\n", mv, mc);
	while (*m > 0)
		printf("    %d\n", *m++);
	printf("\n");
}

void out()
{
	o3d (m17, m17_count,  17);
	o3d (m13, m13_count, 13);
	o3d (m11, m11_count, 11);
	o3d (m7, m7_count, 7);
	o3d (m3, m3_count, 3);
}


/*
 * long digMatch(long n, int twodig, int *arr, int &index)
{
	for (int k = index; arr[k] > 0; k++)
	{
		int d = arr[k] % 10;
		if (isDigInNum(n, d)) continue;
		if (arr[k]/10 == twodig){
			index = k;
			return arr[k] % 10;
		}
	}
	return -1;
}*/

long digMatch(long n, int twodig, int *arr, int index)
{
	int d = arr[index] % 10;
	if (isDigInNum(n, d)) return -1;
	if (arr[index]/10 == twodig){
			return arr[index] % 10;
	}
	return -1;
}

long getNum(int &d3, int &d7, int &d11, int &d13, int &d17)
{
	long s = m3[d3];	// divisible by 3
	s = 10 * s + 5;		// divisible by 5
	long d = digMatch(s, s%100, m7, d7);
	if (d < 0){ return -1; }
	s = 10 * s + d;		// divisible by 7
	d = digMatch(s, s%100, m11, d11);
	if (d < 0){ return -1;}
	s = 10 * s + d;		// divisible by 11
	d = digMatch(s, s%100, m13, d13);
	if (d < 0){ return -1;}
	s = 10 * s + d;		// divisible by 13
	d = digMatch(s, s%100, m17, d17);
	if (d < 0){ return -1;}
	s = 10 * s + d;		// divisible by 17
	return s;
}

bool incIndex(int &d3, int &d7, int &d11, int &d13, int &d17)
{
	d3++;
	if ( d3  >= m3_count) {  d3 = 0;  d7++;}
	if ( d7 >= m7_count) {  d7 = 0;  d11++;}
	if ( d11 >= m11_count) { d11 = 0;  d13++;}
	if ( d13 >= m13_count) { d13 = 0;  d17++;}
	if ( d17 >= m17_count) { 
		//printf("RETURNING TRUE: d3: %d  d7: %d  d11: %d  d13: %d  d17: %d \n", 
		//	d3, d7, d11, d13, d17);
		return true;}
	return false;
}

long addPanDigits(long n, long &sum)
{
	long d10 = 1000000000l;
	long d09 = 100000000l;
	//long d08 = 100000000l;
	vlong_t	vn = get_digits(n);
	vlong	nd(vn);
	if (nd.size() == 7) nd.add(0);
	long fd[3];
	int fd_count = 0;
	for (long k = 0; k <= 9; k++)
	{
		if (nd.exists(k)) continue;
		fd[fd_count++] = k;
	}
	//for (int i = 0; i < fd_count; i++)
	//    printf("Pandigit %d : %ld\n", i, fd[i]);
	long n1 = d10 * fd[0] + d09 * fd[1] + n;
	long n2 = d10 * fd[1] + d09 * fd[0] + n;
	printf("PD #1: %ld\n", n1);
	printf("PD #2: %ld\n", n2);
	sum += n1 + n2;
	return 0;
}

int main()
{
	init();
	//out();
	
	int d3 = 0, d7 = 0, d11 = 0, d13 = 0, d17 = 0;
	bool done = false;
	long num;
	long sum = 0;
	while (!done)
	{
		num = getNum(d3, d7, d11, d13, d17);
		//printf("d3: %d  d7: %d  d11: %d  d13: %d  d17: %d \n", d3, d7, d11, d13, d17);
		if (num > 0) { printf("Number: %ld\n", num);
			printf("d3: %d  d7: %d  d11: %d  d13: %d  d17: %d \n", 
			d3, d7, d11, d13, d17); 
			addPanDigits(num, sum);}
		done = incIndex(d3, d7, d11, d13, d17);
	}
	printf("Sum of wacky pandigitals is: %ld\n", sum);
}
