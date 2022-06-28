#ifdef PROBLEM_DESCRIPTION

Arithmetic expressions


  [Show HTML problem content]  
Problem 93

By using each of the digits from the set, {1, 2, 3, 4}, exactly once, and making use of the four arithmetic operations (+, −, *, /) and brackets/parentheses, it is possible to form different positive integer targets.

For example,

8 = (4 * (1 + 3)) / 2
14 = 4 * (3 + 1 / 2)
19 = 4 * (2 + 3) − 1
36 = 3 * 4 * (2 + 1)

Note that concatenations of the digits, like 12 + 34, are not allowed.

Using the set, {1, 2, 3, 4}, it is possible to obtain thirty-one different target numbers of which 36 is the maximum, and each of the numbers 1 to 28 can be obtained before encountering the first non-expressible number.

Find the set of four distinct digits, a < b < c < d, for which the longest set of consecutive positive integers, 1 to n, can be obtained, giving your answer as a string: abcd.

#endif

#include <cmath>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

double add(double a, double b) { return a + b;}
double mul(double a, double b) { return a * b;}
double div(double a, double b) { return a / b;}
double sub(double a, double b) { return a - b;}

bool isInt(double a) {if ( fabs(a - trunc(a)) > 0.00001) return false; return true;}

#define MAXSOL 5000
int solutions[MAXSOL];

typedef double op_t(double, double);

op_t *ops[] = {add, mul, sub, div};
char  cops[] = {'+', '*', '-', '/'};

int computefl(int a[], op_t *oparr[], bool debug = false)
{
	double v = oparr[0](a[0], a[1]);
	double u = oparr[2](a[2], a[3]);
	v = oparr[1](v, u);
	
	int ans = (isInt(v)) ? (int)(v+0.5) : -1;
	if (ans > 0)
	{
		solutions[ans]++;
		if (debug) printf("***  (%d %c %d) %c (%d %c %d) = %d\n", a[0], cops[0], a[1], cops[1], a[2], cops[2], a[3], ans);
	}
	return ans;
}

int compute(int a[], op_t *oparr[], bool debug = false)
{
	double v = oparr[0](a[0], a[1]);
	v = oparr[1](v, a[2]);
	v = oparr[2](v, a[3]);
	int ans = isInt(v) ? (int)(v+0.5) : -1;
	if (ans > 0)
	{
		solutions[ans]++;
		if (debug) printf("+++  %d %c %d %c %d %c %d = %d\n", a[0], cops[0], a[1], cops[2], a[2], cops[3], a[3], ans);
	}
	return ans;
}

int produce(int dig[], bool debug = false)
{
	op_t *top[3];
	for (int i = 0; i < 4; i++)
	{
		top[0] = ops[i];
		for (int j = 0; j < 4; j++)
		{
			top[1] = ops[j];
			for (int k = 0; k < 4; k++)
			{
				top[2] = ops[k];
				compute(dig, top, debug);
				computefl(dig, top, debug);
			}
		}
	}
	return 1;
}

int	arith(int a, int b, int c, int d, bool debug = false)
{
	int	arr[] = {a, b, c, d};
	sort(arr, arr+4);
	do {
        produce(arr, debug);
    } while(next_permutation(arr, arr + 4));
    return 1;
}

void init()
{
	for (int i = 0; i < MAXSOL; i++) solutions[i] = 0;
}

void display(int &run, int &max)
{
	for (int i = 1; i < MAXSOL; i++) if (solutions[i]) max = i;
	for (int i = 1; i < MAXSOL; i++) 
	{
		if (solutions[i]) run = i;
		else break;
	}
}
static int gcnt = 0;

int trythis(int a, int b, int c, int d, bool debug = false)
{
	int run, max;
	init();
	arith(a, b, c, d, debug);
	display(run, max);
	gcnt++;
	printf("[%4d] For: {%d,%d,%d,%d}  Run is 1 to %d, max number is %d\n", gcnt, a, b, c, d, run, max);
	return run;
}
		
int main()
{
	//arith(1,2,5,8, true);
	//arith(1,2,5,6, true);
	//return 1;
	int ga, gb, gc, gd, gm = 0;
	for (int a = 1; a <= 6; a++)
	{
		for (int b = a+1; b <= 7; b++)
		{
			for (int c = b+1; c <= 8; c++)
			{
				for (int d = c+1; d <= 9; d++)
				{
					int x = trythis(a, b, c, d);
					if (x > gm)
					{
						ga = a; gb = b; gc = c; gd = d;
						gm = x;
					}
				}
			}
		}
	}
	printf("BEST RUN: {%d,%d,%d,%d}  Run is 1 to %d\n", ga, gb, gc, gd, gm);
	
}
