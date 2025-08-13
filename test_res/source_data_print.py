import re

# 1. 读取 C 数组文件
with open("test_res/trajectory_data.txt", "r") as f:
    c_array = f.read()

# 2. 使用正则表达式提取数据
pattern = r"\{(\d+),\s*([\d.]+),\s*([\d.]+),\s*([\d.]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+),\s*([\d.-]+)\}"
matches = re.findall(pattern, c_array)

# 3. 转换为字典列表
trajectory_data = []
for match in matches:
    data = {
        "time": int(match[0]),
        "longitude": float(match[1]),
        "latitude": float(match[2]),
        "altitude": float(match[3]),
        "accelerationX": float(match[4]),
        "accelerationY": float(match[5]),
        "accelerationZ": float(match[6]),
        "velocityX": float(match[7]),
        "velocityY": float(match[8]),
        "velocityZ": float(match[9]),
        "yawAngle": float(match[10]),
        "pitchAngle": float(match[11]),
        "rollAngle": float(match[12]),
        "yawRate": float(match[13]),
        "pitchRate": float(match[14]),
        "rollRate": float(match[15]),
        "yawAcceleration": float(match[16]),
        "pitchAcceleration": float(match[17]),
        "rollAcceleration": float(match[18])
    }
    trajectory_data.append(data)

# 4. 输出（可选）
print(trajectory_data)  # 打印前两条检查