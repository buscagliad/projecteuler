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
	    
#endif

#include "digit.h"

int main()
{
	long N;
	long rad;
	
	for (N = 74049690; ; N++)
	

