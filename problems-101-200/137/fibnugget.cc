#ifdef PROBLEM

A(x) = x F1 + x^2 F2 + x^3 F3 + ...

F(k) = F(k-2) + F(k-1)   Fibonacci sequene F(1) = 1 and F(2) = 1

We shall call A(x) a golden nugget if x is rational, and A(x) is an integer.  
the 10th golden nugget is 74049690.

Find the 15th golden nugget.

#endif

#ifdef SOLUTION

NOTE:  A(x) = x + x^2 + x^3(F1 + F2) + x^4(F2 + F3) + ...
            = x + x^2 + x^2(x F1 + x^2 F2 + x^3 F3 + ...) +
                         x (x^2 F2 + x^3 F3 + x^4 F4 + ...)
            = x + x^2 + x^2(A(x)) + x(A(x) - x)
            = x + x^2 + (x^2 + x)A(x) - x^2
            = x + (x^2 + x) A(x)
            
Therefore:
	   A(x)(1 - x - x^2) = x, or
	   
				     x
	   A(x) = ----------------
	           1 - x - x^2

For A(x) to be an integer, say N, we have_merged

 				     
	   x = N*(1 - x - x^2)    or
	   
	   N x^2 + (N + 1)x - N = 0
	   
	   Solving for x (and removing negative radicand)
	   
	       -(N+1) + SQRT((N+1)^2 - 4 * N * N)
	   x = ----------------------------------
	                2N
	                
	       -(N+1) + SQRT(5 N^2 + 2N + 1)
	     = ------------------------------
	                2N
	                
	    So, whenever 5 N^2 + 2N + 1 is a perfect square, x is rational, and A(x) is
	    a golden nugget.
	    
	    Need to prove A(fk+1/fk) is always an integer, and additionally positive if k is odd, 
	    negative if k is even.
	    
	    Use induction:  A(f2/f3) = A(1/2) = 2
	    
	    Show:  
	    
#endif

#include "digit.h"

long Af(long fk, long fkp1)
{
	long num = fk * fkp1;
	long den = fkp1 * fkp1 - fk * fkp1 - fk * fk;
	return num/den;
}

void test()
{
	long f1 = 1;
	long f2 = 2;
	int index = 1;
	for (int n = 1; n <= 35; n++)
	{
		long af = Af(f1, f2);
		if (af > 0)
		{
			printf("%3d ::  f1: %ld  f2: %ld  Af: %ld\n", index++, f1, f2, Af(f1, f2));
		}
		long s = f2;
		f2 = f2 + f1;
		f1 = s;
	}
}


	

int main()
{
	test();
}
