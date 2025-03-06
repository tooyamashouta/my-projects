def input_year_month():
    year = int(input('西暦年を入力し、Enterキーを押してください: '))
    while True:
        month = int(input('月を入力し、Enterキーを押してください: '))        
        if 1 <= month <= 12:
            break
        print('1から12までの整数を入力してください。')
    return (year, month)

def is_leap_year(year):
    import math
    if year % 400 == 0 or year % 4 == 0 and year % 100 != 0:
        return True 
    else:
        return False

def get_days_of_month(year, month):
    if month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12:
        days_of_month = 31
    elif month == 4 or month == 6 or month == 9 or month == 11:
        days_of_month = 30
    else:
        if is_leap_year(year):
            days_of_month = 29
        else:
            days_of_month = 28
    return days_of_month

def zeller(year, month, day):
    if month >= 3:
        pass
    else:
        month = month + 12
        year = year - 1

    youbi = (year + year//4 - year//100 + year//400 + (13*month + 8)//5 + day) % 7
    return youbi

def print_cal(year, month, days_of_month, first_day): 
    print() #空行
    print(f'     {year:>4}年{month:>2}月') # 右寄せ4桁と2桁 
    print('\033[31m''日''\033[0m'' 月 火 水 木 金 ''\033[34m''土''\033[0m') #挟んでるのは色付けエスケープシークエンス
    print(' ' * 3 * first_day, end='')
    for day in range(1, days_of_month + 1 ): 
        print(f'{day:>2} ', end='') 
        if (day + first_day) % 7 == 0 or day == days_of_month:
            print('')

    print()
    print('本月の国民の祝日は')
    if month == 1:
        print('''1日の元旦と
第2月曜日の成人の日です。''')
    elif month == 2:
        print('''11日の建国記念日と
23日の天皇誕生日です。''')
    elif month == 3:
        print('春分の日です。詳しい日にちは国立天文台ホームページへ')
    elif month == 4:
        print('''29日の昭和の日です。''')
    elif month == 5:
        print('''3日の憲法記念日と
4日のみどりの日と
5日のこどもの日です。''')
    elif month == 6:
        print('残念ながらありません。')
    elif month == 7:
        print('第3月曜日の海の日です。')
    elif month == 8:
        print('11日の山の日です。')
    elif month == 9:
        print('''第3月曜日の敬老の日と
秋分の日です。秋分の日の詳しい日にちは国立天文台ホームページへ''')
    elif month == 10:
        print('第2月曜日のスポーツの日です。')
    elif month == 11:
        print('''3日の文化の日と
23日の勤労感謝の日です。''')
    elif month == 12:
        print('ないけど冬休みあるからいいか。')
    print()

(year, month) = input_year_month()
days_of_month = get_days_of_month(year, month)
first_day = zeller(year, month, 1)
print_cal(year, month, days_of_month, first_day)
