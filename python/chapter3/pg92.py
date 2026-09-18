#!/usr/bin/env python3
first,*rest=[9,2,-4,8,7]
print("first={} rest={}".format(first,rest))
first,*mid,last="Charles Philip Arthur George Windsor".split()
print("first={} mid={} last={}".format(first,mid,last))
*directories,executable="/usr/local/bin/gvim".split("/")
print("directories={} executable={}".format(directories,executable))
