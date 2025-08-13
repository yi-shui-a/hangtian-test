#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "event.h"
#include "missile_control.h"

// 事件名称映射表
const char* get_event_name(uint16_t event_code) {
    static const char* event_names[] = {
        "FLYING",
        "TLJCYQRXH", "FSTFLXH", 
        "YJFDJGBZLXH","YJFLJGJSXH","EJFDJDHXH","ZLZFLXH","MZTJGBZLXH",
        "GXZDXZXH","XGZDJZXH","DTMCJSXH","YESFXH",
        "ZRZTTZXH","MDZDXZXH","YXBXJSXH","YBZLXH"
    };
    
    if (event_code < sizeof(event_names)/sizeof(event_names[0])) {
        return event_names[event_code];
    }
    return "UNKNOWN";
}

int main() {
    // 初始化参数
    uint32_t start_time_ms = 0;        // 起始时间(毫秒)
    uint32_t time_step_ms = 100;      // 时间步长(毫秒)
    uint32_t end_time_ms = 400000;     // 结束时间(毫秒)
    uint32_t current_time_ms = start_time_ms;
    
    // 初始化系统
    // init_event_system();
    // init_trajectory_data();
    
    printf("导弹控制系统启动...\n");
    printf("起始时间: %ums, 结束时间: %ums, 步长: %ums\n", 
           start_time_ms, end_time_ms, time_step_ms);
    
    // 主循环
    while (current_time_ms <= end_time_ms) {
        // 获取当前事件
        uint16_t event = update_missile_position(current_time_ms);
        
        // 打印事件信息
        if (event != 0x00e2 && event != 0x0000) {  // 过滤错误码
            printf("[%6ums] 事件: %s (0x%04x)\n", 
                   current_time_ms, get_event_name(event), event);
        }
        
        // 更新当前时间
        current_time_ms += time_step_ms;
        
        // 模拟时间延迟
        // struct timespec ts = {
        //     .tv_sec = time_step_ms / 1000,
        //     .tv_nsec = (time_step_ms % 1000) * 1000000
        // };
        // nanosleep(&ts, NULL);
    }
    
    printf("导弹控制系统运行结束\n");
    return 0;
}
