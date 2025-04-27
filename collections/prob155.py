
class circuit:
    def __init__(self):
        self.parallel = []  # parallel will contain lists of lists
        self.series = 0

'''
Definition of a K circuit:
[[x],[y],n]

x is either the number 2 or greater, or a list of two or more integers
y is the same
n is a number such that the sum of [x], [y] (and any other parrallel entities
plus n add up to K

To compute the 'value' of the K circuit, we go through each list element (the
'x' and 'y' lists (there may be more, there may be few)
each list has a value equal to the sum of the reciprocols of each element
then taking the reciprocal of that sum.  Each list value is added together
along with the last number (n) in the circuit.
'''
import copy as cp

def same(a, b):
    if abs(a-b) < 1e-9: return True
    return False

def do_count(g, debug = False):
    cnt = 1
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

'''
def addparallel(pc):    # parallel circuit
    rpc = []
    for c in pc:
'''
#
# for a given parallel circuit C, increment each entry
# and add one parallel element
#
def addparallel(C):
    NC=[]
    for i, c in enumerate(C):
        cc = cp.deepcopy(C)
        cc[i] += 1
        NC.append(cc)
    cc = cp.deepcopy(C)
    cc.append(1)
    NC.append(cc)
    return NC
#
# newcircuit - takes each circuit in C and produces the next level
# circuit by going thru each parrallel sub-circuit, and incrementing
# each entry by one, and finally adding one to this circuit
# this continues until all parallel circuits have been gone thru
# this ends with incrementing the last 'serial' subcircuit (unless
# it does not exist, in which case one is added
#

def newcircuit(C):
    NC=[]
    haslast = False
    for i, q in enumerate(C):
        if isinstance(q, list):
            P = addparallel(q)
            for p in P: NC.append(p)
        elif isinstance(q, int):
            cc = cp.deepcopy(C)
            cc[i] += 1
            haslast = True
            NC.append(cc)
    if not haslast:
        cc = cp.deepcopy(C)
        cc.append(1)
        NC.append(cc)

    return NC

def addresistor(P):
    RES=[]
    for c in P:
        nc = newcircuit(c)
        for c in nc:
            RES.append(c)
    return RES

P1 = [[1]]
P2 = [[2], [[1,1]]]
P3 = [[3], [[2,1]], [[1,1,1]], [[1,1],1]]
P4 = [ [[1,1],2], [4], [[1,2],1], [[1,1,1],1], [[1,1,1,1]] ]

q = addresistor(P3)
for j in q: print(j)

exit(1)
print(newcircuit([1]))
exit(1)

P = [P1,P2,P3] #,P4]
g = []

for k, C in enumerate(P):
    for p in C:
        v = compvalue(p, k+1)
        print(p, v)
        g.append(v)

# Test for N = 6
#if __name__ == "__main__":
#    N = 18
g.sort()
if True: print(g)
cnt = do_count(g)
print("There are ", cnt, " unique circuits")
