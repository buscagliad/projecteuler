
#include "digit.h"
#include "prime.h"


// getsum when called from 'outside', will return 0 if no prime numbers
// found of 'remaining_digits' (10 for this problem when this function is called)
// with 'number_of_repeating_digits' of digit	
long getsum(int remaining_digits, int number_repeating_digits, int digit, long curnum) 
{
	// if there are not enough digits to get to number_repeating_digits, return 0
	if(number_repeating_digits > remaining_digits) return 0;

	// if remaining_digits is zero, we need to test for a successful number
	if (remaining_digits == 0) 
	{
		if (number_repeating_digits == 0 && isPrime(curnum)) 
		{
			//printf("%ld\n", curnum);
			return curnum;	// if it's a prime it will be returned to add to sum
		}
		return 0;	// if not, 0 is returned
	}
	long sum = 0;
	int dig_start = 0;
	if (curnum == 0) dig_start = 1;	// no ending 0???
	for (int dig = dig_start; dig <= 9; dig++)
	{
		// decrement remaining_digits (adding the digit 'dig')
		// if the digit from the for loop IS our repeating digit, we decrement the number of repeating
		// digits
		if (dig == digit)
			sum += getsum(remaining_digits-1, number_repeating_digits-1, digit, curnum * 10 + dig);
		else
			sum += getsum(remaining_digits-1, number_repeating_digits, digit, curnum * 10 + dig);
	}
	return sum;
}
		
			

int main()
{
	long   prime_sum = 0;
	int    prime_length = 10;
	for (int repdig = 0; repdig <= 9; repdig++)
	{
		for (int numrd = prime_length - 1; numrd > 1; numrd--)
		{
			long local_sum = getsum(prime_length, numrd, repdig, 0);
			if (local_sum > 0)	// found a good sum, total it and break out of numrd loop
			{
				prime_sum += local_sum;
				break;
			}
		}
	}
	printf("Prime run sum S(%d, d), d = 0, 1, ... 9 is: %ld\n", prime_length, prime_sum);
}

