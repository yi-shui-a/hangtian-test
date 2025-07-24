import re
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


plt.rcParams["font.family"] = ["WenQuanYi Micro Hei", "sans-serif"]
plt.rcParams["axes.unicode_minus"] = False  # Fix minus sign display
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

time_values = []
for match in matches:
    parts = [p.strip() for p in match.split(',')]
    if len(parts) >= 5:
        try:
            # 提取时间、经度、纬度和高度
            time_ms = float(parts[0])
            lon = float(parts[2])
            lat = float(parts[3])
            alt = float(parts[4])
            
            time_values.append(time_ms)
            longitudes.append(lon)
            latitudes.append(lat)
            altitudes.append(alt)
        except ValueError:
            continue

# 创建3D轨迹图
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# 绘制轨迹线
ax.plot(longitudes, latitudes, altitudes, label='导弹轨迹', linewidth=2)

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
plt.savefig('trajectory.png')

# 读取C数据文件
with open('python_test.c', 'r') as f:
    content = f.read()

# 提取结构体数据
pattern = re.compile(r'\{([^}]+)\}')
matches = pattern.findall(content)

longitudes = []
latitudes = []
altitudes = []

time_values = []
for match in matches:
    parts = [p.strip() for p in match.split(',')]
    if len(parts) >= 5:
        try:
            # 提取时间、经度、纬度和高度
            time_ms = float(parts[0])
            lon = float(parts[2])
            lat = float(parts[3])
            alt = float(parts[4])
            
            time_values.append(time_ms)
            longitudes.append(lon)
            latitudes.append(lat)
            altitudes.append(alt)
        except ValueError:
            continue

# 创建3D轨迹图
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# 绘制轨迹线
ax.plot(longitudes, latitudes, altitudes, label='导弹轨迹', linewidth=2)

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
plt.savefig('trajectory.png')