from fractions import Fraction

from sympy import factorint
#Twos = [2**k for k in range(10)]
#Fives = [5**k for k in range(10)]


def num_facts(n):
    n = factorint(n)
    k = 1
    for f in n:
        k *= (1 + n[f])
    return k

def twofivelist(n):
    l = []
    #
    # do 1, 2's & 5's
    two = 1
    for j in range(n+1):
        five = 1
        for m in range(n+1):
            l.append((1,two*five))
            five *= 5
        two *= 2
    #
    # do 2^k with 5^m
    two = 1
    for k in range(1, n+1):
        two *= 2
        five = 1
        for j in range(1, n+1):
            five *= 5
            l.append((two, five))
    return l

#
# for 1/a + 1/b = p/10^n (1)
# only solutions for gcd(a,b) = 1 are
# a is 1 and b is any combinations of 2^n * 5^m where
#                          0 <= n,m <= n
# and then for a in {2, 2^2, ..., 2^n} and b in {5, 5^2, ..., 5^n}
#
# in all cases, p = 10^n * (a + b)//ab
# we can form more solutions by dividing both sides of (1)
# by any factor of p, thus, for a given a,b with gcd(a,b) = 1,
# we can form num_facts(p) of solutions
# we go through all pairs of (a,b) described above, compute p,
# then add num_facts(p) to a sum
#
# we do the above for n = 1, 2, ..., 9
# then add all of these results
#
def countrecip(n):
    cnt = 0
    pairs = twofivelist(n)
    for (a,b) in pairs:
        p = (10**n * (a + b))//a//b
        cnt += num_facts(p)
    return cnt

tc = 0
for n in range(1, 10):
    c = countrecip(n)
    print(n, c)
    tc += c
print(tc)

