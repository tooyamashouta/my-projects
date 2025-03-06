# 二次方程式の解を求め表示
import math # math モジュールを読み込む

print('二次方程式 a*x*x+b*x+c=0 を解きます。 ')
while True:
    try: # except else とセットで例外処理
        a = float(input('2次の係数aは？: '))
    except ValueError:
        print('半角整数で入力し直してください。')
    else:
        break
while True:
    try:
        b = float(input('1次の係数bは？: '))
    except ValueError:
        print('半角整数で入力し直してください。')
    else:
        break
while True:
    try:
        c = float(input('定数項cは？: '))
    except ValueError:
        print('半角整数で入力し直してください。')
    else:
        break

discriminant = b**2 - 4*a*c

if a != 0.0 and discriminant < 0.0:
    ans11 = -1*b/2/a
    dis = -1*discriminant
    ans12 = -1 * math.sqrt(dis)/2/a
    ans22 = math.sqrt(dis)/2/a
    if b == 0:
        print('解はiを虚数単位として ', ans12, 'i と ', ans22, 'i です。',sep='')
    else:
        print('解はiを虚数単位として ', ans11, ans12, 'i と ', ans11, '+', ans22, 'i です。',sep='')

elif a != 0.0 and discriminant >= 0.0:
    ans1 = (-b + math.sqrt(b**2 - 4*a*c))/2/a
    ans2 = (-b - math.sqrt(b**2 - 4*a*c))/2/a
    if ans1 == ans2:
        print('解は', ans1, 'です。')
    else:
        print('解は', ans1, 'と', ans2, 'です。')
elif a == 0.0 and b != 0.0:
    ans3 = -c/b
    print('解は', ans3, 'です。')
else:
    print('解は全ての実数。')
