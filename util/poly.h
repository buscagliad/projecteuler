//
// File: poly.h   -   polynomial class
//
//  Two types of initialization (interp == true, array a is a set of points
//   poly(<type> *a, int nsize, bool interp);
//

#include <cstring>
#include <cstdlib>

template <class T>
class poly {
	private:
		T 		*c;	// coefficients
		int 	N;	// order of polynomial
	public:
		poly(T *a, size_t len)
		{
			c = (T *) malloc( sizeof(T) * len );
			memcpy(c, a, sizeof(T) * len );
			N = len - 1;
		}
		T	eval(T x) {
			T res = x * c[N];
			for (int i = N - 1; i >= 1; i--)
				res = (c[i] + res) * x;
			res += c[0];
			return res;
		}
};

template <class T>
class ipoly {
	private:
		T 		*c;		// coefficients
		T 		*fx;	// coefficients
		int 	N;		// order of polynomial
	public:
		ipoly(T *a, size_t len)
		{
			c = (T) malloc( sizeof(T) * len );
			memcpy(c, a, sizeof(T) * len );
			N = len - 1;
		}
		T	eval(T x) {
			T res = x * c[N];
			for (int i = N - 1; i >= 0; i--)
				res = (c[i] + res) * x;
			return res;
		}
};

