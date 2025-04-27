


'''
Definition of a K circuit:
[x1,x2,..,xm,n]

n is a number such that the sum of x1 thru xm 
plus n add up to K, n can be any number from 0..K
x1, x2 ... xm is a number 2 or greater
n + x1 + x2 + ... + xm = K

Each xi represents all parallel circuits that have xi components

To begin, we will create G[j], where G[j] is a list of all possible parallel values
that can be formed by j resistors each with value 1
To do this, we form all unique partitions of j and compute the recipricol of the sums
of the recipricoal values from each of the partitions.

'''

def same(a, b):
    delta = abs(a-b)
    if delta < 1e-14: return True
    #if delta < 1e-13: print(a,b)
    return False

def do_count(g, debug = False):
    cnt = 1
    g.sort()
    last = g[0]
    for r in g:
        if same(last, r): continue
        last = r
        cnt += 1
    if debug: print("Length: ", len(g), "  Unique: ", cnt)
    return cnt

def sumrecips(l):
    sr = 0
    for x in l:
        sr += 1.0/x
    return 1/sr

def compvalue(L, K):
    v = 0
    kcheck = 0
    for l in L:
        if isinstance(l, list):
            if len(l) == 1:
                print("ERROR - malformed list element: ", l)
                exit(1)
            v += sumrecips(l)
            kcheck += sum(l)
        elif isinstance(l, int):
            v += l
            kcheck += l
        else:
            print("ERROR - element not an int or a list")
            exit(1)
    if kcheck != K:
        print("ERROR - list adds to ", kcheck, " not ", K)
        exit(1)
    return v


def find_partitions(N):
    def partitions(n, min_part, current_partition, result):
        if n == 0:
            result.append(current_partition[:])
            return
        for k in range(min_part, n + 1):
            current_partition.append(k)
            partitions(n - k, k, current_partition, result)
            current_partition.pop()
    
    result = []
    if N < 2:
        return result
    partitions(N, 1, [], result)
    return result

# Example usage
def get_partitions(N, debug=False):
    partitions = find_partitions(N)
    if not partitions:
        if debug: print(f"No partitions for N={N} with parts >= 2")
    else:
        if debug: print(f"Partitions for N={N}:")
        for p in partitions:
            if debug: print(f"{p} (sum: {' + '.join(map(str, p))} = {N})")
    return partitions

def addlists(Lists):
    K = 0
    Total = 1
    for l in Lists:
        Total *= len(l)
    gg = [K]*Total
    part_cycle = 1
    for p in Lists:
        for i in range(Total):
            gg[i] += p[(i // part_cycle) % len(p)]
        part_cycle *= len(p)     # this partition cycles every part_cycle units
                
    return gg

#
# For each resistor count R, we'll find all partitions
# of R where the last number in the partition is the number os series resistors
# if R = x + y + K, then the total number of resistor layouts are
# len(P(x)) * len(P(y)), and the values of the circuit are given by
#   G(i,j) = P(x)[i] + P(y)[j] + K
#
# if R = x + y + z + M, then the total number of resistor layouts are
# len(P(x)) * len(P(y)) * len(P(z)), and the values of the circuit are given by
#   G(i,j,k) = P(x)[i] + P(y)[j] + P(z)[k] + M
#
# 
#  
def addrvalues(ALL, RPARTS, K, part, debug=False):
    #K = part[0]    # K is last element
    if debug: print("part: ", part)
    lists = []
    for p in part:
        lists.append(RPARTS[p])
    gg = addlists(lists)
    if debug: print("K=",K, gg)
    #print(gg)
    for g in gg:
        ALL.append(g+K)
        if debug: print(g+K)
        
from sympy.utilities.iterables import partitions

def partitions_no_ones(n):
    result = []
    for p in partitions(n, k=None):
        parts = sorted([k for k, v in p.items() for _ in range(v)], reverse=True)
        if all(x > 1 for x in parts):
            result.append(parts)
    return result
    
sg = [[],[1]]
totalParts = 0
for N in range(2, 19):
    P = get_partitions(N)
    g = []
    for p in P:
        sr = sumrecips(p)
        g.append(sr)
    #for p in P:
    #    print(p)
    sg.append(g)

    #print(N, " Total number of recips: ", len(g), "  unique: ", do_count(g))     
               
ggg = []
MaxNumberOfResistors = 18
debug = False
for R in range(1, MaxNumberOfResistors+1):
    #if R == MaxNumberOfResistors: debug = True
    if R == 1:
        ggg.append(1)
        continue
    for r in range(R+1):
        dr = R - r
        if debug: print(">>>>>>>>>>>>>>>>>  R r dr: ", R, r, dr)
        # dr will represent the number of slots
        # available for parallel resistors, as the series
        # resistors are define by r
        # we will determine all of the possible parallel combos,
        # then add dr to these values to add to our list of all
        # possible values
        # NOTE: sg[k] is the list of all possible parallel values
        # containing exactly k resistors
        # so, we form all partitions of dr (for which 1 is not
        # in the partition) then form all possible sums of these
        # values to get to the possible values formed
        ppp = partitions_no_ones(dr)
        #if dr == 0: print(ppp)
        if debug: print("<<<<", r, "sg[",r,"]", sg[r], " ppp:", ppp)
        for p in ppp:
            addrvalues(ggg, sg, r, p, debug)
if debug: print(ggg)
print(">>> Total number of recips: ", len(ggg), "  unique: ", do_count(ggg))
#print(ggg)
## Incorrect>>> Total number of recips:  356950   unique:  356201
## Incorrect>>> Total number of recips:  356951   unique:  20838
## from:  https://oeis.org/A153588/b153588.txt  18 3857447
