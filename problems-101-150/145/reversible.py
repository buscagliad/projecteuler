
class dignum:
    def __init__(self, n):
        self.digs = []
        while n:
            self.digs.append(n % 10)
            n //= 10
    def out(self):
        print(self.digs)
    def revsum(self):
        res = []
        carry = 0
        k = len(self.digs) - 1
        for i, dig in enumerate(self.digs):
            dsum = dig + self.digs[k] + carry
            k -= 1
            if (dsum % 10) % 2 == 0: return False
            carry = dsum // 10
        if carry == 0: return True
        return carry % 2 == 1

l = 10
r = 100
tcount = 0
for j in range(7):
    count = 0
    for n in range(l, r, 2):
        if n % 10 == 0: continue
        d = dignum(n)
        if d.revsum(): 
            count += 1
            #d.out()
    l = r
    r *= 10
    count *= 2
    print("Digits: ", j + 2, "  num rev: ", count, flush = True)
    tcount += count
    
print("Number of reversible numbers less than 1,000,000,000 is: ", tcount)
