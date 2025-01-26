/*

Special isosceles triangles

Problem 138

Consider the isosceles triangle with base b, height h and  legs L
By using the Pythagorean theorem it can be seen that 

L^2 = (b/2)^2 + h^2.

Consider all such integer solutions where the height and base differ by one:

that is:   h = b + 1    or    h = b - 1

Two such solutions:  (h, b, L) = (15, 16, 17)  :: b = h + 1
                               = (273, 272, 305)  :: b = h - 1


Find sum(L) for the twelve smallest isosceles triangles satisfying the above.

-----------------------------------------------------------------------------
Using this webiste for diophantine equation solutions:

https://www.alpertron.com.ar/QUAD.HTM


Case 1:   h = b + 1

L^2 = (b/2)^2 + (b+1)^2

Results in the diophantine equation:

4L^2 - 5b^2 - 8b - 4 = 0

4 ⁢L² - 5 ⁢b² - 8 ⁢b - 4 ⁢ = 0
2
L = 1
b = 0

Recursive solutions:

Using these variables in C program for this recursion:
L1, b1, l1p, b1p::

Ln+1 = - 9 ⁢Ln - 10 ⁢bn - 8 ⁢
bn+1 = - 8 ⁢Ln - 9 ⁢bn - 8 ⁢

and also:

Using these variables in C program for this recursion:
L2, b2, l2p, b2p::


Ln+1 = - 9 ⁢Ln + 10 ⁢bn + 8 ⁢
bn+1 = 8 ⁢Ln - 9 ⁢bn - 8 ⁢ 


Case 2:  h = b - 1

L^2 = (b/2)^2 + (b-1)^2

Results in the diophantine equation:

 4 ⁢L² - 5 ⁢b² + 8 ⁢b - 4 ⁢ = 0

L = -1
b = 0

Recursive solutions:

Using these variables in C program for this recursion:
L3, b3, l3p, b3p::

Ln+1 = - 9 ⁢Ln - 10 ⁢bn + 8 ⁢
bn+1 = - 8 ⁢Ln - 9 ⁢bn + 8 ⁢

and also:
Using these variables in C program for this recursion:
L4, b4, l4p, b4p::

Ln+1 = - 9 ⁢Ln + 10 ⁢bn - 8 ⁢
bn+1 = 8 ⁢Ln - 9 ⁢bn + 8 ⁢ 

*/

#include <cstdio>

long L1=1, b1=0, L1n, b1n;
long L2=1, b2=0, L2n, b2n;
long L3=-1, b3=0, L3n, b3n;
long L4=-1, b4=0, L4n, b4n;
long sumL = 0;
int  count = 0;

long iter(long xn, long yn, long xs, long ys, long c)
{
	return xn * xs + yn * ys + c;
}

void ADD(long L, long b)
{
	if (L <= 0) return;
	if (b <= 0) return;
	sumL += L;
	count++;
	printf("%2d  L: %ld   b: %ld    SUM: %ld\n", count, L, b, sumL);
}

void update()
{
	L1n = iter(L1, b1, -9, -10, -8);
	b1n = iter(L1, b1, -8, -9, -8);
	L1 = L1n;
	b1 = b1n;
	ADD(L1, b1);
	
	L2n = iter(L2, b2, -9, 10, 8);
	b2n = iter(L2, b2, 8, -9, -8);
	L2 = L2n;
	b2 = b2n;
	ADD(L2, b2);
	
	L3n = iter(L3, b3, -9, -10, 8);
	b3n = iter(L3, b3, -8, -9, 8);
	L3 = L3n;
	b3 = b3n;
	ADD(L3, b3);
	
	L4n = iter(L4, b4, -9, 10, -8);
	b4n = iter(L4, b4, 8, -9, 8);
	L4 = L4n;
	b4 = b4n;
	ADD(L4, b4);
}

int	main()
{
	while(count < 12)
	    update();
}

	
	
	
	
