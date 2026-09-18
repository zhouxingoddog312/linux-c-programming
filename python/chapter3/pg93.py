#!/usr/bin/env python3
def product(a,b,c):
    return a*b*c
L=[2,3,5]
print(product(2,3,5))
print(product(*L))
print(product(2,*L[1:]))
