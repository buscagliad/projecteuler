//#include <bits/stdc++.h>
#include <cstdarg>
#include <algorithm>

#include "vlong.h"
#include "factor.h"

using namespace std;

int	nextSum(int *set, int setSize, int mask)
{
	int sum = 0;
	for (int j = 0; j < setSize; j++) {
		if ((mask & (1 << j)) != 0)
			sum += set[j];
	}
	//printf("setSize: %d  mask:%d, sum: %d\n",
	//	setSize, mask, sum);
	return sum;
}

int	setSum(int *set, int setSize)
{
	int sum = 0;
	for (int j = 0; j < setSize; j++) {
		sum += set[j];
	}
	return sum;
}


bool addnew(int *a, int N, int value)
{
	for (int i = 0; i < N; i++)
	{
	    if (a[i] == value) 
	    {
			//printf("value %d found twice\n", value);
			return false;
		}
	}
	a[N] = value;
	return true;
}

//
// checks for special sets by adding all combinations
// checking for any duplicates - any duplicate would be a fail (false)
// also, need to ensure that S(B) > S(C) whenever count(B) > count(C)
// and B and C are disjoint.  To do this, since the set is ordered,
// we only need to look at S(B) < S(C) when C is the last N elements,
// and C is the first N+1 elements, we do this for N = 2, 3, until
// it does not make sense anymore, as B and C have to be disjoint

//
// vsum returns the sum of elements from s starting and index si
// up to and include index ei
int	vsum(int *s, int si, int ei)
{
	int sum = 0;
	for (int i = si; i <= ei; i++) sum += s[i];
	return sum;
}

bool isSpecialSet(int *set, int setSize, bool dump = false)
{
	int numSubs = xpower(2, setSize);
	int	setSums[numSubs];
	for (int k = 0; k < numSubs; k++) setSums[k] = 0;
	for (int mask = 1; mask < numSubs; mask++)
		if (!addnew(setSums, mask-1, nextSum(set, setSize, mask)))
			return false;
			
	// check for condition 2
	//
	for (int k = 2; k <= setSize/2; k++)
	{
		int ss = vsum(set, 0, k);
		int ls = vsum(set, setSize - k, setSize - 1);
		if (ss <= ls)
		{
			//printf("SUM(%d,%d) = %d    SUM(%d,%d) = %d\n", 0, k, ss, setSize - k, setSize - 1, ls);
			return false;
		}
	}
	if (dump)
	{
		sort(setSums, setSums + numSubs);
		printf("setsums: {%d", setSums[0]);
		for (int i = 1; i < numSubs; i++) 
			printf(",%d", setSums[i]);
		printf("} ");
	}
	return true;
}

bool validSet(int *s, int n)
{
	for (int i = 0; i < n - 1; i++)
	    if (s[i] >= s[i+1]) return false;
	return true;
}

void trial(int num,...) {
	va_list valist;
	int i;
	int arr[num];

	/* initialize valist for num number of arguments */
	va_start(valist, num);

	/* access all the arguments assigned to valist */
	for (i = 0; i < num; i++) {
		arr[i] = va_arg(valist, int);
	}

	/* clean memory reserved for valist */
	va_end(valist);

	printf("set: {%d", arr[0]);
	for (i = 1; i < num; i++) 
		printf(",%d", arr[i]);
	printf("} ");
	if (isSpecialSet(arr, num))
		printf("     is a Special Set  S(N) = %d\n", setSum(arr, num));
	else
		printf("     is NOT a special set\n");
}

/*
-1           // rotate that thru
-1, -1, 1    // rotate that thru
-2, 1        // rotate that thru
-2, -1, 1, 1
* */
//
// a += u
//
void update(int *a, int *u, int n)
{
	for (int i = 0; i < n; i++)
	    *a++ += *u++;
}

//
// a = u
//
void assign(int *a, int *u, int n)
{
	for (int i = 0; i < n; i++)
	    *a++ = *u++;
}

