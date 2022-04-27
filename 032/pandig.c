#include "prime.h"

bool setbit(int a, int &bits)
{
	while (a)
	{
		int	d = 1 << a%10;
		if (d & bits) return true;
		bits |= d;
		a /= 10;
	}
	return false;
}

#define PANDIG 0x3FE

bool ispandig(int a, int b, int pan)
{
	int	bits = 0;
	if (a * b != pan) return false;
	if (setbit(a, bits)) return false; 	
	if (setbit(b, bits)) return false;
	if (setbit(pan, bits)) return false; 
	if ( (bits & PANDIG) == PANDIG) {
		printf("%d * %d = %d !!\n", a, b, pan);
		return true;
	}
	return false;
}


int main()
{
	ispandig(39, 186, 7254);
	ispandig(23, 78, 1794);
	return 1;
}

	
