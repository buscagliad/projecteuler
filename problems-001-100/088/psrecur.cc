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

NOTE: we generate all sequences of numbers a1 >= a2 >= a3 ... >= an
for n = 2 ... log(max) * 2 / log(n) (we actually just iterate until 2^n > 2 * max

then we compute product(ai) and sum(ai) and  then comput how many ones will it take to 
add to sequence to make the sum and product equal (note: the product does not change
by adding ones, only the sum).  Once they are equal, we have N (the product) and
k = (current) n + number of ones

we keep the smallest N value for each k, the sum over the UNIQUE Ns

ALSO - stack size must be increased to ulimit -s 1000000
smaller values might work, but, 1000000 worked.

#endif

#include <cstdio>
#include <cmath>
#include <algorithm>

#include "vlong.h"
#include "factor.h"

#define DEBUG 0
using namespace std;

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



void rec(minv &mv, vlong_t &v, int &max)
{
	long p = product(v);
	long s = sum(v);
	long k = p - s + v.size();
	mv.add(k, p);
	if (DEBUG) vl_out(v);
	v[0]++;
	if (product(v) < max)
	{
		//rec(v, index+1, max);
		rec(mv, v, max);
	}
	else
	{
		bool found = false;
		for (size_t i = 1; i < v.size(); i++)
		{
			v[i]++;
			for (size_t j = 0; j < i; j++)
		        v[j] = v[i];
		    if (product(v) < max) {
				found = true;
				break;
			}
		}
		if (!found) return;
		rec(mv, v, max);
	}
}

int main(int argc, char **argv)
{
	long maxn = 12000;
	minv  mv(maxn);
	for (int index = 2; index < 14; index++)
	{
		vlong_t v(index, 2);
		if(product(v) > 2*maxn) break;
		int max2 = 2*maxn;
		rec(mv, v, max2);
	}
	if (DEBUG) mv.out();
	printf("Min sum-product value for %ld is %ld\n", maxn, mv.uniquesum());

	return 1;
}
