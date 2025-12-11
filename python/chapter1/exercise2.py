list=[]
count=sum=0
lowest=highest=None
while True:
    try:
        res=input("enter a number or Enter to finish: ")
        if not res:
            break
        else:
            res=int(res)
            if lowest is None or res<lowest:
                lowest=res
            if highest is None or res>highest:
                highest=res
            list.append(res)
            sum+=res
            count+=1
    except ValueError as err:
        print(err)
print("numbers: ",list)
print("count =",count,"sum =",sum,"lowest =",lowest,"highest =",highest,"mean =",sum/count)
