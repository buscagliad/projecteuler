
#include "vlong.h"

int main()
{
	vlong_t v;
	v.push_back(0);
	v.push_back(2);
	v.push_back(3);
	v.push_back(7);
	vlong vv(v);
	vv.out();
	vv.setPermutation(2);
	vlong_t p = vv.getNextPerm();
	while(p.size())
	{
		vl_out(p);
		p = vv.getNextPerm();
	}
}
	
