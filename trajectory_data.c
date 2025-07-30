#include "trajectory_data.h"
#include "generateData.h"

uint32_t index = 0;

uint8_t current_step_num = 0;

void trajectory_array_ptr(TrajectoryData *trajectory_ptr)
{

	return;
}

uint32_t getCurrentTime(uint32_t tick_counter)
{

	return tick_counter;
}

uint8_t getCurrentStep(uint32_t tick_counter)
{

	if (tick_counter > 0 && tick_counter < STEPA)
	{

		current_step_num = 1;
		return current_step_num;
	}
	else if ((tick_counter > STEPA) && (tick_counter < STEPB))
	{
		current_step_num = 2;
		return current_step_num;
	}

	else if ((tick_counter > STEPB) && (tick_counter < STEPC))
	{
		current_step_num = 3;
		return current_step_num;
	}

	else
		return 0xe2;
}