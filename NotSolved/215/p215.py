
import math

def mn(m, n):
    return math.comb(m + n, m)
        

def get23s(size):
    #
    # find orderder list
    max2 = size//2
    max3 = size//3
    n2 = 0
    n3 = 0
    done = False
    ll23 = []
    #print(max2, max3)
    while not done:
        ll = []
        for n2 in range(max2):
            ll.append(2)
        #print(max2, ll)
        for n3 in range(max3):
            if sum(ll) + 3 > size: break
            ll.append(3)
            if sum(ll) == size: break
        if sum(ll) == size:
            ll23.append(ll)
        
        max2 -= 1
        if max2 == -1: done = True
    for k in ll23:
        m = k.count(2)
        n = k.count(3)
        print (mn(m,n) , sum(k), k)

get23s(9)
get23s(32)


                
