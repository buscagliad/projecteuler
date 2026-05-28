
MAX=1

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

MAX = 1000

def abc():
    MAX8 = 8*MAX
    a = 0
    b = 0
    c = 0
    qsum = 0
    x = 0
    for a in range(MAX):
        if (3*a*a - 6*a > MAX8): break
        print("a: ", a, flush=True)
        for b in range(a, MAX):
            if (3*a*a + 4*b*b - 4*a*b -2*a - 4*b > MAX8): break
            for c in range(b, MAX):
                x8 = 3 * ( a*a + b*b + c*c ) - 2 * ( a*b + a*c + b*c ) - 2 * (a + b + c)
                if x8 > MAX8: break
                if x8 < 8: continue
                if x8 % 8 == 0:
                    x = x8 // 8
                    if x+c > MAX: break
                    four = (x, x+a, x+b, x+c)
                    #if av(four):
                    #    print(x, a, b, c, four)
                    qsum += 4 * x + a + b + c
                    qsum %= 433494437

    return qsum

print(MAX, abc())
                
