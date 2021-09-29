num = input().replace('-','').replace('(','').replace(')','').replace('+','')
if len(num) == 11:
    num  = num[1:]
else:
    num = '495' + num


for i in range(3):
    num_ = input().replace('-','').replace('(','').replace(')','').replace('+','')
    if len(num_) == 11:
        num_ = num_[1:]
    else:
        num_ = '495' + num_

    if num == num_:
        print('YES')
    else:
        print('NO')