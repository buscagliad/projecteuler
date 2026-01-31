


int main()
{
	int numb = 0;
	long n = 0;
	int pct = 99;
	bool done = false;
	//printf("Number of 3 digit nonbouncy numbers is: %ld\n", nonbounce(3));
	while(!done)
	{
		n++;
		base10	b(n);
		bool    ib = b.isBouncy();
		if (ib) numb++;
		if (n % 10000 == 0) {printf("%4ld   %s   %.4f\n", n, b.isBouncy() ? "BOUNCY" : "", (double)numb/(double)n); fflush(stdout);}
		if (n * pct == 100 * numb) done = true;
	}
	printf("%4ld      %.4f\n", n, (double)numb/(double)n); 
}

