from fractions import Fraction

n = 3
tp = 10**n
cnt = 0
for a in range(1, 20*tp):
    f1 = Fraction(1, a)
    for b in range(a, 20*tp):
        f2 = Fraction(1, b)
        s = f1 + f2
        #print(f1, f2, s, isinstance(s, Fraction), type(s))
        q = s.denominator
        k = tp % q
        if k == 0:
            j = 10 // q
            print(a, b, j*s.numerator)
            cnt += 1
print("n: ", n, "  count: ", cnt)
