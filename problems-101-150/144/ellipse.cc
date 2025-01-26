#ifdef PROBLEM

In laser physics, a "white cell" is a mirror system that acts as a delay line for the laser beam. The beam enters the cell, bounces around on the mirrors, and eventually works its way back out.

The specific white cell we will be considering is an ellipse with the equation 4x^2 + y^2 = 100

The section corresponding to -0.01 <= x <= +0.01 at the top is missing, allowing the light to enter and exit through the hole.

The light beam in this problem starts at the point (0.0,10.1) just outside the white cell, and the beam first impacts the mirror at (1.4,-9.6).

Each time the laser beam hits the surface of the ellipse, it follows the usual law of reflection "angle of incidence equals angle of reflection." That is, both the incident and reflected beams make the same angle with the normal line at the point of incidence.

In the figure on the left, the red line shows the first two points of contact between the laser beam and the wall of the white cell; the blue line shows the line tangent to the ellipse at the point of incidence of the first bounce.

The slope m of the tangent line at any point (x,y) of the given ellipse is: m = -4x/y

The normal line is perpendicular to this tangent line at the point of incidence.

The animation on the right shows the first 10 reflections of the beam.

How many times does the beam hit the internal surface of the white cell before exiting?

#endif

#include <cmath>
#include <cstdio>


#define Am(m) sqrt(25.0 * m * m + 100)
#define Phi(m) atan(2/m)
#define Lm(x,y,m) ( y - m * x)

#define SIGN(x) ((x) < 0 ? -1 : (x) > 0 ? 1 : 0)
#define MINV 0.001

bool getNext(double x, double y, double m, double &xn, double &yn, double &mn)
{
	//  Goal is to take in x, y, and m and  compute (xn, yn) and mn
	//  and compute the 'next' point after reflection
	//    x <- xn, y <- yn
	//    xn and yn will be newly computed
	//
	//  we know that m (the slope of the line segment from (x,y) to (xn,yn) is
	//  given by:
	//              yn - y
	//              ------ = m           (1)
	//              xn - x
	//
	//  which yields the line equation involving xn, yn:
	//
	//           yn = m(xn - x) + y      (2)
	//
	//  but, xn, yn must satisfy:   
	//
	//           4xn^2 + yn^2 = 100        (3)
	//
	//  Plugging (2) into (3) yields a quadratic in xn
	//
	//
	//       4xn^2 + {m(xn - x) + y}^2 - 100 = 0  (4)
	//
	//  Collecting like terms yields:
	//
	//      (4 + m^2) * xn^2 + 2m *(y - x*m) * xn +
	//                 y^2 - 2*y*x*m +m^2*x^2  - 100 = 0
	//
	//       a xn^2 + b xn + c = 0
	//
	//             -b +/- sqrt(b^2 - 4*a*c)
	//       xn = --------------------------
	//                   2 a
	//
	//   We choose the sign + or - to assure xn != x
	//
	
	double a = 4 + m * m;
	double b = 2 * m * (y  - x * m);
	double c = y * y - 2 * y * x * m + m * m * x * x - 100;
	
	double rad = sqrt(b * b - 4 * a * c);
	double x1 = (-b - rad) / (2 * a);
	double x2 = (-b + rad) / (2 * a);
	if (fabs(x1 - x) > fabs(x2 - x) ) xn = x1; else xn = x2;
	yn = (xn - x) * m + y;

	printf("x: %.6f  y: %.6f   m: %.6f  xn: %.6f  yn: %.6f \n", x, y, m, xn, yn);
	
	
	//   Now we need to compute mn, the slope of the reflective line segment
	//   from (xn, yn) to the next point on the ellipse.
	//
	//   We note that if we denote the slope (mp) of the perpendicular 
	//   to the ellipse at (xn, yn) is given by 
	//           mp = yn / (4 * xn)    (10)
	//
	//   We call the angle between the approaching ray (slope m) and the 
	//   perpendicular (slope mp) to be alpha.  We also know that the
	//   slope of the emanating ray (slope mn) makes an angle alpha with 
	//   the perpendicular line as well.  
	//
	//   The angle alpha between two lines with slopes m1 and m2 is given
	//   by:                m2 - m1
	//       tan(alpha) = -----------    (11)
	//                    1 + m1 * m2
	//   let m2 = m, m1 = mp, then
	//                          mp - m
	//       alpha = arctan  -----------     (12)
	//                        1 + m * mp
	//
	//   let m1 = m, m2 = mn, then we know these two lines are two * alpha 
	//   apart, which yields:
	//
	//                          mn - m
	//       tan(2 * alpha) = -----------   (13)
	//                         1 + m * mn
	//
	//   Solving for mn in (13) yields:
	//
	//              m + tan(2 * alpha)
	//       mn = ----------------------     (14)
    //            1 - m * tan(2 * alpha)	
	//
	//    So, we first compute alpha via (12)
	//    Then plug in alpha into 14 to yield mn.
	//  	
	

	double mp = yn / (4.0 * xn);
	double alpha = atan2((mp - m) , (1 + m * mp));
	double t2alpha = tan(2*alpha);

	mn = (m + t2alpha) / (1 - m * t2alpha);

	printf("     mp: %.6f  alpha: %.6f  t2alpha: %.6f  mn: %.6f\n",
		mp, alpha, t2alpha, mn);
	return true;
}

int main()
{
	double xn , yn, mn;
	getNext(0, 10.1, -19.7/1.4, xn, yn, mn);
	int reflections = 0;
	while (xn < -0.01 || xn > 0.01 || yn < 0.0)
	{
		reflections++;
		getNext(xn, yn, mn, xn, yn, mn);
	}
	printf("Number of reflections: %d\n", reflections);

}
