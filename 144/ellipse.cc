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

#define A(m) sqrt(25.0 * m * m + 100)
#define Phi(m) atan2(2.0, -m)
#define L(x,y,m) ( m * x - y)

#define SIGN(x) ((x) < 0 ? -1 : (x) > 0 ? 1 : 0)

bool getNext(double x, double y, double m, double &xn, double &yn, double &mn)
{
	// we will parameterize the ellipse 4x^2 + y^2 = 100
	// by making the following transformation to t
	// 	x = 5.0 * sin(t)    (1)
	//	y = 10.0 * cos(t)   (2)
	//  NOTE: these x,y pairs satisfy the ellipse for all t, and in particular
	//  for -pi < t <= pi, the entire ellipse is generated.
	//  assume tn is such that:
	//     xn = 5.0 sin(tn) and yn = 10 cos(tn)  (3)
	//  we know that m (the slope of the line segment from (x,y) to (xn,yn) is
	//  given by:
	//              yn - y
	//              ------ = m           (4)
	//              xn - x
	//
	//  which yields   10 cos(tn) - y
	//                 -------------- = m     (5)
	//                 5 sin(tn) - x
	//
	//  simplifying (5) yields:
	//          10 cos(tn) - 5 m sin(tn) = y - m * x  (6)
	//
	//    NOTE:  a cos t + b sin t = A sin (t + w)   (7)
	//        where A = sqrt(a^2 + b^2)
	//              w = atan2(a, b)
	//  Using (7) we can simplify (6) as
	//
	//       A sin (tn + w) = y - m * x       (8)
	//
	//  Solving (8) for tn yields:
	//                   y - m * x
	//       tn = arcsin ----------  -  w   (9)
    //                       A
    //
    //  where 
    //        A = sqrt(100 + 25 * m * m)
    //        w = atan2(10, -5 * m)
	//
	//   We use (9) to compute tn,
	//   then (1) and (2) to compute xn and yn
	//
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
	//                      m - mp
	//       tan(alpha) = -----------     (12)
	//                    1 + m * mp
	//
	//   let m1 = m, m2 = mn, then we know these two lines are two * alpha 
	//   apart, which yields:
	//
	//                          m - mn
	//       tan(2 * alpha) = -----------   (13)
	//                         1 + m * mn
	//
	//   Solving for mn in (13) yields:
	//
	//              m - tan(2 * alpha)
	//       mn = ----------------------     (14)
    //            m * tan(2 * alpha) + 1	
	//
	//                            2 tan(alpha)
	//         tan(2 * alpha) = ----------------     (15)
	//                          1 - tan(alpha)^2
	//
	//    So, we first compute tan(alpha) via (12)
	//    Then plug in tan(alpha) into 15 to arrive at tan(2*alpha)
	//    The take tan(2 * alpha) and plug it into (14) to yield mn.
	//   

	double tn = asin(L(x,y,m)/A(m)) - Phi(m);   // (9)
	if ( (m < 0) && (fabs(tn) <= M_PI/2) ) tn += M_PI;
	if ( (m > 0) && (fabs(tn) >= M_PI/2) ) tn += M_PI;
	xn = 5.0 * sin(tn);							// (1)
	yn = 10.0 * cos(tn);						// (2)
	
	// check xn, yn slope, if it doesn't match, then xn -> -xn   yn -> -yn
	

	double mp = yn / xn / 4.0;					// (10)
	//                      m - mp
	//       tan(alpha) = -----------     (12)
	//                    1 + m * mp
	double talpha = (m - mp) / (1 + m * mp);
	//                            2 tan(alpha)
	//         tan(2 * alpha) = ----------------     (15)
	//                          1 - tan(alpha)^2
	double t2alpha = 2 * talpha / (1 - talpha * talpha);
	//
	//              m - tan(2 * alpha)
	//       mn = ----------------------     (14)
    //            m * tan(2 * alpha) + 1	
	mn = (m - t2alpha) / (m * t2alpha + 1);

	printf("L: %.6f  A: %.6f  Phi: %.6f  t: %.6f  (%.6f,%.6f) @ %.6f   -->   (%.6f,%.6f) @ %.6f\n",
		L(x,y,m), A(m), Phi(m), tn, x, y, m, xn, yn, mn);
	return true;
}

int main()
{
	double xn, yn, mn;
	getNext(0, 10.1, -19.7/1.4, xn, yn, mn);
	getNext(xn, yn, mn, xn, yn, mn);
	getNext(xn, yn, mn, xn, yn, mn);

}
