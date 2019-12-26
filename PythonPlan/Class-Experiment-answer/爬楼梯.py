def getStep(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    elif n == 2:
        return 2
    elif n == 3:
        return 4
    return getStep(n-1)+getStep(n-2)+getStep(n-3)
    #第n层的走法为其相邻前三层走法之和，1 2 4 7...规律
if __name__ == '__main__':
    print(getStep(15))
