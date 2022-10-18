
#include <cstdio>
#include <cstring>
//
// 	Step 1:  2 * (l*w + w*h + h*l) = L1
//  Step k:  (2 * k - 2) * (l*w + w*h) + 4 + Lk
// for 1x1x1
// step 0 - 1
// step 1 - 6   (+5)  = 2 * (lw + wh + hl) = 2 * 3 = 6
//
// step 2 - 18  (+12)
//  2 * (lh + wh) + 
//  2 * 5 + 8
//  5 + 2*(3+1) = 13
//
// step 3 - 38  (+20)
//  7 + 2*(5 + 3 + 1) = 25
//
// step 4 - 66  (+28)
//
//  9 + 2*(7 + 5 + 3 + 1) = 41 (66 - 41 = 25)
// 11 + 2*(9 + 7 + 5 + 3 + 1) = 
//
// for 3x2x1
//  Step 0 - 6
//  Step 1 - 22 (+16)
//  Step 2 = 46 (+24)
//  Step 3 = 78 (+32)
//  Step 4 = 118 (+40)

long    L(long l, long w, long h, long &k, long &last)
{
	long lwh = l * w * h;
	if (k == 0)
	{
		last = lwh;
		k = 1;
		return last;
	}
	if (k == 1)
	{
		last = 2 * (l*w + w*h + h*l);
		k++;
		return last;
	}
	//      ones        
	long ones = 4 * (k - 1) * (k - 1);
	long hw = (2 + 4 * (k - 1)) * h * w;
	long hl = (2 + 4 * (k - 1)) * h * l;
	long lw = 2 * l * w;
	
	last =  ones + hw + hl + lw;
	//printf("k: %d  ones: %d  hw: %d  hl: %d  lw: %d  last: %d\n", k, ones, hw, hl, lw, last);
	k++;
	return last;
}
#include <map>
#include <vector>

#define CSIZE 500
#define STARTN 1
#define LARGE 10000
long C[CSIZE];
//std::map<long, long> rec;
typedef struct {
	long	n;
	long count;
} cube_t;

std::vector<cube_t> rec;
void add(long n)
{
	C[n]++; return;
	if (n < STARTN) return;
	for (std::vector<cube_t>::iterator it = rec.begin(); it != rec.end(); it++)
	{
		if (it->n == n) 
		{
			it->count++;
			return;
		}
	}
	cube_t r = {n, 1};
	rec.push_back(r);
}

void init()
{
	memset(C, 0, CSIZE*sizeof(long));
}



void out()
{
	long ix[] = {22, 46, 78, 118, 154};
	for (long i = 0; i < 5; i++)
	    printf("C[%ld] = %ld\n", ix[i], C[ix[i]]);

	for (long  i = 0; i < CSIZE; i++)
	{
		if (C[i]) printf("C[%ld] = %ld\n", i, C[i]);
	}
}
int	xmain()
{
	long	l, w, h, last;
	init();
	for (h = 1; h <= CSIZE; h++)
	{
		for (w = h; w < CSIZE; w++)
		{
			for (l = w; l < CSIZE; l++)
			{
				long k = 0;
				long getL = L(l, w, h, k, last);
				
				while (getL < CSIZE)
				{
					getL = L(l, w, h, k, last);
					if (getL == 22)	printf("getL: %ld   h: %ld  w: %ld  l: %ld\n", getL, h, w, l);
					if (getL == 46)	printf("getL: %ld   h: %ld  w: %ld  l: %ld\n", getL, h, w, l);
					//add(getL);
					if (getL < CSIZE) C[getL]++;
				}
				printf("l: %ld  w: %ld  h: %ld  getL: %ld\n", l, w, h, getL);
			}
		}
	}
	out();
	return 0;
}
			
int main()
{
	long k = 0, last;
	long getL;
	#define J(l,w,h,a)	getL = L(l, w, h, k, last); printf("k: %ld  L: %ld  getKL %ld  (a = %d) %s\n", k, last, getL, a, (a == getL) ? "GOOD": "FAIL");
	J(3, 2, 1, 6);
	J(3, 2, 1, 22);
	J(3, 2, 1, 46);
	J(3, 2, 1, 78);
	J(3, 2, 1, 118);
	xmain();
}	
				
