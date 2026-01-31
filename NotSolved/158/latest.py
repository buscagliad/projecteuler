#!/usr/bin/env python3
#
#  latest.py
#  
#  Copyright 2025 Dave Buscaglia <dave@MintOS>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  


import sys
from collections import namedtuple

LR = namedtuple('Row', ['left', 'right', 'count'])




def split(A, L, left):
    l = [0]*27
    for a in range(1, 27):
        if left:
            ll = 1
            ul = a - L
        else:
            ll = a + L
            ul = 27
        for i in range(ll, ul):
            l[i] += A[a]
    print("split, sum: ", sum(l))

def dothree():
    l1 = [0]*27
    r1 = [0]*27
    l2 = [0]*27
    r2 = [0]*27

    for c in range(1, 27):
        for a in range(1, 27):
            for b in range(1, 27):
                    # continue if any two are equal
                    if a == b or a == c or b == c : continue
                    # slot B is big element
                    # a < B > c 
                    if a < b and b > c :
                        l1[a] += 1
                        r1[c] += 1
     
                    # slot C is big element
                    # a > b < C 
                    elif a > b and b < c :
                        l2[a] += 1
                        r2[c] += 1
                    
    print(sum(l1), l1)
    print(sum(r1), r1)
    print(sum(l2), l2)
    print(sum(r2), r2)


    split(l1, 4, True)
    split(r1, 4, False)
    split(l2, 4, True)
    split(r2, 4, False)
    return 0

def main(args):
    dothree()


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
