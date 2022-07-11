#ifdef PROBLEM_DESCRIPTION

Arranged probability


  [Show HTML problem content]  
Problem 100

If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red discs, and two discs were taken at random, it can be seen that the probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.

The next such arrangement, for which there is exactly 50% chance of taking two blue discs at random, is a box containing eighty-five blue discs and thirty-five red discs.

By finding the first arrangement to contain over 10^12 = 1,000,000,000,000 discs in total, determine the number of blue discs that the box would contain.

problem 57 has the repeated fraction for root(2)

   1   b: 3   N: 4
   2   b: 15   N: 21
   3   b: 85   N: 120
   4   b: 493   N: 697
   5   b: 2871   N: 4060
   6   b: 16731   N: 23661
   7   b: 97513   N: 137904
   8   b: 568345   N: 803761
   9   b: 3312555   N: 4684660
  10   b: 19306983   N: 27304197
  11   b: 112529341   N: 159140520
  12   b: 655869061   N: 927538921
  13   b: 3822685023   N: 5406093004
  14   b: 22280241075   N: 31509019101
  15   b: 129858761425   N: 183648021600
  16   b: 756872327473   N: 1070379110497

See this web site to solve generic quadratic diophantine equation:
 A x² + B xy  C y² + D ⁢x + E y + F = 0
https://www.alpertron.com.ar/QUAD.HTM

 2 ⁢x² - y² - 2 ⁢x + y = 0

x = 1
y = 1
and also:

x = 0
y = 0

Recursive solutions:

xn+1 = 3 ⁢xn + 2 ⁢yn - 2 ⁢
yn+1 = 4 ⁢xn + 3 ⁢yn - 3 ⁢

and also:
xn+1 = 3 ⁢xn - 2 ⁢yn
yn+1 = - 4 ⁢xn + 3 ⁢yn +  1

#endif

#include <cstdio>
#include <cmath>


/*
x = 1
y = 1
and also:

x = 0
y = 0

Recursive solutions:

xn+1 = 3 ⁢xn + 2 ⁢yn - 2 ⁢
yn+1 = 4 ⁢xn + 3 ⁢yn - 3 ⁢

and also:
xn+1 = 3 ⁢xn - 2 ⁢yn
yn+1 = - 4 ⁢xn + 3 ⁢yn +  1
*/

void solve(long MAX)
{
	long bn = 1;
	long Nn = 1;
	long bnp1, Nnp1;
	int  cnt = 0;
	
	while (Nn < MAX)
	{
		bnp1 = 3l * bn + 2l * Nn - 2l;
		Nnp1 = 4l * bn + 3l * Nn - 3l;
		bn = bnp1;
		Nn = Nnp1;
		printf("%4d   b: %ld   N: %ld\n", ++cnt, bn, Nn);
	}
}

int main()
{
	solve(1000000000000l);

}
