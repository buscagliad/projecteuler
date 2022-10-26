#include <bigint.h>

class isPan {
	public:
		isPan();
		bool add(int dig);	// returns true if 'new', false if already seen
	private:
		int	a[10];
};

isPan::isPan()
{
	for (int i = 0; i < 10; i++) a[i] = 0;
}

bool isPan::add(int n)
{
	if (n == 0) return false;
	if (a[n]) return false;
	a[n] = 1;
	return true;
}

bool firstPan(BigInt &n)
{
	isPan	ip;
	if (n.num_digits() < 10) return false;
	for (int i = 0; i < 9; i++)
	{
		if (!ip.add(n.get_digit(i))) return false;
	}
	return true;
}

bool lastPan(BigInt &n)
{
	isPan	ip;
	if (n.num_digits() < 10) return false;
	for (int i = n.num_digits()-9; i <= n.num_digits()-1; i++)
	{
		if (!ip.add(n.get_digit(i))) return false;
	}
	return true;
}

bool next(BigInt &FN, BigInt &FNm1, BigInt &FNm2, int &n)
{
	FN = FNm1 + FNm2;
	FNm2 = FNm1;
	FNm1 = FN;
	n++;
	bool	first = false;
	bool	last = false;
	
	if (firstPan(FN))
	{
		printf("[%d] FIRST Pan 9: %d\n", n, FN.num_digits());
		first = true;
	}
	if (lastPan(FN))
	{
		printf("[%d] LAST Pan 9: %d\n", n, FN.num_digits());
		last = true;
	}
	return last && first;
}


int main()
{
	BigInt FN;
	BigInt FNm1(1l);
	BigInt FNm2(1l);
	int		n = 2;
	while (!next(FN, FNm1, FNm2, n));
}
