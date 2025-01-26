def rowksum(K):
    if K == 0:
        return 1
    prod = 1
    while K > 0:
        prod *= (K % 7 + 1)
        K //= 7
    return prod

def sumrows(k):
    s = 0
    for i in range(k):
        s += rowksum(i)
        if i % 1000000 == 0:
            print(i, s, flush=True)
    return s

p = 1
# for k in [7, 7**2, 7**3, 7**4, 7**5, 7**10]:
    # print("k: ", k, "   num: ", sumrows(k), 2**(2*p) * 7**p)
    # p += 1
print(sumrows(1000000000))
