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
flag=0
while flag==0:
    index=0
    flag=1
    while index<len(list)-1:
        if list[index]>list[index+1]:
            trans=list[index+1]
            list[index+1]=list[index]
            list[index]=trans
            flag=0
        index+=1
if len(list)%2==0:
    median=(list[len(list)//2-1]+list[len(list)//2])/2
else:
    median=list[len(list)//2]
print("numbers: ",list)
print("count =",count,"sum =",sum,"lowest =",lowest,"highest =",highest,"mean =",sum/count,"median = ",median)
