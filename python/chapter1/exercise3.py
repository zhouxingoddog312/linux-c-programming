import random
article=["the","a"]
theme=["cat","dog","man","woman"]
verb=["sang","ran","jumped"]
adverbial=["loudly","quietly","well","badly"]
i=0
while i<5:
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
