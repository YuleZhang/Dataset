def getStudentInfo():
    get_str = ""
    student_name = [] #学生姓名
    student_sub = []  #学生科目
    student_grade = [] #学生成绩
    while get_str!='q':
        get_str = input("请输入姓名 科目 成绩，输入q结束：")
        if(get_str != 'q'):
            name = get_str.split()[0]
            subject = get_str.split()[1]
            grade = get_str.split()[2]
            student_name.append(name)
            student_sub.append(subject)
            student_grade.append(grade)
    student_info = {'姓名':student_name, '科目':student_sub, '成绩':student_grade}
    return student_info
def studentGrade(student_info):
    sub_credit = {'数学': 6, '英语': 3, 'python': 3, '大数据概论': 2} #课程学分
    stu_grade = {}
    length = len(student_info['姓名'])
    for i in student_info['姓名']:
        sum_grade = 0
        for j in range(0, length):
            if student_info['姓名'][j] == i:
                sum_grade += sub_credit[student_info['科目'][j]] * int(student_info['成绩'][j])
        stu_grade[i] = sum_grade
    return stu_grade
def averageGrade(stu_grade):
    sum_ = 0
    for i in stu_grade:
        sum_ += stu_grade[i]
    avg_grade = sum_ / len(stu_grade)
    return avg_grade
if __name__ == '__main__':
    std_info = {}
    std_grade = {}
    MAX_NAME = ''
    MIN_NAME = ''
    GPA_MAX = 0
    GPA_MIN = float("inf") #无穷大
    std_info = getStudentInfo()
    std_grade = studentGrade(std_info)
    print('班级平均学分绩{0}'.format(averageGrade(std_grade)))
    for i in std_grade:
        if std_grade[i] > GPA_MAX:
            MAX_NAME = i
            GPA_MAX = std_grade[i]
        elif std_grade[i] < GPA_MIN:
            MIN_NAME = i
            GPA_MIN = std_grade[i]
    print('第一名是{0}，其GPA为{1}'.format(MAX_NAME, GPA_MAX / 14))
    print('最后一名是{0}，其GPA为{1}'.format(MIN_NAME, GPA_MIN / 14))
