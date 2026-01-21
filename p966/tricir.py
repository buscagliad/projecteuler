import math
from scipy.optimize import minimize
import numpy as np

debug = False

def length(x1, y1, x2, y2):
    return math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))

#
# triangle_area returns the area of the triangle as well
# as the radius of the circle with the same area
#
def triangle_area(xa, ya, xb, yb, xc, yc):
    a = length(xa,ya,xb,yb)
    b = length(xc,yc,xb,yb)
    c = length(xa,ya,xc,yc)
    s = (a + b + c) / 2.0
    rad = s * (s - a) * (s - b) * (s - c)
    if rad < 0:
        return 0
    A = math.sqrt(rad)
    return A

# compute the angle at the b vertex of the triangle
def inangle(xa, ya, xb, yb, xc, yc):
    ABx = xb - xa
    ABy = yb - ya
    CBx = xc - xb
    CBy = yc - yb
    AB = math.sqrt(ABx * ABx + ABy * ABy)
    CB = math.sqrt(CBx * CBx + CBy * CBy)
    cosB = (-ABx * CBx - ABy * CBy) / (AB * CB)
    if AB == 0 or CB == 0:
        angleB = 0.0
    else:
        angleB = math.acos(max(min(cosB, 1.0), -1.0))
    return angleB

#
# returns the angle from side AB and BC
#              A       B      C
def compangle(x1,y1, x2,y2, x3,y3):
    # Vectors
    ax, ay = x2 - x1, y2 - y1
    bx, by = x3 - x1, y3 - y1
    cx, cy = x3 - x2, y3 - y2

    # Lengths
    len_b = math.sqrt(ax**2 + ay**2)           # AC
    len_c = math.sqrt(cx**2 + cy**2)           # AB

    # Cosines
    cosB = (-ax*cx - ay*cy) / (len_b * len_c) if len_b*len_c != 0 else 0

    # Angles in degrees
    angleB = acos(max(min(cosB, 1.0), -1.0))

    return angleB
#
#
#
def tricirc(x1, y1, x2, y2, xc, yc, r):
    global debug
    ##
    ## NOTE:  tricirc(x1, y1, x2, y2, xc, yc, r) == tricirc(y1, x1, y2, x2, yc, xc, r)
    ##        meaning the intersection area is preserved under rotation, since the solution
    ##        assumes x1 != x2 below, if they are, we will rotate the values to ensure
    ##        a valid solution
    ##
    arc1=arc2=tri=0
    if x2 == x1:
        print("************ switcharoo")
        s = x1
        x1 = y1
        y1 = s
        s = x2
        x2 = y2
        y2 = s
        s = xc
        xc = yc
        yc = s
        
    m = (y2 - y1) / (x2 - x1)
    a = m * m + 1
    b = 2 * (y1 * m - xc - x1 * m * m - m * yc)
    c = (xc * xc + y1 * y1 + m * m * x1 * x1 + yc * yc -
            2 * y1 * m * x1 - 2 * y1 * yc + 2 * m * x1 * yc - r * r)
    disc = b * b - 4 * a * c
    #
    # 0, 1 solutions - circle arc is inside of triangle - use full arc of circle
    #
    if debug: print("-----------------------")
    if debug: print("m: ", m, "  a: ", a, "  b: ", b, "  c: ", c)
    if disc <= 0:
        alpha = inangle(x1, y1, xc, yc, x2, y2)
        if debug: print("Case 0: No intersection", disc)
        return r * alpha
    rdisc = math.sqrt(disc)
    sx1 = (-b - rdisc) / (2 * a)
    sx2 = (-b + rdisc) / (2 * a)
    sy1 = y1 + m * (sx1 - x1)
    sy2 = y1 + m * (sx2 - x1)
    if debug: print("x1, sx1, sx2, x2: ", x1, sx1, sx2, x2)
    if debug: print("y1, sy1, sy2, y2: ", y1, sy1, sy2, y2)
    if debug: print("xc, yc: ", xc, yc)
    
    #
    # if there are two solutions, then we have several cases to consider
    # sx2 > sx1 is given
    #
    # case 1:  x1 < sx1 < sx2 < x2
    # In this case, we return the two arcs formed by (x1, y1, xc, yc, sx1, sy1) and by
    #                                                (sx2, sy2, xc, yc, x2, y2)
    # and the triangle:  (sx1, sy1, xc, yc, sx2, sy2)
    if x1 < sx1 < sx2 < x2:
        arc1 = r * inangle(x1, y1, xc, yc, sx1, sy1)
        arc2 = r * inangle(sx2, sy2, xc, yc, x2, y2)
        tri = triangle_area(sx1, sy1, xc, yc, sx2, sy2)
        if debug: print("Case 1: ", "(",sx1,sy1,")", "(", sx2,sy2, ")", "  arc1: ", arc1, "  arc2: ", arc2, "  tri: ", tri)
    #
    # case 2: s1 < x1 < s2 < x2
    # In this case, we return the traingle formed by (x1, y1, xc, yc, sx2, sy2)
    #                         and the arcs formed by (sx2, sy2, xc, yc, x2, y2)
    elif (sx1 < x1 < sx2 < x2):
        arc1 = r * inangle(x1, y1, xc, yc, sx2, sy2)
        tri  = triangle_area(sx2, sy2, xc, yc, x2, y2)
        arc2 = 0
        if debug: print("Case 2: ", "(",sx1,sy1,")", "(", sx2,sy2, ")", "  arc1: ", arc1, "  arc2: ", arc2, "  tri: ", tri)
    #
    # case 3: x1 < s1 < x2 < s2
    # In this case, we return the traingle formed by (sx1, sy1, xc, yc, x2, y2)
    #                         and the arcs formed by (x1, y1, xc, yc, sx1, sy1)
    elif (x1 < sx1 < x2 < sx2):
        arc1 = r * inangle(x1, y1, xc, yc, sx1, sy1)
        tri  = triangle_area(sx1, sy1, xc, yc, x2, y2)
        arc2 = 0
        if debug: print("Case 3: ", "(",sx1,sy1,")", "(", sx2,sy2, ")", "  arc1: ", arc1, "  arc2: ", arc2, "  tri: ", tri)
    #
    # case 4: sx1 < x1 < x2 < sx2
    # In this case the circle contains the triangle (x1, y1, xc, yc, x2, y2)
    elif (sx1 < x1 < x2 < sx2):
        arc1 = 0
        arc2 = 0
        tri = triangle_area(x1, y1, xc, yc, x2, y2)
        if debug: print("Case 4: ", "(",sx1,sy1,")", "(", sx2,sy2, ")", "  arc1: ", arc1, "  arc2: ", arc2, "  tri: ", tri)
    else:
        print("We have a problem: ", x1, y1, x2, y2, xc, yc, r)
        print("  ", "s1:  (",sx1,sy1,")", "  s2: (", sx2,sy2, ")", "  arc1: ", arc1, "  arc2: ", arc2, "  tri: ", tri)
        print("x1, sx1, sx2, x2: ", x1, sx1, sx2, x2)
        print("y1, sy1, sy2, y2: ", y1, sy1, sy2, y2)
        print("xc, yc: ", xc, yc)
        #return 0
    if arc1 < 0 or arc2 < 0 or tri < 0:
        print("Negative: ", arc1, arc2, arc3)
    return arc1 + arc2 + tri
         

