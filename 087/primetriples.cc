#ifdef PROBLEM_DESCRIPTION

Prime power triples


  [Show HTML problem content]  
Problem 87

The smallest number expressible as the sum of a prime square, prime cube, and prime fourth power is 28. In fact, there are exactly four numbers below fifty that can be expressed in such a way:^

28 = 2^2 + 2^3 + 2^4
33 = 3^2 + 2^3 + 2^4
49 = 5^2 + 2^3 + 2^4
47 = 2^2 + 3^3 + 2^4

How many numbers below fifty million can be expressed as the sum of a prime square, prime cube, and prime fourth power?

#endif

#include "prime.h"
#include "vlong.h"

vlong psqr;
vlong pcube;
vlong pquad;


#define TARGET 50000000
#define MAXNUM TARGET
bool  counter[MAXNUM];

int   count()
{
	int rv = 0;
	for (int i = 0; i < MAXNUM; i++) if (counter[i])rv++;
	return rv;
}

void init()
{
	Prime p;
	long  v = 2;
	bool done = false;
	for (int i = 0; i < MAXNUM; i++)counter[i] = false;
	while (!done)
	{
		long pv = v * v;
		//printf("v = %ld   pv = %ld\n", v, pv);
		if (pv < TARGET)
			psqr.add(pv);
		else
			done = true;
		pv *= v;
		if (pv < TARGET)
			pcube.add(pv);
		pv *= v;
		if (pv < TARGET)
			pquad.add(pv);
		v = p.next();
	}
	printf("Square list is %lu elements\n", psqr.size());
	printf("Cube list is %lu elements\n", pcube.size());
	printf("Quad list is %lu elements\n", pquad.size());
}

vlong	list(true);
void run()
{
	for (vlong_it s = psqr.begin(); s != psqr.end(); s++)
	{
		for (vlong_it c = pcube.begin(); c != pcube.end(); c++)
		{
			long csum = *s + *c;
			if (csum > TARGET) break;
			for (vlong_it q = pquad.begin(); q != pquad.end(); q++)
			{
				long qsum = csum + *q;
				if (qsum > TARGET) break;
				if (list.exists(qsum)) continue;
				counter[qsum] = true;
				//printf("%ld Added %ld\n", list.size(), qsum);
			}
		}
	}
	printf("%d size of prime triple sums\n", count());
}
	
	
int main()
{
	init();
	run();
}
