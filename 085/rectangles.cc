#ifdef PROBLEM_DESCRIPTION


#endif

#include <cstdio>

int   rect(int n, int m)
{
	int sum = 0;
	for (int p = 1; p <= n; p++)
	{
		for (int q = 1; q <= m; q++)
		{
			sum += (n - p + 1) * (m - q + 1);
		}
	}
	return sum;
}

typedef struct _rectres{
	int	n;
	int m;
	int numrects;
} rectres_t;

typedef struct _results{
	rectres_t low;
	rectres_t high;
} results_t;

#define TARGET 2000000

int get_res(int n, results_t &r)
{
	r.low.n = n;
	r.high.n = n;
	r.high.numrects = 0;
	r.high.m = 10;
	while(r.high.numrects < TARGET)
	{
		r.low.m = r.high.m;
		r.high.m++;
		r.low.numrects = r.high.numrects;
		r.high.numrects = rect(n, r.high.m);
	}
	return r.high.m;
}

void outrect(rectres_t &r, const char *t)
{
	printf("%s  n: %d  m: %d   #rects: %d\n", t, r.n, r.m, r.numrects);
}

void outres(results_t &r)
{
	outrect(r.low, "LOW ");
	outrect(r.high, "HIGH");
}
		
// LOW   n: 36  m: 77   #rects: 1999998
// HIGH  n: 3  m: 816   #rects: 2000016

int main()
{
	// find first rect as a 1 x N
	results_t answer;
	results_t nres;
	get_res(1, answer);
	int maxn = answer.high.m;
	for (int n = 2; n < maxn; n++)
	{
		get_res(n, nres);
		if (nres.low.numrects > answer.low.numrects)
		    answer.low = nres.low;
		if (nres.high.numrects < answer.high.numrects)
			answer.high = nres.high;
	}
	outres(answer);
	printf("6,9: %d   9,6: %d\n", rect(6,9), rect(9,6));
}
