import math

list2 = [[1,1]]
list3 = [[1,1,1],[2,1],[1,2]]
list4 = [[1,1,1,1],[2,1,1],[1,2,1],[1,1,2],[2,2],[3,1],[1,3]]
list5 = [[1,1,1,1,1],[2,1,1,1],[1,2,1,1],[1,1,2,1],[1,1,1,2], [2,2,1],[2,1,2],[1,2,2],
         [3,1,1]]
list6 = [[1,1,1,1,1,1],[2,1,1,1,1],[1,2,1,1,1],[1,1,2,1,1],[1,1,1,2,1],[1,1,1,1,2],
           [2,2,1,1],[2,1,2,1],[2,1,1,2],[1,2,1,2],[1,1,2,2],[1,2,2,1],[2,2,2],[3,1,1,1],
           [1,3,1,1],[1,1,3,1]]

xsplits=[]
xsplits.append([])   # 0
xsplits.append([])   # 1
xsplits.append(list2)


#
# creates a set of lists,
# where each set has elements that sum to n, and contain only postive integers
#
def splitList(n):
    sList = []
    start = [1]*n
    
def insertone(ll, ix):
    nl = []
    app = False
    for j, k in enumerate(ll):
        if j == ix: 
            app=True
            nl.append(1)
        nl.append(k)
    if not app:
        nl.append(1)
    if sum(ll) +1 != sum(nl):
        print("ERROR inOne: ", ll, ix, nl)
    return nl

def addone(ll, ix):
    nl = []
    for j, k in enumerate(ll):
        if j == ix: nl.append(k+1)
        else: nl.append(k)
    #print("addOne: ", ll, ix, nl)
    if sum(ll) +1 != sum(nl):
        print("ERROR addone: ", ll, ix, nl)
    return nl

def nextlist(listA, ck):
    #print("nextlist: ", listA)
    nlist = []
    mn = 0
    for l in listA:
        mn = max(mn, max(l))
    #
    # insert 1 at every spot
    #
    for l in listA:
        for ix in range(mn):
            newl = insertone(l, ix)
            if newl not in nlist:
                nlist.append(newl)
    #
    # add 1 at every spot
    #
    for l in listA:
        for ix in range(len(l)):
            newl = addone(l, ix)
            if newl not in nlist:
                nlist.append(newl)
        
    #print(listA)
    #print(nlist)

    return nlist

##
## Create split lists
##
nl = xsplits[2]
for _ in range(3, 14):
    nl = nextlist(nl, _)
    xsplits.append(nl)

##
## remove any that do not have log10(sqrt()) or greater
##

splits = [[],[]]
for pten in range(2, 14):
    nsplit = []
    maxval = pten // 2
    for ns in xsplits[pten]:
        if max(ns) < maxval: continue
        nsplit.append(ns)
    splits.append(nsplit)

def check():
    for k, sp in enumerate(splits):
        for s in sp:
            if sum(s) != k:
                print(s, sum(s), k)
            else: print(sum(s), " : ", s)


def digits(n):
    digs = []
    while n > 0:
        digs.insert(0, n % 10);
        n //= 10
    return digs
    
def dosum(digs, dord):
    s = 0
    i = 0
    for m, d in enumerate(dord):
        v = 0
        for k in range(d):
            v = 10 * v + digs[i]
            i += 1
        s += v
    return s

def allsums(digs, n):
    ldigs = len(digs)
    maxg = ldigs // 2
    


def numsplit(n):
    nsqr = n * n
    digs = digits(nsqr)
    #print(nsqr, digs)

def test1():
    numsplit(351)
        
    print(dosum([8,1],[1,1]), " expect 9 ")
    print(dosum([6,7,2,4],[1,2,1]), " expect 82")

def getnum(diglist, n):
    s = 0
    #print("getnum:: ", diglist, n, end="")
    for cnt, i in enumerate(diglist):
        s = 10*s + int(i)
        if cnt >= n - 1: break
    #print(" --> ", s)
    return s

def s_sum(dl, ls):
    s = 0
    index = 0
    #print("s_sum:: ", dl, ls)
    for j in ls:
        s += getnum(dl[index:], j)
        index += j
    return s

def is_s_number(dl, v):
    ll = splits[len(dl)]
    #print("is_s_number:: ", dl, v, ll)
    for ls in ll:
        ss = s_sum(dl, ls)
        if ss == v: 
            #print(ls, dl, v, flush=True)
            return True
    return False
    
def do_num_splits(N):
    lval = 10**8
    ts = 0
    mn = int(math.sqrt(N) + 0.5) + 1
    for t in range(1, mn):
        if t % 9 > 1 : continue  # speed up trick digit sums are preserved mod 9
        sq = t * t
        sqs = digits(sq)
        if (is_s_number(sqs, t)):
            #print(sqs, sq%9, t%9)
            ts += sq
        if sq > lval:
            print(sq, ts, flush=True)
            lval *= 10
            
    return ts

print(do_num_splits(10**12))
#print(do_num_splits(10000))
