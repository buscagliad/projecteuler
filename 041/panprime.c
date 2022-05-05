#ifdef PROBLEM_DESCRIPTION

Pandigital prime


Problem 41

We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?

#endif

#include "prime.h"

// C++ program to print all permutations using
// Heap's algorithm
#include <bits/stdc++.h>
using namespace std;

// Prints the array
void printArr(int a[], int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	printf("\n");
}

long	maxP = 0;


// Prints the array
void checkArray(int a[], int n)
{
	long	s = 0;
	for (int i = 0; i < n; i++)
		s = 10 * s + a[i];
	if (isPrime(s) && s > maxP) maxP = s;
}
int nCount = 1;

// Generating permutation using Heap Algorithm
void heapPermutation(int a[], int size, int n)
{
	// if size becomes 1 then prints the obtained
	// permutation
	if (size == 1) {
		checkArray(a, n);
		return;
	}

	for (int i = 0; i < size; i++) {
		heapPermutation(a, size - 1, n);

		// if size is odd, swap 0th i.e (first) and
		// (size-1)th i.e (last) element
		if (size % 2 == 1)
			swap(a[0], a[size - 1]);

		// If size is even, swap ith and
		// (size-1)th i.e (last) element
		else
			swap(a[i], a[size - 1]);
	}
}

// Driver code
int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7 };
	int n = sizeof a / sizeof a[0];
	heapPermutation(a, n, n);
	printf("Max prime is: %ld\n", maxP);
	return 0;
}
