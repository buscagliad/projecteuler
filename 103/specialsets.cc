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
			printf("value %d found twice\n", value);
			return false;
		}
	}
	a[N] = value;
	return true;
}

bool isSpecialSet(int *set, int setSize, bool dump = false)
{
	int numSubs = xpower(2, setSize);
	int	setSums[numSubs];
	for (int k = 0; k < numSubs; k++) setSums[k] = 0;
	for (int mask = 1; mask < numSubs; mask++)
		if (!addnew(setSums, mask-1, nextSum(set, setSize, mask)))
			return false;
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

void test()
{
	trial(2, 1, 2);
	trial(3, 2, 3, 4);
	trial(4, 3, 5, 6, 7);
	trial(5, 6, 9, 11, 12, 13);
	trial(6, 11, 17, 20, 22, 23, 24);
	trial(6, 11, 18, 19, 20, 22, 25);
	trial(6, 7, 8, 9, 10, 11, 12);
	trial2(6, 11, 18, 19, 20, 22, 25);
}

int main()
{
    test();
}
