import csv
import random

# 活性化関数
def act_func(data, weight, bias):
    sum = bias
    for (d, w) in zip(data, weight):
        sum += w * d
    if sum >= 0.0:
        return 1
    else:
        return 0

# 学習 (1回)
def training(training_data_set, teacher_set, weight, bias, eta):
    new_weight = []
    for w in weight:
        new_weight.append(w)
    new_bias = bias
    n_error = 0
    for (training_data, teacher) in zip(training_data_set, teacher_set):
        error = teacher - act_func(training_data, weight, bias)
        if error != 0:
            n_error += 1
            for num in range(len(training_data)):
                new_weight[num] += eta * error * training_data[num]
            new_bias += eta * error
    return (new_weight, new_bias, n_error)

# 学習 (繰り返し)
def iter_training(training_data_set, teacher_set, weight=None, bias=None, eta=0.01, n_iter=1000, stop=0):
    if weight == None:
        weight = []
        for num in training_data_set[0]:
            weight.append(random.uniform(-1.0, 1.0))
    if bias == None:
        bias = random.uniform(-1.0, 1.0)
    errors = []
    for num in range(n_iter):
        (weight, bias, n_error) = training(training_data_set, teacher_set, weight, bias, eta)
        errors.append(n_error)
        if n_error <= stop: # 間違ったサンプル数がstop以下となったら終了
            break
    return (weight, bias, errors, num + 1) 

training_data_set = []
teacher_set = []

with open('iris.csv') as csvfile:
    csvdata = csv.reader(csvfile)
    for line in csvdata:
        # 調べる品種を変更する場合はここで設定！
        # 品種を 'Iris-setosa' 'Iris-versicolor'
        #        'Iris-virginica' から選択
        if line[4] == 'Iris-virginica':       # ラベル「1」の品種
            teacher_set.append(1)
        elif line[4] == 'Iris-versicolor': # ラベル「0」の品種
            teacher_set.append(0)
        else:
            continue
        training_data_set.append( (float(line[0]), float(line[1]), float(line[2]), float(line[3])) )

# 学習率 eta 、最大繰り返し数 n_iter、繰り返しをやめる誤判定数 stopはパラメータとして与える
(weight, bias, errors, num)=iter_training(training_data_set, teacher_set, eta=0.000001, stop=0, n_iter=2000000)

print('Final weight =', weight)
print('Final bias =', bias)
print('Iteration =', num)
print()
input('Pease type enter key...')
print()
print('Error history =', errors)

print()
input('Pease type enter key...')
# 最終的な判定と教師データの比較
print()
print('teacher predict')
for (data, t) in zip(training_data_set, teacher_set):
    print(f'{t:>7} {act_func(data, weight, bias):>7}')
