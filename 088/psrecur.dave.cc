#ifdef PROBLEM_DESCRIPTION

Product-sum numbers


  [Show HTML problem content]  
Problem 88

A natural number, N, that can be written as the sum and product of a given set of at least two natural numbers, {a1, a2, ... , ak} is called a product-s


um number: N = a1 + a2 + ... + ak = a1 × a2 × ... × ak.

For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.

For a given set of size, k, we shall call the smallest N with this property a minimal product-sum number. The minimal product-sum numbers for sets of size, k = 2, 3, 4, 5, and 6 are as follows.

k=2: 4 = 2 × 2 = 2 + 2
k=3: 6 = 1 × 2 × 3 = 1 + 2 + 3
k=4: 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
k=5: 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6
k=9995: 10032
Hence for 2≤k≤6, the sum of all the minimal product-sum numbers is 4+6+8+12 = 30; note that 8 is only counted once in the sum.

In fact, as the complete set of minimal product-sum numbers for 2≤k≤12 is {4, 6, 8, 12, 15, 16}, the sum is 61.

What is the sum of all the minimal product-sum numbers for 2≤k≤12000?

#endif

#include <cstdio>
#include <cmath>
#include <algorithm>

#include "vlong.h"
#include "factor.h"

#define DEBUG 1
#define MAXN 200
#define MAX_N_LARGE 999999999

int	kcount[MAXN];

int insert(long k, long N)
{
	int rv = 0;
	if ( (k < 1) || (k >= MAXN)) return 0;
	if (kcount[k] > N) {
		kcount[k] = N;
		rv = N;
		printf("k = %ld   N - %ld\n", k, N);
	}
	return rv;
}
	
	


class minv {
	public:
		minv(int n);
		~minv();
		bool	add(int k, long v);
		long	sum();
		long	uniquesum();
		void    out();
	private:
		int size;
		long *s;
};

void minv::out()
{
	printf("Size: %d  ", size);
	for (int i = 2; i <= size; i++) printf("k = %d  N = %ld\n", i, s[i]);
	printf("\n");
}

minv::~minv()
{
	delete [] s;
}

minv::minv(int n)
{
	size = n;
	s = new long[n+1];
	for (int i = 0; i <= n; i++) s[i] = 0;
}

bool minv::add(int k, long v)
{
	if ( (k > size) || (k < 0) ) return false;
	if ( (s[k] == 0) || (s[k] > v) ) 
	{
		s[k] = v;
		return true;
	}
	return false;
}

long minv::sum()
{
	long ss = 0;
	for (int i = 0; i <= size; i++) ss += s[i];
	return ss;
}

long minv::uniquesum()
{
	long ss = 0;
	vector<long> v(s, s+size);

	vector<long>::iterator ip;
  
    // Sorting the array
    std::sort(v.begin(), v.end());
  
    // Using std::unique
    ip = std::unique(v.begin(), v.end());
  
    // Resizing the vector so as to remove the undefined terms
    v.resize(std::distance(v.begin(), ip));
  
    // Displaying the vector after applying std::unique
    for (ip = v.begin(); ip != v.end(); ++ip) {
        ss += *ip;
    }
  	
	return ss;
}

class prsum {
	public:
		prsum(int maxn);	// create a new n number list
		~prsum();
		long    prod();
		long    sum();
		bool    inc();
		int     len() {return size;};
		void	out();
	private:
		bool    finc();  // first increment n[0]++, reset are twos
		void    shrink();  // shrink size by one, all twos
		bool    xfinc();  // xfirst increment n[0]++, reset are twos
		long	*n;
		int     size;
		int     curidx;
		long    maxProduct;
		long    lead;
		long    depth;
};

bool prsum::xfinc()
{
	n[0]++;
	for (int i = 1; i < size; i++) { n[i] = 2; }
	curidx = 1;
	return (prod() > maxProduct * 2);
}

bool prsum::finc()
{
	n[1]++;
	n[0] = n[1];
	if (prod() > maxProduct * 2)
	{
		// find the first smallest number from left to right
		long smn = n[0];
		int  smi = 0;
		for (int i = 2; i < size; i++) 
		{ 
			if (n[i] < smn) 
			{ 
				smn = n[i]; 
				smi = i; 
				//break;
			}
		}
		// increment smallest number
		
		smn++;
		for (int i = 0; i <= smi; i++) n[i] = smn;
	}
	return (prod() > maxProduct * 2);
}

void prsum::shrink()
{
	size--;
	for (int i = 0; i < size; i++) { n[i] = 2; }
	curidx = 0;
}

void prsum::out()
{
	//printf("Size: %d  Idx: %d  ", size, curidx);
	printf("k = %ld  Prod: %ld  ", prod()-sum()+size, prod());
	for (int i = 0; i < size; i++) printf(" %ld ", n[i]);
	printf("\n");
}

prsum::~prsum()
{
	delete [] n;
}

prsum::prsum(int maxn)
{
	size = log(maxn)/log(2.0)+1;
	n = new long[size];
	maxProduct = maxn;
	curidx = 0;
	for (int i = 0; i < size; i++) { n[i] = 2; }
}

long prsum::prod()
{
	long p = 1;
	for (int i = 0; i < size; i++) p *= n[i];
	return p;
}

long prsum::sum()
{
	long s = 0;
	for (int i = 0; i < size; i++) s += n[i];
	return s;
}

bool    prsum::inc()
{
	n[curidx]++;
	if (prod() > 2*maxProduct)
	{
		if (n[1] > 2)  // reset and add to first
		{
			//out();
			if (finc())
			{
				if (size == 2) return false;
				shrink();
			}
		}
		else if ( (curidx == 0) && (size != 2) ) // reset and add to first
		{
			finc();
		}
		else if (size == 2)  // reset and add to first
		{
			finc();
		}
		else // shirnk
		{
			shrink();
			
		}
	}
	return true;
}

int test(long n)
{
	prsum pr(n);
	minv  mv(n);
	bool  cont = true;
	while (cont)
	{
		long p = pr.prod();
		long s = pr.sum();
		long k = p - s + pr.len();
		mv.add(k, p);
		//printf("k: %ld (%d)    prod: %ld    sum: %ld\n", k, pr.len(), p, s);
		pr.out();
		cont = pr.inc();
	}
	mv.out();
	printf("Min sum-product value for %ld is %ld\n", n, mv.uniquesum());
	//mv.out();
	return 1;
}

int main(int argc, char **argv)
{
	int num = 12000;
	test(num);
	return 1;
	if (argc > 1) num = atoi(argv[1]);
	for (num = 2; num < 100; num++)
	test(num);
	test(100);
	test(1000);
	test(12000);
	return 0;
}
