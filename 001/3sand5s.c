#include <stdio.h>
#include <stdlib.h>

#define	DIV1 3
#define DIV2 5
#define NUM 1000
int main(int argc, char **argv)
{
	int	sum = 0;
	int num = NUM;
	if (argc == 2) num = atoi(argv[1]);
	
	for (int i = 1; i < num; i++)
	{
		if (i % DIV1 == 0) sum += i;
		else if (i % DIV2 == 0) sum += i;
	}
	printf("Sum of all numbers less than %d divisible by %d or %d is %d\n",
		num, DIV1, DIV2, sum);
	return 1;
}
