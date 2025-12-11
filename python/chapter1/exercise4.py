import random
import sys
article=["the","a"]
theme=["cat","dog","man","woman"]
verb=["sang","ran","jumped"]
adverbial=["loudly","quietly","well","badly"]
i=0
try:
    count=sys.argv[1]
    count=int(count)
except IndexError:
    pass
    count=5
except ValueError as err:
    print(err)
    count=5
if count<1 or count>10:
    count=5
while i<count:
    i+=1
    line=""
    line+=random.choice(article)+" "
    line+=random.choice(theme)+" "
    ii=random.randint(0,1)
    if ii:
        line+=random.choice(verb)+" "
        line+=random.choice(adverbial)
    else:
        line+=random.choice(verb)
    print(line)
