def test():
    n = 1
    c = 2
    tx = 3*n + 3*n + 3*n
    fx = n * c
    while tx > fx:
        tx = 3*n + 3*n + 3*n
        fx = (n**2)*c
        n+=1

    print("c=", c, "n=",n)



test()
