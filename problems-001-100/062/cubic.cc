#ifdef PROBLEM_DESCIPTION

Cubic permutationsProblem 62

The cube, 41063625 (345^3), can be permuted to produce two other cubes: 56623104 (384^3) and 66430125 (405^3). In fact, 41063625 is the smallest cube which has exactly three permutations of its digits which are also cube.

Find the smallest cube for which exactly five permutations of its digits are cube.

#endif

#include "base10.h"
#include "math.h"
#include <vector>

using namespace std;

//41063625

#define CUBE(x) ((x)*(x)*(x))

long    cube_root(long x)
{
	double xd = pow((double)x, 1.0/3.0) + 0.5;
	long   xl = xd;
	//if (CUBE(xl) == x) printf("%ld is cube root of %ld\n", xl, x);
	return xl;
}

long	getcubes(int p10, vector<base10> &c)
{
	c.clear();
	long  ll = pow(10, (double)p10/3.0) + 0.5;
	long  ul = pow(10, (double)(p10 + 1)/3.0);
	for (long k = ll; k <= ul; k++)
		c.push_back(base10(CUBE(k)));
	return ul - 11 + 1;
}

void    outcubes(vector<base10> &c)
{
	for (size_t k = 0; k < c.size(); k++)
	{
		long  x = c[k].value();
		long  cx = cube_root(x);
		printf("%ld ^ 3    %ld\n", cx, x);
	}
}

void	findperms(vector<base10> &c, vector<base10> &ld)
{
	vector<base10> cd;
	for (size_t k = 0; k < c.size(); k++)
	{
		cd.clear();
		cd.push_back(c[k]);
		for (size_t m = k+1; m < c.size(); m++)
		{
			if (c[k].sameDigits(c[m])) cd.push_back(c[m]);
		}
		if (cd.size() > ld.size()) ld = cd;
	}
}

int main()
{
	vector<base10> c;
	vector<base10> pc;
	for (long k = 7; k < 19; k++)
	{
		pc.clear();
		printf("\n\nPower of 10 is %ld\n", k);
		getcubes(k, c);
		findperms(c, pc);
		outcubes(pc);
	}
}
		
