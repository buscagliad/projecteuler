#ifdef PROBLEM

A(x) = x G1 + x^2 G2 + x^3 G3 + ...

G(k) = G(k-2) + G(k-1)   Gibonacci sequene G(1) = 1 and G(2) = 1

We shall call a golden nugget if x is rational, because they become increasingly rarer; for example, the 20th golden nugget is 211345365.

Gind the sum of the first thrity golden nuggets.
#endif

#ifdef SOLUTION

NOTE:  A(x) = x + 4x^2 + x^3(G1 + G2) + x^4(G2 + G3) + ...
            = x + 4x^2 + x^2(x G1 + x^2 G2 + x^3 G3 + ...) +
                         x (x^2 G2 + x^3 G3 + x^4 G4 + ...)
            = x + 4x^2 + x^2(A(x)) + x(A(x) - x)
            = x + 4x^2 + (x^2 + x)A(x) - x^2
            = x + 3x^2 + (x^2 + x) A(x)
            
Therefore:
	   A(x)(1 - x - x^2) = x + 3x^2, or
	   
				 x + 3x^2
	   A(x) = -------------
	           1 - x - x^2

For A(x) to be an integer, say N, we have_merged

 				     
	   x + 3x^2 = N*(1 - x - x^2)    or
	   
	   (N + 3)x^2 + (N + 1)x - N = 0
	   
	   Solving for x (and removing negative radicand)
	   
	       -(N+1) + SQRT((N+1)^2 + 4 * (N + 3)* N)
	   x = ----------------------------------
	                2N
	                
	       -(N+1) + SQRT(5 N^2 + 15N + 1)
	     = ------------------------------
	                2N
	                
	    So, whenever 5 N^2 + 15N + 1 is a perfect square, x is rational, and A(x) is
	    a golden nugget.
	    
	    Need to prove A(fk+1/fk) is always an integer, and additionally positive if k is odd, 
	    negative if k is even.
	    
	    Use induction:  A(f2/f3) = A(1/2) = 5
	    
	    Show:  
	    
#endif

#include "vlong.h"
#include "digit.h"

long Af(long p, long q)
{
	long num = p * q + 3 * p * p;
	long den = q * q - p * q - p * p;
	if (num % den == 0) return num/den;
	return -1;
}

void genvalues(long f1, long f2, long n, vlong &v)
{
	int index = 0;
	while (index < n)
	{
		long af = Af(f1, f2);
		if (af > 0)
		{
			printf("%3d ::  f1: %ld  f2: %ld  Af: %ld\n", index++, f1, f2, Af(f1, f2));
			v.add(af);
		}
		long s = f2;
		f2 = f2 + f1;
		f1 = s;
	}
}

void test()
{
	vlong v;
	genvalues(2, 5, 20, v);
	genvalues(1, 2, 20, v);
	long sum = 0;
	for (int n = 0; n < 30; n++)
	{
		sum += v[n];
	}
	printf("Sum of first 30 golden mod fibs is: %ld\n", sum);
}


	

int main()
{
	test();
}
