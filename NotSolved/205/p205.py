"""
Peter has nine four-sided (pyramidal) dice, each with faces numbered 1, 2, 3, 4.
Colin has six six-sided (cubic) dice, each with faces numbered 1, 2, 3, 4, 5, 6.

Peter and Colin roll their dice and compare totals: the highest total wins. 
The result is a draw if the totals are equal.

What is the probability that Pyramidal Peter beats Cubic Colin? 
Give your answer rounded to seven decimal places in the form 0.abcdefg.
"""
from collections import Counter

def getRollsX(m, k):
    max_sum = m * k
    rolls = [0] * (max_sum + 1)
    rolls[0] = 1
    
    for _ in range(m):
        new = [0] * (max_sum + 1)
        window_sum = 0
        
        for s in range(max_sum + 1):
            window_sum += rolls[s]
            if s - k - 1 >= 0:
                window_sum -= rolls[s - k - 1]
            new[s] = window_sum
        
        rolls = new
    
    return rolls

def getRolls(m, k):
    # DP computation

    counts = Counter({0:1})
    for _ in range(m):
        new = Counter()
        for s, c in counts.items():
            for d in range(1, k+1):
                new[s+d] += c

        counts = new
    ll = [0]*(m*k+1)
    for c in counts:
        print(c, counts[c])
        ll[c] = counts[c]
    return ll

rolls4 = getRolls(9, 4)
rolls6 = getRolls(6, 6)
print(rolls4)


for n, r in enumerate(rolls4):
    print(n, r, r/(4**9))

times4wins = 0
num4rolls = 4 ** 9
num6rolls = 6 ** 6

for n, r in enumerate(rolls4):
    if r == 0: continue
    #
    # can we win with this roll?
    if (rolls6[n-1] > 0):
        for k in range(1, n):
            times4wins += r * rolls6[k]
# 0.5731440767829815 
print(times4wins/num4rolls/num6rolls)
