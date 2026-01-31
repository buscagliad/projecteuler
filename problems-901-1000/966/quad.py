import math
gx1 = gy1 = 0
gx2 = gy2 = 0
gx3 = gy3 = 0
gr = 0
debug = False

def init_glob(a, b, c, debug = False):
    global gx1, gy1, gx2, gy2, gx3, gy3, gr
    gx1 = gy1 = 0
    gx2 = a
    gy2 = 0
    gx3 = ( a * a - b * b + c * c ) / ( 2 * a )
    gy3 = math.sqrt(c * c - gx3 * gx3)
    A = gy3 * a / 2
    gr = math.sqrt(A / math.pi)
    if debug: print("INIT:  a, b, c: ", a, b, c)
    if debug: print("      A: ", gx1, gy1, "  B: ", gx2, gy2, "   C: ", gx3, gy3)
    if debug: print("   Area: ", A, "   Circle: ", gr, "  CA: ", math.pi * gr * gr)
    
    
def length(x1, y1, x2, y2):
    return math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))

#    (lx, rx, uy, ly) = tri_intersections(xc, yc)
#   Assume (0,0), (a, 0) and (gx3, gy3) coordinates
def tri_intersections(xc, yc):
    global gx1, gy1, gx2, gy2, gx3, gy3, gr, debug
    # 
    # find uy - fcn of xc
    #
    if xc < gx3:
        uy = xc * gy3 / gx3
    else:
        uy = ( gy3 / (gx3 - gx2) ) * (xc - gx2)
    ly = 0
    #
    # find lx and rx - fcn of yc
    #
    lx = gx3 / gy3 * yc
    rx = ( (gx3 - gx2) / gx3 ) * yc + gx2
    return lx, rx, uy, ly
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
def sector_area(r, xa, ya, xb, yb, xc, yc):
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
    return angleB * r * r / 2

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
        #print("************ rotate")
        s = x1
        x1 = y1
        y1 = s
        s = x2
        x2 = y2
        y2 = s
        s = xc
        xc = yc
        yc = s
    
    if x1 > x2: 
        s = x1
        x1 = x2
        x2 = s
        s = y1
        y1 = y2
        y2 = s
        
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
        alpha = sector_area(r, x1, y1, xc, yc, x2, y2)
        if debug: print("Case 0: No intersection", disc, xc, yc)
        return alpha
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
        arc1 = sector_area(r, x1, y1, xc, yc, sx1, sy1)
        arc2 = sector_area(r, sx2, sy2, xc, yc, x2, y2)
        tri = triangle_area(sx1, sy1, xc, yc, sx2, sy2)
        if debug: print("Case 1: ", "(",sx1,sy1,")", "(", sx2,sy2, ")", "  arc1: ", arc1, "  arc2: ", arc2, "  tri: ", tri)
    #
    # case 2: sx1 < x1 < sx2 < x2
    # In this case, we return the traingle formed by (x1, y1, xc, yc, sx2, sy2)
    #                         and the arcs formed by (sx2, sy2, xc, yc, x2, y2)
    elif (sx1 < x1 < sx2 < x2):
        arc1 = sector_area(r, sx2, sy2, xc, yc, x2, y2)
        tri  = triangle_area(x1, y1, xc, yc, sx2, sy2)
        arc2 = 0
        if debug: print("Case 2: ", "(",sx1,sy1,")", "(", sx2,sy2, ")", "  arc1: ", arc1, "  arc2: ", arc2, "  tri: ", tri)
    #
    # case 3: x1 < s1 < x2 < s2
    # In this case, we return the traingle formed by (sx1, sy1, xc, yc, x2, y2)
    #                         and the arcs formed by (x1, y1, xc, yc, sx1, sy1)
    elif (x1 < sx1 < x2 < sx2):
        arc1 = sector_area(r, x1, y1, xc, yc, sx1, sy1)
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
    elif (sx2 < x1) or (sx1 > x2):
        arc1 = sector_area(r, x1, y1, xc, yc, x2, y2)
        arc2 = 0
        tri = 0
        if debug: print("Case 5: No intersection", disc, xc, yc)
    else:
        print("We have a problem: ", x1, y1, x2, y2, xc, yc, r)
        print("  ", "s1:  (",sx1,sy1,")", "  s2: (", sx2,sy2, ")", "  arc1: ", arc1, "  arc2: ", arc2, "  tri: ", tri)
        print("x1, sx1, sx2, x2: ", x1, sx1, sx2, x2)
        print("y1, sy1, sy2, y2: ", y1, sy1, sy2, y2)
        print("xc, yc: ", xc, yc)
        #return 0
    if arc1 < 0 or arc2 < 0 or tri < 0:
        print("Negative: ", arc1, arc2, arc3)
    pos = arc1 + arc2 + tri
    return pos


