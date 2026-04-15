
MAX=10**8

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
        x8 = 3 * k * k + 4 * k + 1
        if x8//8 + k + 1 <= MAX:
            if x8 % 8 == 0:
                x = x8 // 8
                c = k + 1
                four = (x, x, x, x+c)
                if (av(four)):
                    print(four)
        else:
            break
        k += 1

def aabb():
    k = 2
    while True:
        x = (k*k - k) // 2
        if x + k <= MAX:
            a = k
            four = (x, x, x+a, x+a)
            if av(four):
                print(four)
        else:
            break
        k += 1
aabb()
