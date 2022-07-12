//
// File: poly.h   -   polynomial class
//
//  Two types of initialization (interp == true, array a is a set of points
//   poly(<type> *a, int nsize, bool interp);
//

template <class T>
class poly {
	private:
		T 		*c;	// coefficients
		int 	N;	// order of polynomial
	public:
		poly(T *a, size_t len)
		{
			c = (T) malloc( sizeof(T) * len );
			memcpy(c, a, sizeof(T) * len );
			N = len - 1;
		}
		T	eval(T x) {
			T res = x * a[N];
			for (int i = N - 1; i >= 0; i--)
				res = (a[i] + res) * x;
			return res;
		}
};

template <class T>
class ipoly {
	private:
		T 		*x;		// coefficients
		T 		*fx;	// coefficients
		int 	N;		// order of polynomial
	public:
		poly(T *a, size_t len)
		{
			c = (T) malloc( sizeof(T) * len );
			memcpy(c, a, sizeof(T) * len );
			N = len - 1;
		}
		T	eval(T x) {
			T res = x * a[N];
			for (int i = N - 1; i >= 0; i--)
				res = (a[i] + res) * x;
			return res;
		}
};

poly<int> p
