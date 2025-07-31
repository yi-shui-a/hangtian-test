
#include "event.h"

static Event discrete_points[] = {
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0}}; /* 20 ��� */

static uint16_t array_index = 0;
static uint16_t array_current = 0;

void insert_node(uint32_t time, uint16_t event, uint8_t isNull)
{
	discrete_points[array_index].time = time;
	discrete_points[array_index].event = event;
	discrete_points[array_index].isNull = isNull;
	array_index++;
}

uint16_t get_current_node(uint32_t current_time)
{
	printf("array_index = %d\n", array_index);
	printf("array_current = %d\n", array_current);

	uint16_t current_event = 0;

	if ((current_time >= discrete_points[array_current].time) && (current_time < discrete_points[array_current + 1].time))
	{
		printf("(current_time >= discrete_points[array_current].time)---------------------------------------------- \n");

		if (discrete_points[array_current].isNull > 0){
			current_event = discrete_points[array_current].event;
			discrete_points[array_current].isNull--;
		}
		// discrete_points[array_current].isNull = 0;
	}
	if (discrete_points[array_current].isNull == 0)
	{
		array_current++;
	}
	return current_event;
}
