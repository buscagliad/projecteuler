
#include <cstdio>
#include <cmath>
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

int    L(int l, int w, int h, int k, int &last)
{
	if (k == 0)
	{
		int lwh = l * w * h;
		last = lwh;
		return last;
	}
	int layer1 = 2 * (l*w + w*h + h*l);
	if (k == 1)
	{
		last = layer1;
		return last;
	}
	//      ones       
	//cubes = 2(ab+ac+bc) + 4(n-1)(x+y+z) + 4(n-1)(n-2) 
	int ones = 4 * (k - 1) * (k - 2);
	int hpwpl = 4 * (k - 1) * (h + l + w);
	
	last =  ones + hpwpl + layer1;
	if ((last == 130) || (last == 154)) printf("k: %d  ones: %d  hpwpl: %d   lwh: %d last: %d\n", k, ones, hpwpl, layer1, last);
	return last;
}
#include <map>
#include <vector>

#define CSIZE 1000000
int C[CSIZE];

void init()
{
	memset(C, 0, CSIZE*sizeof(int));
}

void out(int x)
{
	for (int  i = 0; i < CSIZE; i++)
	{
		if (C[i] == x) {
			printf("C[%d] = %d\n", i, C[i]);
			return;
		}
	}
}

int croot(int x)
{
	int y = log(x) / 3 + 2;
	return y;
}

int	xmain()
{
	int	l, w, h, last;
	init();
	//int hmax = croot(CSIZE);
	//int wmax = sqrt(CSIZE) + 2;
	//int lmax = CSIZE;
	for (h = 1; L(h, h, h, 1, last) <= CSIZE; h++)
	{
		for (w = h; L(w, w, h, 1, last) <= CSIZE; w++)
		{
			for (l = w; L(l, w, h, 1, last) <= CSIZE; l++)
			{
				int k = 0;
				int getL = L(l, w, h, k, last);
				
				while (getL < CSIZE)
				{
					k++;
					getL = L(l, w, h, k, last);
					if (getL == 130)	printf("getL: %d   h: %d  w: %d  l: %d\n", getL, h, w, l);
					if (getL == 154)	printf("getL: %d   h: %d  w: %d  l: %d\n", getL, h, w, l);
					//if (getL == 46)	printf("getL: %d   h: %d  w: %d  l: %d\n", getL, h, w, l);
					//add(getL);
					if (getL < CSIZE) C[getL]++;
				}
				//printf("l: %d  w: %d  h: %d  getL: %d\n", l, w, h, getL);
			}
		}
	}
	int ix[] = {2, 4, 5, 8, 10};
	for (int i = 0; i < 5; i++)
	    out(ix[i]);
	    
	out(1000);
	return 0;
}
			
int main()
{
	int k = 0, last;
	int getL;
	#define J(l,w,h,a)	getL = L(l, w, h, k++, last); printf("k: %d  L: %d  getKL %d  (a = %d) %s\n", k, last, getL, a, (a == getL) ? "GOOD": "FAIL");
	J(3, 2, 1, 6);
	J(3, 2, 1, 22);
	J(3, 2, 1, 46);
	J(3, 2, 1, 78);
	J(3, 2, 1, 118);
	return xmain();
}	

