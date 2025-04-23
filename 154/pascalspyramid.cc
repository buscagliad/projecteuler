
#include <stdio.h>

const int N = 200000;
int PTEN = 12;

int fact5s[N+1];
int sfact5s[N+1];
int fact2s[N+1];
int sfact2s[N+1];

void init()
{
    for (int i = 1; i <= N; i++)
    {
        int f = i;
        int count = 0;
        while (f % 5 == 0)
        {
            count ++;
            f /= 5;
        }
        fact5s[i] = count;
        count = 0;
        while (f % 2 == 0)
        {
            count ++;
            f /= 2;
        }

        fact2s[i] = count;
    }

    sfact5s[1] = fact5s[1];
    sfact2s[1] = fact2s[1];
    for (int i = 1; i <= N; i++)
    {
        sfact2s[i] = sfact2s[i-1] + fact2s[i];
        sfact5s[i] = sfact5s[i-1] + fact5s[i];
    }
    printf("%d!  has %d factors of 2, and %d factors of 5\n", 
        N, sfact2s[N], sfact5s[N]);
}




/*
#print(sfacts)

# (x + y + z)^n = SUM[n!/(m! * l! * (n-m-l)!) * x^m * y^m * z ^(n-m-l)] from 0 to n
# the coefficient n!/(m! * l! * (n-m-l)!) is divisible by 10^R whenenver
# the coeeficient has at least R factors of 2 and 5 (each)
# Since 2 and 5 are relatively prime, we need to just see how many
# factors of 2 and 5 exist in n!, m!, l! and (n-m-l)! 
# sfact2s[k] and sfact5s[k] will provide the number of factors or 2 and 5
# respectively for k!
#
# c2 = sfact2s[n] - sfact2s[m] - sfact2s[k] - sfact2s[l]
# c5 = sfact5s[n] - sfact5s[m] - sfact5s[k] - sfact5s[l]
# provides the number of factors of 2 and 5 in each coefficient
# if c2 and c5 are both >= R, then the coefficient is divisible by 10^R
#
*/
int main()
{
    init();
    int total = 0;
    int combos = 0;
    int n5 = sfact5s[N];
    int n2 = sfact2s[N];
    int early = 0;
    for (int m = 0; m <= N; m++)
    {
        if (m % 200 == 0)
            printf("Percent complete: %.1f %%\r", (double)m*100.0/(double)N);
        int perm = 0;
        int cn5 = n5 - sfact5s[m];
        int cn2 = n2 - sfact2s[m];
        if ( (cn2 < PTEN) || (cn5 < PTEN) ) 
        { 
            combos += 1;
            early += 1;
            continue;
        }
        for (int l = 1; l <= N - m; l++)
        {
            int k = N - l - m;
            combos += 1;
            // print(m, l, k, m+l+k)
            // 
            //  there should be some logic that will let us skip over
            //  coefficients once 12 is reached 
            //  is there symmetry at play??
            // 
            int c5 = cn5 - sfact5s[k] - sfact5s[l];
            int c2 = cn2 - sfact2s[k] - sfact2s[l];
            if ( (c2 < PTEN) || (c5 < PTEN) )
            {
                // print(c5, c2, m, l, k)
                continue;
            }
            else
            { 
                // if ss > 1: print(m, l, ss)
                perm += 1;
                total += 1;
            }
        }
    }
    printf("\n");
    printf("Total: %d\n", total);
    // ;
    //  Answer is 479742450
    //  200000!  has 199994 factors of 2, and 49998 factors of 5
    //  Percent complete: 100.0 %
    //  Total: 479742450
    //  
    //  real	0m33.196s
    //  user	0m33.069s
    //  sys	0m0.060s
    //  

    // 
}
