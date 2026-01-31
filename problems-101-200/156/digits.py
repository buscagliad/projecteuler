debug = False
#
# NOTE: f (x) = count_digit_occurences(x, d)
#        d
#
def count_digit_occurrences(N, D):
    count = 0
    pow = 1  # Start with units place (10^0)
    while pow <= N:
        left = N // (pow * 10)  # Digits to the left
        right = N % pow         # Digits to the right
        digit = (N // pow) % 10 # Current digit
        
        if digit > D:
            xx = (left + 1) * pow
        elif digit == D:
            xx = left * pow + right + 1
        else:  # digit < D
            xx = left * pow
        #if debug: print(xx)
        count += xx

        pow *= 10  # Move to next digit position
    
    return count
    
#
# getdignum will find the NEXT integer satisfying
# f(n, d) = n  (NOTE: f is count_digit_occurences)
# getdignum will use a binary search, where assume G(n, d) = f(n, d) - n = do_delta(n, d)
# We start with the input n, knowing G(n, d) - n < 0
def getdignum(n, digit):
    maxn = digit * (10 ** 10)
    dn = 1
    done = False
    # print("Dignum, n is: ", n, "  digit is: ", digit)
    while not done:
        v = count_digit_occurrences(n, digit) - n
        nn = n + dn # next n
        if nn > maxn: return False, -1
        vnn = count_digit_occurrences(nn, digit) - nn
        # check if we are on a fixed point
        if dn == 1 and vnn == 0:
            #print(n, nn, vnn)
            return True, nn
        
        if v > 1:
            #print("What", n, v, nn, vnn)
            # double dn - found a sign change
            n = n + v - 1   # move n to near fixed point, shrink delta n (dn) for finer search
            dn = 1
        #
        # if n is greater that nn's count, need to increase search area
        elif dn == 1 or count_digit_occurrences(nn, digit) < n:
            n = nn
            dn *= 2
            #print("*2 dn : ", dn)
        #
        # otherwise, we overshot, and need to shrink search width
        else:
            dn //= 2
            #print("/2 dn : ", dn)

sumdigs = 0   
for digit in range(1, 10):
    ds = 0
    if digit == 1: ds = 1 # account for f(1,1)=1
    n = 2
    tf = True
    while tf:
    #for _ in range(5):
        tf, v = getdignum(n, digit)
        if tf:
            #print("Result: ", v)
            ds += v
            n = v
    print("Digit: ", digit, " sum is: ", ds)
    sumdigs += ds
print("Total sum: ", sumdigs)
