from fractions import Fraction

primelist=[1,2,3,5,7,11,13]

def createlist(n):
    l = []
    two = 1
    for j in range(n+1):
        five = 1
        for m in range(n+1):
            l.append(two*five)
            five *= 5
        two *= 2
    l.sort()
    return l

#
# if a and b are pure 2^m * 5^k numbers,
# tfcount will count how many solutions of this form
#
def tfcount(n):
    tsum = 0
    for k in range(n+1):
        for m in range(n+1):
            tsum += (n - k + 1) * (n - m + 1)
    return tsum

#
# a and b must be of the form:  s * 2^m * 5^k 
# to be solutions of the diophantine equation
# BUT: the value of A <= B and B <= 2 * 10^(N+Nadd)
# Given N, how many s's exist that satisfy the
# above constraints:
#
Twos = [2**k for k in range(10)]
Fives = [5**k for k in range(10)]
print(Twos, Fives)
def allcount(N):
    ssum = 0
    Nadd = 1
    for r in range(N+Nadd):
        A = Twos[r]
        for q in range(N+Nadd):
            B = Fives[q]
            if B < A: continue
            print(A,B)
            ssum += (N - r + 1) * (N - q + 1)
    for r in range(N+Nadd):
        A = Fives[r]
        for q in range(N+Nadd):
            B = Twos[q]
            if B < A: continue
            print(A,B)
            ssum += (N - r + 1) * (N - q + 1)
    return ssum

for N in range(1, 5):
    print(">>>>>>>>", N, allcount(N))
exit(1)
            
       
    
    

n = 2
cset = []
total = 0
for n in range(1, 10):
    #print("*************  ", n, "  ***************")
    tp = 10**n
    cnt = 0
    Max = 20 * tp
    twofive = createlist(n)
    #print(twofive)
    s = 1
    done = False
    while not done:
        done = True
        for a in twofive:
            A = s * a
            if A > Max: break
            f1 = Fraction(1, A)
            for b in twofive:
                done = False
                B = s * b
                # B >= A
                if B < A: continue
                f2 = Fraction(1, B)
                sf = f1 + f2
                #print(f1, f2, s, isinstance(s, Fraction), type(s))
                q = sf.denominator
                k = tp % q
                if k == 0:
                    j = tp // q
                    if not (A,B) in cset:
                        #print(A, B, j*sf.numerator)
                        cset.append((A,B))
        s += 1
    print("n: ", n, "  count: ", len(cset), flush=True)
    total += len(cset)
    cset.clear()

print(total)
