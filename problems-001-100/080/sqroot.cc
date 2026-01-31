#ifdef PROBLEM_DESCRIPTION

Square root digital expansion


  [Show HTML problem content]  
Problem 80

It is well known that if the square root of a natural number is not an integer, then it is irrational. The decimal expansion of such square roots is infinite without any repeating pattern at all.

The square root of two is 1.41421356237309504880..., and the digital sum of the first one hundred decimal digits is 475.

For the first one hundred natural numbers, find the total of the digital sums of the first one hundred decimal digits for all the irrational square roots.

#endif

#include <vector>
#include <cmath>
#include <cstdio>
#include "digit.h"
#include "bigint.h"

using namespace std;

const BigInt B[10]{
	"0000000000000", // ignored
	"0000000000000", // ignored
	"5000000000000", // 1/2
	"3333333333333", // 1/3
	"2500000000000", // 1/4
	"2000000000000", // 1/5
	"1666666666666", // 1/6
	"1428671428671", // 1/7
	"1250000000000", // 1/8
	"1111111111111"}; // 1/9


#include <cstdio>
#include <cstring>


#include "bigint.h"

vector<int> cfvalues;
		int cfa0;

typedef BigInt INT;

//#define SQUARE_ROOT_2
//1.4142135623730950488016887242096980785696718753769480731766797379907324784621
//r 4142135623730950488016887242096980785696718753769480731766797379907324784621
//07038850387534327641572735013846230912297024924836055850737212644121497099935831
//070388503875343276415727
//41322266592750559275579995050115278206057147010955997160597027
//r : 4142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727

void div(INT &r, INT n, INT d)
{
	INT b = n * 10l;
	long ntimes = 0;
	r = 0l;
	while (r.num_digits() < 105)
	{
		while (b > d)
		{
			b -= d;
			ntimes++;
		}
		r = r * 10l + ntimes;
		b *= 10l;
		//printf("ntimes : %ld\n", ntimes);
		//printf("n : %s\n", n.c_str());
		//printf("d : %s\n", d.c_str());
		//printf("b : %s\n", b.c_str());
		//printf("r : %s\n", r.c_str());
		ntimes = 0;
	}
}
	
	

INT an(int n)
{
	#ifdef COMPUTE_E
	if (n == 0l) return INT(2);
	// 1, 2, 3 --> 1, 2, 1
	// 4, 5, 6 --> 1, 4, 1
	// 3k - 2, 3K - 2, 3k --> 1, 2k, 1
	if (n % 3 == 1) return INT(1);
	if (n % 3 == 0) return INT(1);
	return INT(2 * (n+1)/3);
	#else
	INT rv;
	if (n == 0) 
	    rv = cfa0;
	else
	{
		n--;
		n %= cfvalues.size();
		rv = cfvalues[n];
	}
	//printf("n: %d   rv: %s\n", n, rv.c_str());
	return rv;
	#endif
}

static int gn(-1);
static int gk(-1);
static INT hnm2(0l);
static INT hnm1(1l);
static INT knm2(1l);
static INT knm1(0l);

void init()
{
	gn = -1;
	gk = -1;
	hnm2 = 0l;
	hnm1 = 1l;
	knm1 = 0l;
	knm2 = 1l;
}

INT hNext()
{
	gn++;
	INT hn = an(gn) * hnm1 + hnm2;
	hnm2 = hnm1;
	hnm1 = hn;
	return hn;
}

INT kNext()
{
	gk++;
	INT kn = an(gk) * knm1 + knm2;
	knm2 = knm1;
	knm1 = kn;
	return kn;
}


int	contfrac(int n, int &a0, vector<int> &cf)
{
	double dn = n;
	a0 = sqrt(dn);
	long a = a0;
	long r = a;
	long s = (n - r * r);
	cf.clear();
	bool done = false;
	while (!done)
	{
		a = (double)(r + a0) / (double) s;
		r = a * s - r;
		s = (n - r * r)/s;
		cf.push_back(a);
		done = a == 2 * a0;
	}
	printf("Square root of %d  :: a0: %d ", n, a0);
	for (int i = 0; i < cf.size(); i++) printf(" %d ", cf[i]);
	printf("\n");
	return cf.size();
}

#define N(x)  ( (x < 10) ? 1 : (x < 100) ? 2 : (x < 1000) ? 3 : 0 )

void docf(int n, int &odd_periods)
{
	vector<int> v;
	int a0;
	contfrac(n, a0, v);
	printf("Continued fraction for square root of %d is: ", n);
	printf("[%d,(%d", a0, v[0]);
	for (size_t i = 1; i < v.size(); i++)
	    printf(",%d", v[i]);
	printf(")]\n");
	if (v.size() % 2) odd_periods++;
}

#define MAX_NUM 10000
int mainexit()
{
	int odd = 0;
	for (int j = 2; j <= MAX_NUM; j++)
	{
		if (isSquare(j)) continue;
		docf(j, odd);
	}
	printf("Number of odd continued fraction periods <= %d is %d\n",
		MAX_NUM, odd);
	return 0;
}

int SUM(int a)
{
	int s = 0;
	while ( a > 0)
	{
		s += a % 10;
		a /= 10;
	}
	return s;
}
		

int main()
{
	BigInt k;
	BigInt h;
	int sum = 0;
	for (int i = 2; i <= 100; i++)
	{
		init();
		if (isSquare(i)) continue;
		h = 0l;
		k = 0l;
		contfrac(i, cfa0, cfvalues);
		while ( (h.num_digits() < 110) && (k.num_digits() < 110) )
		{
			h = hNext();
			k = kNext();
		}
		BigInt r(0l);
		div(r, h, k);
			
		printf("h: %s\nk: %s\n", h.c_str(), k.c_str());
		printf("r: %s\n", r.c_str());
		char digs[r.num_digits()+2];
		strcpy(digs, r.c_str());
		for (size_t i = 0; i < 100; i++)
			if (isdigit(digs[i])) sum += digs[i] - '0';
		printf("Sum of the numeration digits is %d\n", sum);
	}
}

	
