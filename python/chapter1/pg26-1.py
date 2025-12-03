def get_int(msg):
    while True:
        try:
            line=int(input(msg))
            return line
        except ValueError as err:
            print(err)
age=get_int("enter your age:")
print(age)