# Define the function to maximize
def f(params):
    global gx1, gy1, gx2, gy2, gx3, gy3, gr, debug
    xc, yc = params
    if gx1 > gx2:
        a1 = tricirc(gx2, gy2, gx1, gy1, xc, yc, gr)
    else:
        a1 = tricirc(gx1, gy1, gx2, gy2, xc, yc, gr)

    if gx1 > gx3:
        a2 = tricirc(gx3, gy3, gx1, gy1, xc, yc, gr)
    else:
        a2 = tricirc(gx1, gy1, gx3, gy3, xc, yc, gr)

    if gx3 > gx2:
        a3 = tricirc(gx2, gy2, gx3, gy3, xc, yc, gr)
    else:
        a3 = tricirc(gx3, gy3, gx2, gy2, xc, yc, gr)

    res = a1 + a2 + a3
    if debug: print("  xc, yc, a1, a2, a3, res: ", xc, yc, a1, a2, a3, res)
    return res

    
def init_glob(a, b, c, debug = False):
    global gx1, gy1, gx2, gy2, gx3, gy3, gr
    gx1 = gy1 = 0
    gx2 = a
    gy2 = 0
    gx3 = ( a * a - b * b + c * c ) / ( 2 * a )
    gy3 = math.sqrt(c * c - gx3 * gx3)
    A = gy3 * a / 2
    gr = math.sqrt((gy3 * a)/(2 * math.pi))
    if debug: print("INIT:  a, b, c: ", a, b, c)
    if debug: print("      A: ", gx1, gy1, "  B: ", gx2, gy2, "   C: ", gx3, gy3)

    
def maxsol(a, b, c):
    global gx1, gy1, gx2, gy2, gx3, gy3, gr
    init_glob(a, b, c)
    # 
    # Initial guess for the parameter would be the center of the
    # triangle:
    #            xc = (x1+x2+x3)/3 = (0 + a + gx3) / 3 = (a + gx3) / 3
    #            yc = (y1+y2+y3)/3 = (0 + 0 + gy3) / 3 = gy3 / 3
    
    initial_guess = np.array([(a + gx3) / 3, gy3 / 3])

    # Use the minimize function
    # The result will contain the optimal parameters in `x`
    result = minimize(f, initial_guess, method='Nelder-Mead')
    return result


#result = maxsol(1,1,1)

init_glob(1,1,1)
debug=True
print(f((0.5,1/math.sqrt(3)/2)))
#exit(1)




result = maxsol(3, 4, 5)
result = maxsol(3, 4, 6)
result = maxsol(3, 5, 5)
if result.success:
    optimal_point = result.x
    max_value = result.fun 
    print(f"Found local maximum at x={optimal_point[0]:.2f}, y={optimal_point[1]:.2f}")
    print(f"Maximum value: {max_value:.2f}")
else:
    print(f"Optimization failed: {result.message}")

ans=4.592854956993022 
xy=(1.0598361876396127, 1.2113446381657513)
print(ans, f(xy))
