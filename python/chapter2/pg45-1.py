import sys
def equal_float(a,b):
    return abs(a-b)<=sys.float_info.epsilon
s=equal_float(1.2,1.3)
print(s)
