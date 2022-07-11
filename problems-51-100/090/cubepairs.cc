#ifdef PROBLEM_DESCRIPTION


Each of the six faces on a cube has a different digit (0 to 9) written on it; the same is done to a second cube. By placing the two cubes side-by-side in different positions we can form a variety of 2-digit numbers.

For example, the square number 64 could be formed:

In fact, by carefully choosing the digits on both cubes it is possible to display all of the square numbers below one-hundred: 01, 04, 09, 16, 25, 36, 49, 64, and 81.

For example, one way this can be achieved is by placing {0, 5, 6, 7, 8, 9} on one cube and {1, 2, 3, 4, 8, 9} on the other cube.

However, for this problem we shall allow the 6 or 9 to be turned upside-down so that an arrangement like {0, 5, 6, 7, 8, 9} and {1, 2, 3, 4, 6, 7} allows for all nine square numbers to be displayed; otherwise it would be impossible to obtain 09.

In determining a distinct arrangement we are interested in the digits on each cube, not the order.

{1, 2, 3, 4, 5, 6} is equivalent to {3, 6, 4, 1, 2, 5}
{1, 2, 3, 4, 5, 6} is distinct from {1, 2, 3, 4, 5, 9}

But because we are allowing 6 and 9 to be reversed, the two distinct sets in the last example both represent the extended set {1, 2, 3, 4, 5, 6, 9} for the purpose of forming 2-digit numbers.

How many distinct arrangements of the two cubes allow for all of the square numbers to be displayed?


#endif

#include <cstdio>
#include <cstring>

int	sq[][2] = { {0, 0},
				{0, 1},
				{0, 4},
				{0, 9},
				{1, 6},
				{2, 5},
				{3, 6},
				{4, 9},
				{6, 4},
				{8, 1} };

bool isin(int *d, int n)
{
	for (int i = 0; i < 6; i++)
	{
		if (n == d[i]) return true;
		if ( (n * d[i]) == 54) return true;
	}
	return false;
}

bool goodsq(int *d1, int *d2, int *n)
{
	return isin(d1, n[0]) && isin(d2, n[1]);
}
				
bool valid(int *d1, int *d2)
{
	for (int s = 1; s <= 9; s++)
	{
		if ( goodsq(d1, d2, sq[s]) || goodsq(d2, d1, sq[s]) ) continue;
		return false;
	}
	return true;
}

void   out(const char *s, int *d)
{
	printf("%s : {%d, %d, %d, %d, %d, %d}   ",
		s, d[0], d[1], d[2], d[3], d[4], d[5]);
}

static int cnt = 1;
bool	test(int *d1, int *d2)
{
	printf("%4d  ", cnt++);
	out("Dice 1", d1);
	out("Dice 2", d2);
	bool rv = valid(d1, d2);
	printf("  -  VALID: %s\n",  rv ? "YES" : "NO");
	return rv;
}

bool	incDie(int *d)
{
	if (d[5] == 0)
	{
		d[0] = 0;
		d[1] = 1;
		d[2] = 2;
		d[3] = 3;
		d[4] = 4;
		d[5] = 5;
		return true;
	}
	for (int i = 5; i >= 0; i--)
	{
		if (d[i] < 4 + i)
		{
			d[i]++;
			for (int j = i+1; j < 6; j++)
				d[j] = d[j-1] + 1;
			return true;
		}
	}

	return false;
}

int main()
{
	int d1[6];
	int d2[6];
	d1[5] = 0;
	int valid_die_sets = 0;
	while (incDie(d1))
	{
		//d2[5] = 0;
		memcpy(d2, d1, sizeof(int) * 6);
		while(incDie(d2))
		{
			if (test(d1, d2)) valid_die_sets++;
		}
	}
	printf("Number of valid die sets: %d\n", valid_die_sets);
}
	
