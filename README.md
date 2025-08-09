编译结构体生成文件
gcc position_final.c -o position_final -lm

运行文件
./position_final

编译main函数
gcc main.c event.c trajectory_data.c missile_control.c generateData.c -o missile_simulator -lm