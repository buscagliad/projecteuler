
MAX=10**8
MAX=10**2

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
aaab()
aabb()
abbb()
