#!/usr/bin/env python3
numbers=[0,1,2,3,4]
for i in range(len(numbers)):
    numbers[i]+=1
print("numbers={}".format(numbers))
woods=["Cedar","Yew","Fir"]
print("woods+=['Kauri','Larch'] is {}".format(woods+["Kauri","Larch"]))
woods.extend(['Kauri','Larch'])
print("woods={}".format(woods))
woods=["Cedar","Yew","Fir","Spruce"]
woods[2:2]=["Pine"]
print(woods)
woods=["Cedar","Yew","Fir","Spruce"]
woods.insert(2,"Pine")
print(woods)
