#!/usr/bin/env python3
import sys
import unicodedata
def print_unicode_table(words):
    print("decimal  hex chr {0:^40}".format("name"))
    print("-------  ----- --- {0:-<40}".format(""))
    code=ord(" ")
    end=sys.maxunicode
    while code<end:
        flag=True
        c=chr(code)
        name=unicodedata.name(c,"***unknown***")
        for word in words:
            if word not in name.lower():
                flag=False
                break
        if flag:
            print("{0:7}   {0:5X}  {0:^3c}  {1}".format(code,name.title()))
        code+=1
words=[]
if len(sys.argv)>1:
    if "-h" in sys.argv or "--help" in sys.argv:
        print("usage:{0} [parameters...]".format(sys.argv[0]))
        exit(0)
    else:
        for cell in sys.argv[1:]:
            words.append(cell.lower())
print_unicode_table(words)
