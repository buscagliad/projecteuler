import numpy as np
from shapely.geometry import Polygon, Point
import math

# coarse grid then refine
def search(triangle, xs, ys, r):
    best=0; best_xy=None
    for x in xs:
        for y in ys:
            inter = Point(x,y).buffer(r,128).intersection(triangle).area
            if inter>best:
                best=inter; best_xy=(x,y)
    return best, best_xy

def minarea(a, b, c):
    s = (a + b + c) / 2.0
    A = math.sqrt(s * (s - a) * (s - b) * (s - c) )
    y = A * 2 / a
    x = math.sqrt(c * c - y * y)
    triangle = Polygon([(0,0),(a,0),(x, y)])
    #print(A, triangle.area)
    r = np.sqrt(A/np.pi)
    xs = np.linspace(0,a,120)
    ys = np.linspace(0,b,160)
    best, xy = search(triangle, xs, ys, r)
    print(xs, ys, r, best, xy)

    for step in [0.2,0.05,0.01]:
        x0,y0=xy
        xs = np.linspace(x0-step,x0+step,80)
        ys = np.linspace(y0-step,y0+step,80)
        best, xy = search(triangle, xs, ys, r)
    return best
print(minarea(3, 4, 6))
exit(1)
p966  = 0
for a in range(1, 201):
    for b in range(a, 201):
        for c in range(b, a + b):
            if a+b+c > 200: continue
            D = minarea(a, b, c)
            print(a, b, c, D, flush=True)
            p966 += D
            
print(p966)

