//
//
/*
he radical of n, rad(n), is the product of the distinct prime factors of n. For example, 504 = 23 × 32 × 7, so rad(504) = 2 × 3 × 7 = 42.

If we calculate rad(n) for 1 ≤ n ≤ 10, then sort them on rad(n), and sorting on n if the radical values are equal, we get:
Unsorted 	  	Sorted
n 	rad(n) 	  	n 	rad(n) 	k
1	1 	  		1	1		1
2	2 	  		2	2		2
3	3 	  		4	2		3
4	2 	  		8	2		4
5	5 	  		3	3		5
6	6 	  		9	3		6
7	7 	  		5	5		7
8	2 	  		6	6		8
9	3 	  		7	7		9
10	10 	  		10	10		10

Let E(k) be the kth element in the sorted n column; for example, E(4) = 8 and E(6) = 9.

If rad(n) is sorted for 1 ≤ n ≤ 100000, find E(10000).
*/
#include "factor.h"

typedef struct {
	long	n;
	long	rad;
} nrad_t;

bool compare(nrad_t &a, nrad_t &b)
{
	if (a.rad < b.rad) return true;
	if (a.rad > b.rad) return false;
	if (a.n < b.n) return true;
	return false;
}

int main()
{
	const int SIZE = 100000;
	const int INDEX =  10000;
	vector<nrad_t>	vr;
	long    n;
	for (n = 1; n <= SIZE; n++)
	{
		factor f(n);
		nrad_t r;
		r.n = n;
		r.rad = f.rad();
		vr.push_back(r);
	}
	sort(vr.begin(), vr.end(), compare);
	printf("%d   %ld\n", INDEX, vr[INDEX-1].n);
}
