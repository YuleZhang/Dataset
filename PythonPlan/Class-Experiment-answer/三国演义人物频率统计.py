import jieba
def readPersonName():
    names = []
    try:
        with open("红楼梦人物列表.txt", encoding="UTF-8") as f :
            for name_line in f:
                if name_line != '\n':
                    for i in name_line.split('：')[1].split('、'):
                        names.append(i.strip())
    except FileNotFoundError:
        print("读取文件出错")
    names = list(set(names))
    return names
def readPersonNickName():
    nick_name = []
    try:
        with open("红楼梦人物别名.txt", encoding="UTF-8-sig") as f :
            for name_line in f:
                list_name = []
                if name_line != '\n':
                    for i in name_line.split(' '):
                        list_name.append(i.strip())
                    nick_name.append(list_name)
    except FileNotFoundError:
        print("读取文件出错")
    return nick_name
def getNameList():
    names = []
    nick_name = []
    names = readPersonName()
    nick_name = readPersonNickName()
    name_length = len(names)
    nick_length = len(nick_name)
    for i in range(name_length):
        for j in range(nick_length):
            if names[i] == nick_name[j][0]:
                names[i] = nick_name[j]
    return names
def getNameFreq(names):
    data = open("红楼梦.txt",encoding="UTF-8").read()
    words = jieba.lcut(data)
    name_dict = {}
    for word in words:
        for i in range(len(names)):
            if type(names[i]) == list:
                for j in range(len(names[i])):
                    if word == names[i][j]:
                        if names[i][0] in name_dict:
                            name_dict[names[i][0]] += 1
                        else:
                            name_dict[names[i][0]] = 1
            else:
                if word == names[i]:
                    if names[i] in name_dict:
                        name_dict[names[i]] += 1
                    else:
                        name_dict[names[i]] = 1
    return name_dict
def getTop10(name_dict):
    item=list(name_dict.items())
    item.sort(key=lambda x:x[1],reverse=True)
    for i in range(10):
        word,count=item[i]
        print("{0:<10}{1:>5}".format(word,count))
if __name__ == '__main__':
    names = []
    name_dict = []
    names = getNameList()
    name_dict = getNameFreq(names)
    getTop10(name_dict)
