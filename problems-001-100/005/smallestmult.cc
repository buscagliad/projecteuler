
#include "prime.h"
#include "factor.h"

int main(int argc, char **argv)
{
	long NUM = 20;
	factor c(2);
	for (long t = 3; t <= NUM; t++)
	{
		c.merge(t);
	}
	c.out();
	return 1;
}