void trial2(int  num,...) {
	va_list valist;
	int i;
	num++;
	int arr[num];

	/* initialize valist for num number of arguments */
	va_start(valist, num);

	/* access all the arguments assigned to valist */
	arr[0] = 0;
	for (i = 1; i < num; i++) {
		arr[i] = va_arg(valist, int);
	}

	/* clean memory reserved for valist */
	va_end(valist);

	int narr[num];

	int mid = arr[4];
	for (i = 0; i < num; i++) 
		narr[i] = arr[i] + mid;;
	printf("set: {%d", narr[0]);
	for (i = 1; i < num; i++) 
		printf(",%d", narr[i]);
	printf("} ");
	if (isSpecialSet(narr, num, true))
		printf("     is a Special Set  S(N) = %d\n", setSum(narr, num));
	else
		printf("     is NOT a special set\n");
	
}

//
// incseq produces a vector of length N (returned in v) with
// elements such that v[i] < v[j] whenever i < j, anv 
// each element is a natural number.
// starting with y = 0, it will return a vector v with its
// elements starting with 1, 2, ..., N, subsequent
// calls will return a differnt set by incrementing/decrementing one
// or more values in the v array.  Each time incseq is called, a check
// is made to see if the sum of the values of incseq exceed the value
// maxSum, if so, a incseq will adjust the arry to maintain a sum
// at or below maxSum, if no such rearrangement can be made, false
// is returned as all possible combinations have been created.
//

void    incvec(int *v, int N)
{
	int	i = 0;
	for (i = 1; i < N; i++)
	{
		if ( (v[i-1] - v[i]) == 1) continue;
	}
	v[i-1]++;
}


int SUM(int *v, int N)
{
	int sum = 0;
	for (int i = 0; i < N; i++) sum += v[i];
	return sum;
}

#define PVEC(a, n, s)	printf("[%d] Vec: ", __LINE__); 					\
						for (int k = 0; k < n; k++) 					\
						printf("%d ", a[k]);							\
						printf("  = %d\n", s);

bool	incseq(int *v, int N, int maxSum)
{
	v[N-1]++;
	//PVEC(v, N, -100);
	int sum = SUM(v, N);
	if (sum <= maxSum)
	{
		return true;
	}
	else
	{
		while (sum > maxSum)
		{
			sum = 0;
			for (int i = N-2; i >= 0; i--)
			{
				if (v[i+1] - v[i] > 1)
				{
					v[i]++;
					for (int j = i+1; j < N; j++)
						v[j] = v[j-1] + 1;
					sum = SUM(v, N);
					//PVEC(v, N, sum);
					if (sum <= maxSum) return true;
				}
			}
		}
		return false;
	}
	return false;
}
	
//
// cmbvec produces a vector of length N (returned in v) made up
// of elements from the set offsets of Ni < N values
// starting with y = 0, it will return a vector v with its
// first Ni elements set to the values if offsets, subsequent
// calls will set the values at different places in v 
// until all posible combinations of places have been achieved,
// at when that happens, cmbvec returns a false value indiating
// it has been called enough time to produce all such possible
// combinations.
// NOTE":  this function does not account for duplicate values
//         in the offset array
//
bool	cmbvec(int *v, int N, int *offsets, int Ni, int &y)
{
	int c = y;
	y++;
	bool rv = true;
	int maxy = 1;
	int ix[Ni];
	//printf("y: %d   v[N-Ni]: %d   offsets[Ni-1]: %d\n", y, v[N-Ni], offsets[Ni-1]);
	//if (v[N-Ni] == offsets[Ni-1]) return false;
	for (int i = 0; i < N; i++) v[i] = -1;
	// y = ix[0] + ix[1] * N + ix[2] * N ^ 2 + ... + ix[Ni - 1] * N ^ (Ni - 1)
	// y represents the position and index of each of the indeces into v with values
	// from the array is
	int powerN = 1;
	for (int i = 0; i < Ni; i++)
	{
		ix[i] = c % N;
		//printf("i: %d  ix[%d] = %d  c: %d\n", i, i, ix[i], c);
		c = c / N;
		maxy += (N - Ni + i) * powerN;
		powerN *= N;
	}
	// printf("maxy = %d\n", maxy);
	if (y > maxy) return false;
	
	for (int i = 0; i < Ni; i++)
	{
		if (v[ix[i]] != -1) // this means we have already put a number here
		{
			rv = false;
			break;
		}
		v[ix[i]] = offsets[i];
	}
	for (int i = 0; i < N; i++) if (v[i] == -1) v[i] = 0;
	if (!rv) cmbvec(v, N, offsets, Ni, y);
	//printf("maxy: %d  ", maxy);
	//printf("Index: "); for (int i = 0; i < Ni; i++) printf("%d ", ix[i]);
	//printf("   Vector: "); for (int i = 0; i < N; i++) printf("%d ", v[i]);
	//printf("\n");
	return true;
}
	

