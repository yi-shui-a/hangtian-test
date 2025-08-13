import bisect
from trajectory_data import *

# 事件时间点（单位：ms）和对应的 event 宏定义
event_times = [
    (200, "TLJCYQRXH"),
    (400, "FSTFLXH"),
    (18400, "YJFDJGBZLXH"),
    (18600, "YJFLJGJSXH"),
    (18800, "EJFDJDHXH"),
    (38900, "ZLZFLXH"),
    (47900, "MZTJGBZLXH"),
    (50100, "GXZDXZXH"),
    (52100, "GXZDXZXH"),
    (54100, "GXZDXZXH"),
    (56100, "GXZDXZXH"),
    (58100, "GXZDXZXH"),
    (60100, "GXZDXZXH"),
    (62100, "GXZDXZXH"),
    (64100, "GXZDXZXH"),
    (66100, "GXZDXZXH"),
    (68100, "GXZDXZXH"),
    (70100, "GXZDXZXH"),
    (72100, "GXZDXZXH"),
    (74100, "GXZDXZXH"),
    (76100, "GXZDXZXH"),
    (78200, "XGZDJZXH"),
    (80100, "GXZDXZXH"),
    (82100, "GXZDXZXH"),
    (84100, "GXZDXZXH"),
    (86100, "GXZDXZXH"),
    (88100, "GXZDXZXH"),
    (90100, "GXZDXZXH"),
    (92100, "GXZDXZXH"),
    (94100, "GXZDXZXH"),
    (96100, "GXZDXZXH"),
    (98100, "GXZDXZXH"),
    (100100, "GXZDXZXH"),
    (102100, "GXZDXZXH"),
    (104100, "GXZDXZXH"),
    (106100, "GXZDXZXH"),
    (108200, "XGZDJZXH"),
    (110100, "GXZDXZXH"),
    (112100, "GXZDXZXH"),
    (114100, "GXZDXZXH"),
    (116100, "GXZDXZXH"),
    (118100, "GXZDXZXH"),
    (120100, "GXZDXZXH"),
    (122100, "GXZDXZXH"),
    (124100, "GXZDXZXH"),
    (126100, "GXZDXZXH"),
    (128100, "GXZDXZXH"),
    (130100, "GXZDXZXH"),
    (132100, "GXZDXZXH"),
    (134100, "GXZDXZXH"),
    (136100, "GXZDXZXH"),
    (138200, "XGZDJZXH"),
    (140100, "GXZDXZXH"),
    (142100, "GXZDXZXH"),
    (144100, "GXZDXZXH"),
    (146100, "GXZDXZXH"),
    (148100, "GXZDXZXH"),
    (150100, "GXZDXZXH"),
    (152100, "GXZDXZXH"),
    (154100, "GXZDXZXH"),
    (156100, "GXZDXZXH"),
    (158100, "GXZDXZXH"),
    (160100, "GXZDXZXH"),
    (162100, "GXZDXZXH"),
    (164100, "GXZDXZXH"),
    (166100, "GXZDXZXH"),
    (168200, "XGZDJZXH"),
    (170100, "GXZDXZXH"),
    (172100, "GXZDXZXH"),
    (174100, "GXZDXZXH"),
    (176100, "GXZDXZXH"),
    (178200, "DTMCJSXH"),
    (180100, "GXZDXZXH"),
    (180200, "YESFXH"),
    (182100, "GXZDXZXH"),
    (184100, "GXZDXZXH"),
    (184200, "YESFXH"),
    (186100, "GXZDXZXH"),
    (186200, "YESFXH"),
    (188100, "GXZDXZXH"),
    (190100, "GXZDXZXH"),
    (190200, "YESFXH"),
    (192100, "GXZDXZXH"),
    (192200, "YESFXH"),
    (194100, "GXZDXZXH"),
    (196100, "GXZDXZXH"),
    (196200, "YESFXH"),
    (198200, "XGZDJZXH"),
    (198300, "YESFXH"),
    (200100, "GXZDXZXH"),
    (202100, "GXZDXZXH"),
    (202200, "YESFXH"),
    (204100, "GXZDXZXH"),
    (204200, "YESFXH"),
    (206100, "GXZDXZXH"),
    (208100, "GXZDXZXH"),
    (208200, "YESFXH"),
    (210100, "GXZDXZXH"),
    (210200, "YESFXH"),
    (212100, "GXZDXZXH"),
    (214100, "GXZDXZXH"),
    (214200, "YESFXH"),
    (216100, "GXZDXZXH"),
    (216200, "YESFXH"),
    (218100, "GXZDXZXH"),
    (220100, "GXZDXZXH"),
    (220200, "YESFXH"),
    (222100, "GXZDXZXH"),
    (222200, "YESFXH"),
    (228100, "ZRZTTZXH"),
    (235100, "MDZDXZXH"),
    (237500, "YXBXJSXH"),
    (239400, "YBZLXH"),
]

