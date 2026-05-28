
list2 = [[1,1]]
list3 = [[1,1,1],[2,1],[1,2]]
list4 = [[1,1,1,1],[2,1,1],[1,2,1],[1,1,2],[2,2]]
list5 = [[1,1,1,1,1],[2,1,1,1],[1,2,1,1],[1,1,2,1],[1,1,1,2], [2,2,1],[2,1,2],[1,2,2]]
list6 = [[1,1,1,1,1,1],[2,1,1,1,1],[1,2,1,1,1],[1,1,2,1,1],[1,1,1,2,1],[1,1,1,1,2],
           [2,2,1,1],[2,1,2,1],[2,1,1,2],[1,2,1,2],[1,1,2,2],[1,2,2,1],[2,2,2],[3,1,1,1],
           [1,3,1,1],[1,

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
    print(nsqr, digs)

numsplit(351)
    
print(dosum([8,1],[1,1]), " expect 9 ")
print(dosum([6,7,2,4],[1,2,1]), " expect 82")
    
