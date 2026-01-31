#include <cstdio>
#include <bitset>
#include <iostream>
#include "factor.h"


#define DEBUG 0

//
// returns index into the nth 1 bit in b
int	T(const unsigned long u, size_t n)
{
	std::bitset<12> b(u);
	//cout << "U: " << u << "  " << b << "  n = " << n << std::endl;
	for (size_t i = 0; i < 12; i++)
	{
		if (b[i]) { 
			n--; 
			// printf("i: %d  n: %d\n", i, n); 
		}
		if (n == 0) return i;
	}
	return -1;
}

int test(int nelems)
{
	int	Counter[nelems];
	int maxValue = xpower(2, nelems);
	if (DEBUG) printf("test:: nelems: %d   max: %d\n", nelems, maxValue);
	for (int i = 0; i < nelems; i++) Counter[i] = 0;
	for (int i = 0; i < maxValue - 1; i++)
	{
		for (int j = i+1; j < maxValue; j++)
		{
			std::bitset<12>	bi(i);
			std::bitset<12> bj(j);
			if (DEBUG)
			{
				cout << "i: " << i << "  " << bi << "  cnt: "  << bi.count() << std::endl;
				cout << "j: " << j << "  " << bj << "  cnt: "  << bj.count() << std::endl;
			}
			if ((bi & bj).count() > 0) continue;	// do not include intersecting sets
			if (bi.count() != bj.count()) continue;	// do not include tests when number of set
													// elements are NOT the same
			// the function valid looks at the bits in bi and bj and determines if
			// bi or bj is ordered greater than the other.  what this means is that
			// T(bi, n)) > T(bj, n) for each n, where T is the true bit finder, and
			// T(b, n) is the position of the nth 1 bit in the binary number b
			int	Tbi = 0;
			int	Tbj = 0;
			for (int k = 1; k <= (int) bi.count(); k++)
			{
				if (T(bi.to_ulong(), k) > T(bj.to_ulong(), k)) Tbi++;
				else Tbj++;
			}
			//
			// if Tbj or Tbi is zero, this is NOT a valid set comparison
			if (DEBUG) printf("i: %d (%s) Ti: %d j: %d  (%s) Tj: %d\n", i, bi.to_string().c_str(), Tbi, 
															 j, bj.to_string().c_str(), Tbj);
			if (Tbi == 0) continue;
			if (Tbj == 0) continue;
			Counter[bi.count()]++;
		}
	}
	int	sum = 0;
	for (int k = 0; k < nelems; k++)
	{
		if (Counter[k] == 0) continue;
		printf("Set size: %d    Count: %d\n", k, Counter[k]);
		sum += Counter[k];
	}
	return sum;
}


int main()
{
	//unsigned long g = 41241;
	//for (int k = 1; k < 15; k++)
	//{
	//	printf("k: %d   T: %d\n", k, T(g, k));
	//}
	for (int sz = 4; sz <= 12; sz++)
	{
		int ts = test(sz);
		printf("Set Size: %d    Number of tests: %d\n\n", sz, ts);
	}
}
