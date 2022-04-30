#include <bitset>
#include "vlong.h"
#include "prime.h"
#include "factor.h"

typedef	std::bitset<10>	digbit_t;	// represents digits 0 thru 9
typedef std::bitset<64> facbit_t;	// factor bits

// returns true if a digit in 'a' is repeated   OR
// a digit in 'a', say k, is also set in bits, i.e. bits[k] is true (1 <= k <= 9)
// false means the digits of 'a' do NOT appear in bits nor a has a repeating digit
// if bits == 0, a true return means 'a' has a repeating digit
bool setbit(int a, digbit_t &bits)
{
	while (a)
	{
		int	d = a%10;    // get ones digit of a
		if (bits[d]) return true; // a has more than 1 digit in its
		bits[d] = 1;	// digit 'd' has been found
		a /= 10;		// shift a by one digit
	}
	return false;
}

#define PANDIG 0x3FE	// bits 1, 2, ..., 9 are set

bool ispandig(long a, long b, long pan)
{
	digbit_t	bits;
	//printf("pandig: %ld * %ld = %ld (%ld)\n", a, b, a*b, pan);
	if (a * b != pan) return false;
	if (setbit(a, bits)) return false; 	
	if (setbit(b, bits)) return false;
	if (setbit(pan, bits)) return false; 
	if (bits[0]) return false; // no digit 0
	if ( (bits.to_ulong() & PANDIG) == PANDIG) {
		printf("%ld * %ld = %ld !!\n", a, b, pan);
		return true;
	}
	return false;
}

bool repdigit(int n)
{
	digbit_t bits;
	return setbit(n, bits); 	
}

long	power_size(vlong_t &v)
{
	int	n = v.size() - 1;
	int p = 2;
	for (; n > 0; n--) p *= 2;
	return p - 1;
}

long    prod(vlong_t &v, int n, bool in)
{
	int p = 1;
	facbit_t b(n);
	for (size_t i = 0; i < v.size(); i++)
	{
		if (b[i] && in) p *= v[i];
		else if (!b[i] && !in) p *= v[i];
	}
	return p;
}

bool	gettwo(vlong_t &v, long prod, long &a, long &b, long &n)
{
	if (n < 0) return false;	// only search to 2^(N-1) - 1
	if (n >= (int)v.size()) return false;	// only search to 2^(N-1) - 1
	a = v[n];
	b = prod / a;
	return true;
}

int main()
{
	ispandig(39, 186, 7254);
	ispandig(23, 78, 1794);
	vlong_t v;
	long sum = 0;
	long fa, fb, n;
	for (long a = 1234; a < 10000; a++)
	//for (long a = 7254; a < 7255; a++)
	{
		if (repdigit(a)) continue;
		if (isPrime(a)) continue;
		factor f(a);
		//std::bitset<f.size()> fset;
		v = f.divisors();
		//vlong(v).out();
		n = 0;
		while (gettwo(v, a, fa, fb, n))
		{
			n++;
			if (ispandig(fa, fb, fa*fb)) {
				sum += a;
				break;
			}
		}
	}
	printf("Sum of 1-9 pandigital numbers is: %ld\n", sum);
	return 1;
}

	
