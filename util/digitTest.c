
#include <stdio.h>
#include "digit.h"
#include "fract.h"
#include "prime.h"
#include "vlong.h"

int main()
{
	long a = 9876543210;
	
	#define ANSWER(n) ( ( ( (n) < 0)  || ( (n) > 9 ) ) ? 0 : (n) )
	
	for (int i = -5; i < 20; i++)
	    if (digit(a, i) == ANSWER(i)) printf("+");
	    else printf("-");
	    
#define FTEST(p, m)	{ fract fr(p1, m * p1);	\
	if (fr.reduced_denominator() != m) { printf("frac denom error"); errcnt++; }}
	
	long p1 = prime_list[32];
	long p2 = prime_list[212];
	long p3 = prime_list[3221];
	long errcnt = 0;
	FTEST(p1, 82);
	FTEST(p2, 612);
	fract fa(p3, p2);
	if (fa.reduced_denominator() != p2) errcnt++;
	if (fa.reduced_numerator() != p3) errcnt++;
	if (errcnt == 0) printf("Successful fract test\n"); 
	else printf("%ld errors found for fract\n", errcnt);
	
	
	return 1;
}


