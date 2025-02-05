import copy

runs = [[1,1,0,0,0,0]]

total_picks = 0
total_a5s = 0
total_singles = 0
prob_singles = 0

def issingle(r):
    cnt = sum(r[1:])
    if cnt == 1: return True
    return False


def update(r):
    global total_picks, total_a5s, total_singles, prob_singles
    ret = []
    for pick in r:
        if issingle(pick): 
            total_singles += 1
            prob_singles += pick[0]
        #pick[0] += 1
        choices = sum(pick[1:])
        #print(choices, " total choices", pick)
        total_picks += choices
        total_a5s += pick[5]
        for j in range(1,6):
            if pick[j] > 0:
                n = copy.deepcopy(pick)
                #print(pick[j], choices)
                n[0] *= pick[j] / choices
                n[j] -= 1
                for k in range(j+1,6):
                    n[k] += 1
                ret.append(n)
                #print(n)
    return ret

total_picks = 0
total_a5s = 0
total_singles = 0
l = update(runs)
prob_singles = 0
debug = False
for n in range(1,15):
    if debug: 
        print("******************* Trial ", n, " ************************")
        prob = 0
        for a in l:
            print(a)
            prob += a[0]
        print("total prob: ", prob)
    l = update(l)
if debug: print(total_a5s, total_picks, total_singles, total_a5s/total_picks)

if debug: print(total_singles/total_picks)
print(prob_singles)

