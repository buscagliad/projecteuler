




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

from sympy.utilities.iterables import partitions

def partitions_no_ones(n):
    result = []
    for p in partitions(n, k=None):
        parts = sorted([k for k, v in p.items() for _ in range(v)], reverse=True)
        if all(x > 1 for x in parts):
            result.append(parts)
    return result





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

def comp_rec(part):
    r = 0
    for a in part:
        r += 1/a
    return 1/r

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
    
# Test for N = 6
#if __name__ == "__main__":
#    N = 18
def caps(n, debug = False):
    if n == 1: return 1
    g = []
    for j in range(0, n+1):
        parts = get_partitions(j)
        print(parts)
        for p in parts:
            if debug: print(f"{p} ", comp_rec(p))
            g.append(comp_rec(p)+n-j)
    g.sort()
    if debug: print(g)
    return do_count(g)
    
def getCircuits(n):
    P = []
    for k in range(n):    # k then and all partitions with at least two elements
        parts = get_partitions(n-k)
        for p in parts:
            C = [k, p]
            P.append(C)
    P.append([n])
    return P

pp = get_partitions(17)
g=[]
for p in pp:
    print(p)
    if p == [17]: p = 17
    g.append(compvalue([p], 17))

g.sort()
cnt = do_count(g)
print("There are ", cnt, " unique circuits")


# Get all partitions of 18 with no 1s
for N in range (2, 19):
    partitions_18_no_ones = partitions_no_ones(N)
    unique_sorted_partitions = sorted(partitions_18_no_ones)

    print(N, len(unique_sorted_partitions))

exit(1)

cc = getCircuits(3)
for c in cc:
    print(c)
exit(1)
N=4
un = 0
for j in range(1, N+1):
    print("----------------------")
    k = caps(j, True)
    print(j, k)
