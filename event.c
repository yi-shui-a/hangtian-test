
#include "event.h"

Event discrete_points[150]; /* 130 个事件 */

uint8_t array_index = 0;

uint8_t array_current = 0;

void insert_node(uint32_t time, uint16_t event, uint8_t isNull)
{
    discrete_points[array_index].time = time;
    discrete_points[array_index].event = event;
    discrete_points[array_index].isNull = isNull;
    array_index++;
}

void init_discrete_points()
{
    for(int i=0;i<150;i++){
        discrete_points[i].time = 0;
        discrete_points[i].event = SXGB;
        discrete_points[i].isNull = 0;
    }
}


// 判断当前飞行状态是否符合事件需求
int check(float trend, uint32_t alt_samples[], uint32_t current_step, uint16_t current_event)
{
    // 上升阶段判断
    if (current_step == 1)
    {
        // 一级点火阶段要求高度持续上升
        if (trend < 50)
        {
            return 0;
        }

        // 检查高度波动是否过大
        float variance = 0;
        for (int i = 0; i < 4; i++)
        {
            variance += fabs(alt_samples[i + 1] - alt_samples[i] - trend);
        }
        if (variance > 100)
        {
            return 0;
        }

        // 检查当前高度是否符合阶段预期
        if (alt_samples[2] < 10000 && trend < 80)
        {
            return 0;
        }
        else if (alt_samples[2] >= 10000 && trend < 30)
        {
            return 0;
        }

        // 点火发射阶段特殊事件检查
        if (current_event == TLJCYQRXH)
        {
            if (trend < 60)
                return 0;
        }
        else if (current_event == FSTFLXH)
        {
            if (alt_samples[2] < 1000)
                return 0;
        }

        // 助推段特殊事件检查
        if (current_event == YJFDJGBZLXH)
        {
            if (alt_samples[2] < 30000)
                return 0;
        }
        else if (current_event == YJFLJGJSXH)
        {
            if (alt_samples[2] < 35000)
                return 0;
        }
        else if (current_event == EJFDJDHXH)
        {
            if (alt_samples[2] < 40000)
                return 0;
        }
        else if (current_event == ZLZFLXH)
        {
            if (alt_samples[2] < 50000)
                return 0;
        }
        else if (current_event == MZTJGBZLXH)
        {
            if (alt_samples[2] < 70000)
                return 0;
        }

        return 0;
    }
    // 巡航阶段判断（中段）
    else if (current_step == 2)
    {
        // 巡航阶段要求高度相对稳定
        if (fabs(trend) > 20)
        {
            return 0;
        }

        // 检查高度波动模式
        int peak_count = 0;
        for (int i = 1; i < 4; i++)
        {
            if ((alt_samples[i] > alt_samples[i - 1] &&
                 alt_samples[i] > alt_samples[i + 1]) ||
                (alt_samples[i] < alt_samples[i - 1] &&
                 alt_samples[i] < alt_samples[i + 1]))
            {
                peak_count++;
            }
        }
        if (peak_count > 2)
        {
            return 0;
        }

        // 中段特殊事件检查
        if (current_event == GXZDXZXH)
        {
            if (fabs(trend) > 10)
                return 0;
        }
        else if (current_event == XGZDJZXH)
        {
            if (alt_samples[2] < 80000 || alt_samples[2] > 100000)
                return 0;
        }
        else if (current_event == DTMCJSXH)
        {
            if (alt_samples[2] < 90000)
                return 0;
        }
        else if (current_event == YESFXH)
        {
            if (alt_samples[2] < 95000)
                return 0;
        }

        return 0;
    }
    // 末端阶段判断
    else if (current_step == 3)
    {
        // 末端制导阶段要求高度持续下降
        if (trend > -30)
        {
            return 0;
        }

        // 检查下降加速度
        float accel = (alt_samples[4] - 2 * alt_samples[2] + alt_samples[0]) / 4.0;
        if (accel > 10)
        {
            return 0;
        }

        // 末段特殊事件检查
        if (current_event == ZRZTTZXH)
        {
            if (trend > -40)
                return 0;
        }
        else if (current_event == MDZDXZXH)
        {
            if (alt_samples[2] > 20000)
                return 0;
        }
        else if (current_event == YXBXJSXH)
        {
            if (alt_samples[2] > 5000)
                return 0;
        }
        else if (current_event == YBZLXH)
        {
            if (alt_samples[2] > 1000)
                return 0;
        }

        return 0;
    }

    return 0;
}

uint16_t get_current_node(uint32_t current_time, uint32_t current_step)
{

    uint16_t current_event = 0;
    static uint32_t last_altitude = 0;

    // 获取当前dd数据
    TrajectoryData current_data = getTrajectoryData(current_time);
    uint32_t current_altitude = current_data.altitude;

    // 获取前后5个点的高度数据用于趋势判断
    uint32_t alt_samples[5]; // 前后4个点加当前点
    for (int i = -2; i <= 2; i++)
    {
        uint32_t sample_time = current_time + i * 1000; // 假设时间间隔为1000ms
        TrajectoryData sample = getTrajectoryDataWithIndex(i);
        alt_samples[i + 2] = sample.altitude;
    }

    // 计算高度变化趋势
    float trend = 0;
    for (int i = 0; i < 10; i++)
    {
        trend += (alt_samples[i + 1] - alt_samples[i]);
    }
    trend /= 10; // 平均变化率

    if (current_time >= discrete_points[array_current].time)
    {
        // 时间条件满足且高度变化趋势符合要求
        if (discrete_points[array_current].isNull > 0 || check(trend, alt_samples, current_step, discrete_points[array_current].event))
        {
            if (discrete_points[array_current + 1].time - current_time || discrete_points[array_current].time - current_time)
            {
                printf("array_current: %d\n", array_current);
                current_event = discrete_points[array_current].event;
                discrete_points[array_current].isNull--;
            }
        }
        discrete_points[array_current].isNull = 0;
    }

    if (discrete_points[array_current].isNull == 0)
    {
        if (array_current == 0)
        {
            array_current++;
        }
        else
        {
            if (discrete_points[array_current].event != SXGB)
            {
                array_current++;
            }
        }

        // printf("array_current: %d\n", array_current);
    }
    return current_event;
}
