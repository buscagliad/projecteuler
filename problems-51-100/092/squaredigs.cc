#ifdef PROBLEM_DESCRIPTION

Square digit chains


  [Show HTML problem content]  
Problem 92

A number chain is created by continuously adding the square of the digits in a number to form a new number until it has been seen before.

For example,

44 → 32 → 13 → 10 → 1 → 1
85 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58 → 89

Therefore any chain that arrives at 1 or 89 will become stuck in an endless loop. What is most amazing is that EVERY starting number will eventually arrive at 1 or 89.

How many starting numbers below ten million will arrive at 89?

#endif

#include <cstdio>

int next(int n)
{
	int sum = 0;
	while (n > 0)
	{
		sum += (n % 10) * (n % 10);
		n /= 10;
	}
	return sum;
}

int ones = 0;
int eightynines = 0;


void run(int n)
{
	bool done = false;
	while(!done)
	{
		n = next(n);
		if (n == 89)
		{
			eightynines++;
			done = true;
		}
		if (n == 1)
		{
			ones++;
			done = true;
		}
	}
}

int main()
{
	for (int i = 1; i <= 10000000; i++)
	    run(i);
	printf("Ones = %d\n", ones);
	printf("89's = %d\n", eightynines);
	printf("Total = %d\n", ones + eightynines);
}
