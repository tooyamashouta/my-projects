import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm

# 読み込んだファイルの文字列を１行ずつlineに代入
file = open("1-1.txt", "r")
for line in file:
    data_str = file.read().strip()
    data_list = data_str.split()

# 文字列から数値に変換し、NumPyのarrayに変換
data_array = np.array([float(item) for item in data_list])

# 361つごとに異なる行にreshape
rows, cols = divmod(len(data_array), 361)
reshaped_array = data_array[:rows*361].reshape((rows, 361))
#print('reshaped_array')
#print(reshaped_array)

#91~180を消す
half_array = np.delete(reshaped_array, np.s_[:90], axis=0)

# 各行の1つ目の要素を消す（2列目以降を抽出）
modified_array = half_array[:, 1:]
#print('modified_array')
#print(modified_array)

# データを最大値で規格化
modified_array = modified_array / np.max(modified_array)

# 各列を逆の順番にする
reversed_columns_array = modified_array[::-1, :]
#print('reversed_columns_array')
#print(reversed_columns_array)

# データを極座標に変換
theta = np.linspace(0, 2*np.pi,reversed_columns_array.shape[1], endpoint=False)
r = np.arange(reversed_columns_array.shape[0])

# メッシュグリッドを作成
theta, r = np.meshgrid(theta, r)

# ヒートマップを描画 (対数スケール)
fig, ax = plt.subplots(subplot_kw=dict(projection='polar'))
c = ax.pcolormesh(theta, r, reversed_columns_array, cmap='viridis', shading='auto', norm=LogNorm())

# カラーバーを追加
plt.colorbar(c, ax=ax, label='Values (log scale)')

# グラフの向きを変更
ax.set_theta_offset(np.pi/2)  # グラフの開始位置を90度に設定
ax.set_theta_direction(-1)    # グラフの回転方向を時計回りに設定

# 角度の軸に目盛りと線を設定
ax.set_xticks(np.linspace(0, 2*np.pi, 12, endpoint=False))
ax.set_xticklabels(['0', '30', '60', '90', '120', '150', '180', '210', '240', '270', '300', '330'])

#線を引く
ax.grid(True)

ax.set_title('Normalized Heatmap')

plt.show()
