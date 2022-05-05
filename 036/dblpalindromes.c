#ifdef PROBLEM_DESCRIPTION

Double-base palindromes

Problem 36

The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)

#endif

#include "utils.h"

bool	test(long n)
{
	vlong_t v10 = get_digits(n, 10);
	vlong_t v2 = get_digits(n, 2);
	//vl_out(v10);
	//vl_out(v2);
	if (isPalindrome(v10) && isPalindrome(v2)) return true;
	return false;
}

int main()
{
	long sum = 0;
	for (long n = 1; n < 1000000; n++)
	{
		if (test(n)) {
			printf("%ld is a base 2 and 10 palindrome\n", n);
			sum += n;
		}
	}
	printf("The sum of these numbers is: %ld\n", sum);
	return 1;
}
