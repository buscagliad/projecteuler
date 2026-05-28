
MAX=10**8
MAX=10**2
def solve_quad_mod8(a, b, c):
    a, b, c = a%8, b%8, c%8
    solutions = []
    for x in range(8):
        if (a * x * x + b * x + c) % 8 == 0:
            solutions.append(x)
    return solutions

# Example
#print(solve_quad_mod8(1, 1, 6))   # → [1, 6]

def av(t):
    m = sum(t)
    var = ((4*t[0]-m)**2 + (4*t[1]-m)**2 + (4*t[2]-m)**2 + (4*t[3]-m)**2) 
    if 8*m == var : return True
    print("ERROR: ", t, m, var)
    exit(1)
    return False

def aaab ():
    """ Function doc """
    x8 = 0
    k = 1
    while True: # x8 <= 8 * MAX :
        x8 = 3 * k * k - 2 * k
        if x8 % 8 == 0:
            if x8//8 + k + 1 <= MAX:
                x = x8 // 8
                four = (x, x, x, x+k)
                if (av(four)):
                    print(four)
            else:
                break
        k += 1

def aabb():
    k = 2
    while True:
        t = (k*k - k)
        if t % 2 == 0:
            x = t // 2
            if x + k <= MAX:
                four = (x, x, x+k, x+k)
                if av(four):
                    print(t, k, four)
            else:
                break
        k += 1
        
def abbb():
    k = 3
    while True:
        t = (3*k*k - 6*k)
        if t % 8 == 0:
            x = t // 8
            if x + k <= MAX:
                four = (x, x+k, x+k, x+k)
                if av(four):
                    print(t, k, four)
            else:
                break
        k += 1
# aaab()
# aabb() 
# abbb()

MAX = 100000

def abc():
    MAX8 = 8*MAX
    a = 0
    b = 0
    c = 0
    qsum = 0
    x = 0
    for a in range(0,MAX):
        if (3*a*a + 6*a > MAX8): break
        #print("a: ", a, flush=True)
        for b in range(a, MAX):
            if (3 * a * a + 4 * b * b - 4 * a * b - 2 * a - 4 * b > MAX8): break
            f8 = 0
            cs = solve_quad_mod8(3, -2 * (a + b + 1), 3 * (a*a + b*b) -2*(a*b + a + b))
            if len(cs) == 0: continue
            done = False
            #c = b
            while not done:
                for cm in cs:
                    c = 8*f8 + cm
                    if c < b: continue
                    x8 = 3 * ( a*a + b*b + c*c ) - 2 * ( a*b + a*c + b*c ) + 2 * (a + b + c)
                    if x8 > MAX8: 
                        done = True
                        break
                    if x8 < 8: continue
                    x = x8 // 8
                    if x < 3: continue
                    if x > MAX: 
                        print("x: ", x, "a, b, c: ", a, b, c, "  x+c: ", x+c, "   f8: ", f8, "  (f8-1)*8 +cm = ", (f8-1)*8+cm)
                        done = True
                        break
                    else:
                        four = (x-c, x-b, x-a, x)
                        #if av(four):
                        if (x == MAX): 
                            if (a == b): print("a=b", end="")
                            if (b == c): print("b=c", end="")
                            print(a, b-a, b, c-b, c, x, four)
                        qsum += 4 * x - a - b - c
                        qsum %= 433494437
                f8 += 1

    return qsum

print(MAX, abc())
                
#
# NOTE: for MAX = 1000, sum is: 37048340
# 1000000 374740769
