print("Type integers, each followed by Enter; or just Enter to finish")
total=0
count=0
while True:
    line=input("integer: ")
    if line:
        try:
            number=int(line)
        except ValueError as err:
            print(err)
            continue
        count+=1
        total+=number
    else:
        break
if count:
    print("count=",count,"total=",total,"mean=",total/count)
