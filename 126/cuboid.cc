
#include <cstdio>
#include <cstring>

int	f(int l, int w, int h, int k)
{
	return (l * w * h + 2) * (k + 1);
}

int    L(int l, int w, int h, int &k, int &last)
{
	int lwh = l * w * h;
	if (k == 0)
	{
		last = lwh;
		k = 1;
		return last;
	}
	k++;
	last += (lwh + 2) * k;
	return last;
}

#define CSIZE 1000
int	C[CSIZE];
void init()
{
	memset(C, 0, CSIZE*sizeof(int));
}

void out()
{
	for (int  i = 0; i < CSIZE; i++)
	{
		if (C[i]) printf("C[%d] = %d\n", i, C[i]);
	}
}

int	main()
{
	int	l, w, h, last;
	init();
	for (h = 1; h < CSIZE; h++)
	{
		for (l = h; l < CSIZE; l++)
		{
			for (w = l; w < CSIZE; w++)
			{
				int k = 0;
				int getL = L(l, w, h, k, last);
				if (getL < CSIZE)	printf("getL: %d   C[%d] =  %d\n", getL, getL, C[getL]);
				while (getL < CSIZE)
				{
					if (getL > CSIZE) break;
					C[getL]++;
					getL = L(l, w, h, k, last);
				}
			}
		}
	}
	out();
}
				
				
