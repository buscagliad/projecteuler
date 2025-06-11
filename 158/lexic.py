from math import comb



def choose(n, k):
    if k == 0: return 1
    if n <= 0: return 0
    if k <= 0: return 0
    if n < k: return 0
    return comb(n, k)

    
def skm(L, k, m, debug = False):
    A = m - 2
    B = L - m - 1
    if debug: print("A=",A, "  B=", B, "  L=",L, "  m=",m,"  k=", k)

    #
    # Edge case 1: m == 2, odd element at position 2
    #
    # Verified
    if m == 2:
        return (k - L + 1) * choose(k-1,L-m)
    #
    # Edge case 2: m == L, odd element at end position
    #
    # Verified
    if m == L:
        s = 0
        T = 26 - (L - m + 1)
        for x in range(1, k):
            s += choose(T-x, L - 2)
        return s
        
    #
    # Edge case 3: (similar to case 1) odd element next to last
    #
    # Verified
    if m == L-1:
        s = 0
        N = 26

        for l in range(1, k):
            for r in range(1, k):
                if l == r: continue
                choices = N - l - 2
                if l > r: choices += 1
                
                #print(l,r,"choices: ", choices, "  ", choose(choices, A))
                s += choose(choices, A)
        return s
        
    #
    # All other cases, there are elements to the left and right
    # of the three element sequence:  l < k > r
    # all elements to left of l are > l
    # all elements to right of r are < r
    # the relationship between l and r will create more or fewer
    # choices
    # 
    # In this case we have the format for the length L sequence
    # with the left sequence made up of A elements and the right
    # sequence made up of B elements
    #
    # __ __ ... __  l  k  r  __ __ ... __
    #
    # <--- A ----> <-- 3 --> <--- B ---->
    # <----------------- L ------------->
    #
    # NOTES:
    #   o  When l < A, there are no solutions
    #   o  When r < B, there are no solutions
    #   o  A + B + 3 = L
    # 
    # LEFT SIDE:
    #   lf l > r, only choices from {26, 25, ..., l+1} are available
    #       if l < A: no possible combinations, as there are more
    #                 spaces than numbers to fill them
    #       Left combos:  (26 - (l+1) + 1) choose A
    #                     (26 - l) choose A
    #   if l < r, then we remove r - l elements from the set above
    #       Left combos:  (26 - (l+1) + 1 - (r - l)) choose A
    #                     (27 - r) choose A
    #
    # RIGHT SIDE:
    #   lf l > r, only choices from {1, 2, ..., r-1} are available
    #       Right combos:  (r - 1) choose B
    #   if l < r, then we remove r - l + 1 elements from the set above
    #       Right combos:  (r-1 - (r-l + 1)) choose B
    #                      (l - 1) choose B
    #
    s = 0
    N = 26
    for l in range(1, k):
        for r in range(1, k):
            if l == r: continue
            if 26-l <= A or r <= B: 
                if debug:
                    if 26-l <= A: print("26-l <= A: ", 26-l, " <= ", A)
                    if r <= B: print("r <= B: ", r, " <= ", B)
                continue
            #
            # the number of 'right' choices is r - B
            # this number is reduced by 1 if l < r
            rightChoices = r - B
            Rstar = " "
            if l < r: 
                Rstar = "*"
                rightChoices -= 1
            
            #
            # the number of 'left' choices ir 26 - B - 3,
            # as these choices have been consumbed by the
            # (l k r) component, and the remaining B slots
            # however, if l is smaller than k by B + 1 units
            # then there is an additional set of numbers to use
            leftChoices = min(26-3-B, 26 - l) # most choices for left side
            remUnits = 0
            Lstar = " "
            if l < r: 
                leftChoices -= remUnits
                Lstar = "*"
            #if l < r: leftChoices -= 1

            cl = choose(leftChoices, A)
            cr = choose(rightChoices, B)    
            if debug: print("l: ", l, " r: ", r, " k: ", k, 
                    "  leftChoices: ", leftChoices, Lstar, cl,
                    "  rightChoices: ", rightChoices, Rstar, cr, "  prod: ", cl*cr)
            s += cl * cr
    return s    

def table(L):
    for k in range(1, 27):
        print(k, end=",")
        for m in range(L-2, L-1):
            print(skm(L, k, m), end=",")
        print()
            

def P3(L):
    s = 0
    for k in range(1, 27):
        #print(k, end="  ")
        #for m in range(2, L+1):
        for m in range(2, L+1):
            s += skm(L, k, m)
    return s
    #for k in range(1, 27):
    #    print("m=", L, k, skm(L, k, L))

d = skm(7,4,5,True)
print("skm=",d)
d = skm(7,5,5,True)
print("skm=",d)
exit(1)
table(7)
exit(1)
for L in range(3, 26):
    print("L = ", L,"  P(L) = ", P3(L))