# 从 trajectory_data 提取时间点（假设已加载）
traj_times = [point["time"] for point in trajectory_data]


def interpolate_data(time):
    """在 trajectory_data 中查找或插值获取数据"""
    idx = bisect.bisect_left(traj_times, time)
    if idx == 0:
        return trajectory_data[0]
    elif idx == len(traj_times):
        return trajectory_data[-1]
    else:
        # 线性插值
        t0, t1 = traj_times[idx - 1], traj_times[idx]
        p0, p1 = trajectory_data[idx - 1], trajectory_data[idx]
        alpha = (time - t0) / (t1 - t0)
        interpolated = {}
        for key in p0:
            if isinstance(p0[key], (int, float)):
                interpolated[key] = round(p0[key] + alpha * (p1[key] - p0[key]), 6)
            else:
                interpolated[key] = p0[key]
        return interpolated


# 生成 discrete_points 数组
discrete_points = []
for i in range(len(event_times)):
    time, event = event_times[i]
    data = interpolate_data(time)

    # 计算 duration_time
    if i < len(event_times) - 1:
        next_time = event_times[i + 1][0]
        time_diff = next_time - time
        duration_time = min(time_diff, 500)  # 如果时间差 <500，则 duration_time=时间差
    else:
        duration_time = 500  # 最后一个事件默认 500ms

    point = {
        "time": time,
        "event": event,
        "duration_time": duration_time,  # 动态计算
        "action_times": 1,
        "longitude": data["longitude"],
        "latitude": data["latitude"],
        "altitude": data["altitude"],
        "accelerationX": data["accelerationX"],
        "accelerationY": data["accelerationY"],
        "accelerationZ": data["accelerationZ"],
        "velocityX": data["velocityX"],
        "velocityY": data["velocityY"],
        "velocityZ": data["velocityZ"],
        "yawAngle": data["yawAngle"],
        "pitchAngle": data["pitchAngle"],
        "rollAngle": data["rollAngle"],
        "yawRate": data["yawRate"],
        "pitchRate": data["pitchRate"],
        "rollRate": data["rollRate"],
        "yawAcceleration": data["yawAcceleration"],
        "pitchAcceleration": data["pitchAcceleration"],
        "rollAcceleration": data["rollAcceleration"],
    }
    discrete_points.append(point)

# 输出 C 代码格式
print("DiscretePoint discrete_points[] = {")
for point in discrete_points:
    print(
        f"    {{{point['time']}, {point['event']}, {point['duration_time']}, 1, {point['longitude']}, {point['latitude']}, {point['altitude']}, {point['accelerationX']}, {point['accelerationY']}, {point['accelerationZ']}, {point['velocityX']}, {point['velocityY']}, {point['velocityZ']}, {point['yawAngle']}, {point['pitchAngle']}, {point['rollAngle']}, {point['yawRate']}, {point['pitchRate']}, {point['rollRate']}, {point['yawAcceleration']}, {point['pitchAcceleration']}, {point['rollAcceleration']}}},"
    )
print("};")
