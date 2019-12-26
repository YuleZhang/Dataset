def numGameResult():
    m = 0
    i = 0
    n = input("请输入小朋友的个数n：")
    data=list(range(1, (int(n)+1)))
    while(len(data)):
        m = data[0]
        del(data[0])

        i = i+1
        if(i % 3 != 0):
            data.append(m)
    print("第{0}个小朋友获胜".format(m))
if __name__ == '__main__':
    numGameResult()
