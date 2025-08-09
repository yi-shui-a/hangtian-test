
#include "event.h"
#include "missile_control.h"

uint32_t current_step = 0;

void init_trajectory_stepA(uint32_t current)
{
	insert_node(current + SXGB_DELTA, SXGB, 1);
	insert_node(current + TLJCYQRXH_DELTA, TLJCYQRXH, 1);
	insert_node(current + FSTFLXH_DELTA, FSTFLXH, 1);
}

void init_trajectory_stepB(uint32_t current)
{
	insert_node(current + YJFDJGBZLXH_DELTA, YJFDJGBZLXH, 1);
	insert_node(current + YJFLJGJSXH_DELTA, YJFLJGJSXH, 1);
	insert_node(current + EJFDJDHXH_DELTA, EJFDJDHXH, 1);
	insert_node(current + ZLZFLXH_DELTA, ZLZFLXH, 1);
	insert_node(current + MZTJGBZLXH_DELTA, MZTJGBZLXH, 1);
}

void init_trajectory_stepC(uint32_t current)
{
	int GXZDXZXH_time = current;
	int XGZDJZXH_time = current;
	for (int i = current; i < 378000; i += 1000)
	{
		if ((GXZDXZXH_time - current) % GXZDXZXH_DELTA == 0 && (GXZDXZXH_time - current) != 0)
		{
			insert_node(GXZDXZXH_time, GXZDXZXH, 1);
			printf("GXZDXZXH_time: %d\n", GXZDXZXH_time);
		}
		if ((XGZDJZXH_time - current) % XGZDJZXH_DELTA == 0 && (XGZDJZXH_time - current) != 0)
		{
			insert_node(XGZDJZXH_time, XGZDJZXH, 1);
		}
		if (i == current + DTMCJSXH_DELTA)
		{
			insert_node(current + DTMCJSXH_DELTA, DTMCJSXH, 1);
		}
		if (i > current + DTMCJSXH_DELTA && (i - (current + DTMCJSXH_DELTA)) % YESFXH_DELTA == 0)
		{
			insert_node(current + YESFXH_DELTA, YESFXH, 1);
		}
		GXZDXZXH_time += 1000;
		XGZDJZXH_time += 1000;
	}
}

void init_trajectory_stepD(uint32_t current)
{
	insert_node(current + ZRZTTZXH_DELTA, ZRZTTZXH, 1);
	insert_node(current + MDZDXZXH_DELTA, MDZDXZXH, 1);
	insert_node(current + YXBXJSXH_DELTA, YXBXJSXH, 1);
	insert_node(current + YBZLXH_DELTA, YBZLXH, 1);
}

uint16_t update_missile_position(uint32_t current_time)
{

	uint8_t step = getCurrentStep(current_time);

	if (step == 0xe2)
	{
		return 0x00e2; // return CurrentStep error code
	}

	if (current_step != step)
	{
		current_step = step;
		if (step == 1)
		{
			init_discrete_points();
			init_trajectory_stepA(current_time);
		}
		else if (step == 2)
		{
			init_trajectory_stepB(current_time);
		}
		else if (step == 3)
		{
			init_trajectory_stepC(current_time);
		}
		else if (step == 4)
		{
			init_trajectory_stepD(current_time);
		}
	}
	uint16_t ret_command_code = get_current_node(current_time, current_step);

	return ret_command_code;
}
