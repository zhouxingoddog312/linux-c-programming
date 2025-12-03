print("Type integers, each followed by Enter; or ^D or ^Z to fininsh")
total=0
count=0
while True:
    try:
        line=input()
        if line:
            try:
                number=int(line)
            except ValueError as err:
                print(err)
                continue
            total+=number
            count+=1
    except EOFError:
        break
if count:
    print("count = ",count,"total = ",total,"mean = ",total/count)