def point_in_triangle(x, y):
    global gx1, gy1, gx2, gy2, gx3, gy3, gr, debug
    # Compute vectors
    denominator = ((gy2 - gy3)*(gx1 - gx3) + (gx3 - gx2)*(gy1 - gy3))
    
    # Avoid division by zero (degenerate triangle)
    if abs(denominator) < 1e-10:
        return False
    
    # Barycentric coordinates (unnormalized first)
    a = ((gy2 - gy3)*(x  - gx3) + (gx3 - gx2)*(y  - gy3)) / denominator
    b = ((gy3 - gy1)*(x  - gx3) + (gx1 - gx3)*(y  - gy3)) / denominator
    c = 1 - a - b
    
    # Inside if all are non-negative (including boundary)
    return (a >= 0) and (b >= 0) and (c >= 0)


def f(params):
    global gx1, gy1, gx2, gy2, gx3, gy3, gr, debug
    xc, yc = params
    if not point_in_triangle(xc, yc) : return 0
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


def quad(x, y, dx, dy):
    center = True
    maxxy = (x,y)
    maxf = f(maxxy)
    maxdelta = 0
    for nx, ny in [(x-dx, y), (x+dx,y), (x, y+dy), (x, y-dy)]:
        nf = f((nx,ny))
        maxdelta = max(abs(maxf-nf),maxdelta)
        if nf > maxf:
            maxf = nf
            center = False
            maxxy = (nx,ny)
    #print("quad:  maxxy: ", maxxy, "  maxf: ", maxf, "  center: ", center)
    return center, maxxy, maxf, maxdelta

def maxsol(a, b, c):
    global gx1, gy1, gx2, gy2, gx3, gy3, gr, debug
    init_glob(a, b, c)
    #
    # computer center of mass - our starting point
    #
    e = (a * a - b * b + c * c)/(2 * a)
    f = math.sqrt(c * c - e * e)
    xc = (a + e) / 3
    yc = f / 3
    #print("a:",a,"b:",b,"c:",c,"e:",e,"f:",f)
    #
    # we will determine dx by taking the smaller of the distance
    # at yc to each side of the triangle
    # we will determine dy by taking the smaller of the distance  
    # at xc to the top and bottom of the triangle
    #
    ## dx:
    ##   look for the left side (AC) intersection length
    ##   look for the right side (AC) intersection length
    (lx, rx, uy, ly) = tri_intersections(xc, yc)
    
    dx = min(abs(rx-xc),abs(lx-xc))
    dy = min(abs(uy-yc),abs(ly-yc))
    #print("dx:", dx, "dy:", dy, "rx:", rx, "lx:", lx, 
    #        "uy:", uy, "ly:", ly, "xc:", xc, "yc:", yc)
    done = False
    oldmaxf = 0
    while not done:
        center, (xc, yc), maxf, maxdelta = quad(xc, yc, dx, dy)
        if center:
            dx /= 2
            dy /= 2
        if maxdelta < 0.000001: done = True
        oldmaxf = maxf
        #print("dx, dy: ", dx, dy, "  a, b, c: ",  a,b,c, ", xc, yc: ", xc,yc,  "   max: ", maxf)
    return maxf, (xc, yc)

def doprob():
    p966  = 0
    for a in range(1, 201):
        for b in range(a, 201):
            for c in range(b, a + b):
                if a+b+c > 200: continue
                val, xy = maxsol(a, b, c)
                #print(a, b, c, val, xy, flush=True)
                p966 += val
    print("Answer: ", p966)


#debug = True
# maxsol(2, 89, 90)
doprob()
#maxsol(1,1,1)
