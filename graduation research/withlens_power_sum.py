import numpy as np
import matplotlib.pyplot as plt
from scipy.io import loadmat
from matplotlib.colors import LogNorm

# 読み込んだファイルの文字列を１行ずつlineに代入
file1 = open("データファイル名.txt", "r")
for line in file1:
    data_str = file1.read().strip()
    data_list = data_str.split()

# 文字列から数値に変換し、NumPyのarrayに変換
data_array = np.array([float(item) for item in data_list])

# 361つごとに異なる行にreshape（メッシュの細かさにより修正が必要）
rows, cols = divmod(len(data_array), 361)
reshaped_array = data_array[:rows*361].reshape((rows, 361))

#91~180を消す（メッシュの細かさにより修正が必要）
half_array = np.delete(reshaped_array, np.s_[:90], axis=0)
#print('かけられる数')
#print(half_array)

# 各行の1つ目の要素を消す（2列目以降を抽出）
modified_array = half_array[:, 1:]


#lenzprofileをロード
lenz_array = np.loadtxt('output_data44.txt') #145用
#lenz_array = np.loadtxt('output_data55.txt') #220用

# 1つごとに異なる行にreshape
rows, cols = divmod(len(lenz_array), 1)
reshaped_lenz_array = lenz_array[:rows*1].reshape((rows, 1))

# 一番上の行を削除
lenz90_array = np.delete(reshaped_lenz_array, 0, axis=0)
#print('かける数')
#print(lenz90_array)

# np.ndarray1の各行にnp.ndarray2の対応する行の要素を掛ける
result_array = np.multiply(modified_array, lenz90_array)
#print('結果')
#print(result_array)

'''
# ヒートマップを描画
fig, ax = plt.subplots()
c = ax.imshow(result_array, cmap='viridis', aspect='auto', norm=LogNorm())

# カラーバーを対数スケールに設定
cbar = plt.colorbar(c, ax=ax, label='Values (log scale)')
cbar.set_label('Values (log scale)')
plt.xlabel('X Axis')
plt.ylabel('Y Axis')
plt.title('Heatmap from Text File')
plt.show()
'''

# 全ての要素を足す
sum_of_elements = np.sum(result_array)

#全光線本数で割る
power = sum_of_elements/(1.0*10**9)

# 結果を表示
print(power)
