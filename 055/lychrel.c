#ifdef PROBLEM_DESCRIPTION


If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.

Not all numbers produce palindromes so quickly. For example,

349 + 943 = 1292,
1292 + 2921 = 4213
4213 + 3124 = 7337

That is, 349 took three iterations to arrive at a palindrome.

Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome. A number that never forms a palindrome through the reverse and add process is called a Lychrel number. Due to the theoretical nature of these numbers, and for the purpose of this problem, we shall assume that a number is Lychrel until proven otherwise. In addition you are given that for every number below ten-thousand, it will either (i) become a palindrome in less than fifty iterations, or, (ii) no one, with all the computing power that exists, has managed so far to map it to a palindrome. In fact, 10677 is the first number to be shown to require over fifty iterations before producing a palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).

Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.

How many Lychrel numbers are there below ten-thousand?

NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.

#endif
#include <stdio.h>
#include "bigint.h"


bool	isLychrel(BigInt b, bool debug=false, int max_iterations = 50)
{
	for (int i = 0; i < max_iterations; i++)
	{
		if (debug) cout << i + 1 << "  " << b << " + " << b.reverse() << " = ";
		b = b + b.reverse();
		if (debug) cout << b << endl;
		if (b.isPalindrome()) return false;
	}
	return true;
}

int main()
{
	//isLychrel(349l, true); 
	//isLychrel(4994l, true); return 1;
	//isLychrel(196, true, 100); 
	//isLychrel(10677, true, 100); 
	//BigInt d(94039l);
	//cout << d << " p? " << d.isPalindrome() << endl;return 1;
	int count = 0;
	for (long s = 1; s < 10000; s++)
	{
		bool il = isLychrel(s);
		if (il) {
			count++;
			printf("%ld is a Lychrel\n", s);
		}
	}
	printf("There are %d Lychrel numbers less than 10000\n", count);
}
		
