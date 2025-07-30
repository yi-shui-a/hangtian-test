
#include "event.h"
#include "missile_control.h"

uint32_t current_step = 0;

void init_trajectory_stepA(uint32_t current)
{
	insert_node(current + SXGB_DELTA, SXGB, 1);
	insert_node(current + YJDH_DELTA, YJDH, 1);
	insert_node(current + YJFL_DELTA, YJFL, 1);
	insert_node(current + EJDH_DELTA, EJDH, 1);
	insert_node(current + EJFL_DELTA, EJFL, 1);
}

void init_trajectory_stepB(uint32_t current)
{
	insert_node(current + DYZK_DELTA, DYZK, 1);
	insert_node(current + FDGR_DELTA, FDGR, 1);
	insert_node(current + ZDJD_DELTA, ZDJD, 1);
}

void init_trajectory_stepC(uint32_t current)
{
	insert_node(current + DTFL_DELTA, DTFL, 1);
	insert_node(current + LDZD_DELTA, LDZD, 1);
	insert_node(current + HWZD_DELTA, HWZD, 1);
	insert_node(current + MBFP_DELTA, MBFP, 1);
	insert_node(current + DJJD_DELTA, DJJD, 1);
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
	}
	uint16_t ret_command_code = get_current_node(current_time, current_step);

	return ret_command_code;
}
