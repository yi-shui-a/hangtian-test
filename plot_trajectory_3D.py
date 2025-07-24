import re
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


plt.rcParams["font.family"] = ["WenQuanYi Micro Hei", "sans-serif"]
plt.rcParams["axes.unicode_minus"] = False  # Fix minus sign display


# 读取C数据文件
with open('python_test.c', 'r') as f:
    content = f.read()

# 提取结构体数据
pattern = re.compile(r'\{([^}]+)\}')
matches = pattern.findall(content)

longitudes = []
latitudes = []
altitudes = []
velocityX = []  # 添加速度数组
velocityY = []
velocityZ = []

time_values = []
for match in matches:
    parts = [p.strip() for p in match.split(',')]
    if len(parts) >= 11:  # 确保有足够的字段
        try:
            # 提取时间、经度、纬度、高度（索引0,2,3,4）
            time_ms = float(parts[0])
            lon = float(parts[2])
            lat = float(parts[3])
            alt = float(parts[4])
            
            # 提取速度分量（索引8,9,10）
            vx = float(parts[8])
            vy = float(parts[9])
            vz = float(parts[10])
            
            time_values.append(time_ms)
            longitudes.append(lon)
            latitudes.append(lat)
            altitudes.append(alt)
            velocityX.append(vx)  # 存储速度数据
            velocityY.append(vy)
            velocityZ.append(vz)
        except ValueError:
            continue

# 创建3D轨迹图
fig = plt.figure(figsize=(15, 12))
ax = fig.add_subplot(111, projection='3d')

# 绘制轨迹线（使用时间作为颜色映射）
sc = ax.scatter(longitudes, latitudes, altitudes, c=time_values, cmap='viridis', s=15, alpha=0.6)
line, = ax.plot(longitudes, latitudes, altitudes, 'b-', linewidth=1.5, alpha=0.8)

# 添加方向向量（每10个点添加一个速度方向箭头）
vec_interval = 10
for i in range(0, len(longitudes), vec_interval):
    # 计算方向向量长度（速度大小）
    speed = (velocityX[i]**2 + velocityY[i]**2 + velocityZ[i]**2)**0.5
    scale = 0.001  # 缩放因子
    ax.quiver(longitudes[i], latitudes[i], altitudes[i],
              velocityX[i]*scale, velocityY[i]*scale, velocityZ[i]*scale,
              color='red', length=0.01, normalize=True)

# 标记关键事件点
event_points = [5, 15, 25, 60, 120, 180, 250, 300, 350, 380, 390]  # 事件时间点（秒）
event_indices = [int(t*1000/500) for t in event_points if t*1000/500 < len(longitudes)]
event_colors = ['green', 'yellow', 'cyan', 'magenta', 'orange', 'purple', 'brown', 'pink', 'gray', 'olive', 'teal']
for idx, color in zip(event_indices, event_colors):
    ax.scatter(longitudes[idx], latitudes[idx], altitudes[idx], c=color, s=100, edgecolors='black', linewidths=1.5)

# 设置坐标轴标签和标题
ax.set_xlabel('经度 (度)', fontsize=12, labelpad=15)
ax.set_ylabel('纬度 (度)', fontsize=12, labelpad=15)
ax.set_zlabel('高度 (米)', fontsize=12, labelpad=15)
ax.set_title('导弹三维运动轨迹与方向可视化', fontsize=15, pad=20)

# 设置初始视角（仰角30度，方位角45度）
ax.view_init(elev=30, azim=45)

# 添加颜色条和图例
cbar = fig.colorbar(sc, ax=ax, pad=0.1)
cbar.set_label('时间 (毫秒)', rotation=270, labelpad=20)
ax.legend(['轨迹线', '位置点'], loc='upper right')

# 添加网格和坐标轴刻度优化
ax.grid(True, linestyle='--', alpha=0.7)
ax.tick_params(axis='both', which='major', labelsize=10)

# 标记起点和终点
ax.scatter(longitudes[0], latitudes[0], altitudes[0], c='green', s=100, label='发射点')
ax.scatter(longitudes[-1], latitudes[-1], altitudes[-1], c='red', s=100, label='目标点')

# 设置坐标轴标签和标题
ax.set_xlabel('经度 (度)', fontsize=12)
ax.set_ylabel('纬度 (度)', fontsize=12)
ax.set_zlabel('高度 (米)', fontsize=12)
ax.set_title('导弹运动轨迹三维可视化', fontsize=15)
ax.legend()

# 添加时间颜色条
sm = plt.cm.ScalarMappable(cmap='viridis', norm=plt.Normalize(min(time_values), max(time_values)))
sm.set_array([])
fig.colorbar(sm, ax=ax, label='时间 (毫秒)')

plt.tight_layout()
plt.show()

# 绘制高度随时间变化曲线
plt.figure(figsize=(10, 4))
plt.plot([t/1000 for t in time_values], altitudes)
plt.xlabel('时间 (秒)')
plt.ylabel('高度 (米)')
plt.title('导弹高度变化曲线')
plt.grid(True)
plt.tight_layout()
plt.show()

# 保存图片
plt.savefig('trajectory3D.png')