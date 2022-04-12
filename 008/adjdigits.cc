#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int	nextdigit(FILE *f)
{
	int	c;
	while (!feof(f))
	{
		c = fgetc(f);
		if (isdigit(c)) return c - '0';
	}
	return -1;
}

long prod(long *l, int n)
{
	long p = 1;
	for (int i = 0; i < n; i++) p *= l[i];
	return p;
}

long nextprod(long *nvalues, int &lvindex, int nvsize, FILE *f)
{
	lvindex = (lvindex + 1) % nvsize;
	long nd = nextdigit(f);
	if (nd < 0) return -1;
	nvalues[lvindex] =  nd;
	return prod(nvalues, nvsize);
}

int main(int argc, char **argv)
{
	FILE *f = fopen("digits.txt", "r");
	int  sz = 13;
	long *values = (long *)calloc(sizeof(long), sz);
	long *max_values = (long *)calloc(sizeof(long), sz);
	long max_prod = 1;
	long nprod = 1;
	int	 index = 0;
	while (nprod >= 0)
	{
		nprod = nextprod(values, index, sz, f);
		if (nprod > max_prod) {
			max_prod = nprod;
			memcpy(max_values, values, sz * sizeof(long));
		}
	}
	printf("Values: ");
	for (int i = 0; i < sz; i++) printf(" %ld", max_values[i]);
	printf("\nProduct: %ld\n", max_prod);
	return 1;
}
