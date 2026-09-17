#!/usr/bin/env python3
import collections
Sale=collections.namedtuple("Sale","productid customerid date quantity price")
sales=[]
sales.append(Sale(432,921,"2008-09-14",3,7.99))
sales.append(Sale(419,874,"2008-09-15",1,18.49))
total=0
for sale in sales:
    total+=sale.quantity*sale.price
print("Total ${0:.2f}".format(total))