void test()
{
	trial(2, 1, 2);
	trial(3, 2, 3, 4);
	trial(4, 3, 5, 6, 7);
	trial(5, 6, 9, 11, 12, 13);
	trial(6, 11, 17, 20, 22, 23, 24);
	trial(6, 11, 18, 19, 20, 22, 25);
	trial(6, 7, 8, 9, 10, 11, 12);
	//trial2(6, 11, 18, 19, 20, 22, 25);
	trial(7,20,31,38,39,40,42,45);
	trial(7,19,31,38,39,40,42,45);
	trial(7,20,30,38,39,40,42,45);
	trial(7,20,31,37,39,40,42,45);
	trial(7,20,31,38,39,40,41,45);
	trial(7,20,31,38,39,40,42,44);
	trial(7,18,32,38,39,40,42,45);
}

void testv()
{
	int v[7];
	int dv[] = {1, 2, 3, 4};
	int y = 0;
	for (int Ni = 1; Ni <= 4; Ni++)
	{
		y = 0;
		while (cmbvec(v, 7, dv, Ni, y))
		{
			printf("y = %d   v: ", y);
			for (int i = 0; i < 7; i++) printf("%d ", v[i]);
			printf("\n");
		}
	}
}

void test55()
{
	trial(6, 11, 17, 20, 22, 23, 24);
	int v[6] = {11, 17, 20, 22, 23, 24};
	int dv[] = {-2, 1};

	for (int Ni = 2; Ni <= 2; Ni++)
	{
		int y = 0;
		while (cmbvec(v, 7, dv, Ni, y))
		{
			printf("y = %d   v: ", y);
			for (int i = 0; i < 7; i++) printf("%d ", v[i]);
			printf("\n");
		}
	}
}	


void test8()
{
	int v[] = {1, 2, 3, 4, 5, 6};
	int n = 0;
	#define VECSIZE 5
	while (incseq(v, VECSIZE, 20) && n++ < 100)
	{
		PVEC(v, VECSIZE, SUM(v, VECSIZE));
	}

}

void test5()
{
	int v[] = {6,7,8,9,10};
	int maxsum = 60;
	while (incseq(v, VECSIZE, maxsum) )
	{
		//PVEC(v, 5, SUM(v, 5));
		if (isSpecialSet(v, 5))
		{
			printf("SPECIAL SET: ");
			PVEC(v, 5, SUM(v, 5));
			maxsum = SUM(v, 5) - 1;
		}
	}
}

void test6()
{
	int v[] = {11, 12, 13, 14, 15, 16};
	int maxsum = 118;
	while (incseq(v, 6, maxsum) )
	{
		//PVEC(v, 5, SUM(v, 5));
		if (isSpecialSet(v, 6))
		{
			printf("SPECIAL SET: ");
			PVEC(v, 6, SUM(v, 6));
			maxsum = SUM(v, 6) - 1;
		}
	}
}

void test7()
{
	int v[] = {16,17,18,19,20,21,22};
	int maxsum = 256;
	while (incseq(v, 7, maxsum) )
	{
		//PVEC(v, 5, SUM(v, 5));
		if (isSpecialSet(v, 7))
		{
			printf("SPECIAL SET: ");
			PVEC(v, 7, SUM(v, 7));
			maxsum = SUM(v, 7) - 1;
		}
	}
}


int main()
{
    //test();
    test5();
    fflush(stdout);
    test6();
    fflush(stdout);
    test7();
}
