
#include "event.h"
#include "missile_control.h"

static uint32_t index = 0;
static uint32_t current_step = 0;

void init_trajectory_stepA(uint32_t current){
	insert_node(current + SXGB_DELTA, SXGB, 1);
	insert_node(current + TLJCYQRXH_DELTA, TLJCYQRXH, 1); 
	insert_node(current + FSTFLXH_DELTA, FSTFLXH, 1);
	insert_node(current + YJFDJGBZLXH_DELTA, YJFDJGBZLXH, 1);
	insert_node(current + YJFLJGJSXH_DELTA, YJFLJGJSXH, 1);
	insert_node(current + EJFDJDHXH_DELTA, EJFDJDHXH, 1);
	insert_node(current + ZLZFLXH_DELTA, ZLZFLXH, 1);
	insert_node(current + MZTJGBZLXH_DELTA, MZTJGBZLXH, 1);
}

void init_trajectory_stepB(uint32_t current){
	insert_node(current + GXZDXZXH_DELTA, GXZDXZXH, 1);
	insert_node(current + XGZDJZXH_DELTA, XGZDJZXH, 1); 
	insert_node(current + DTMCJSXH_DELTA, DTMCJSXH, 1);
	insert_node(current + YESFXH_DELTA, YESFXH, 1);
}

void init_trajectory_stepC(uint32_t current){
	insert_node(current + ZRZTTZXH_DELTA, ZRZTTZXH, 1);
	insert_node(current + MDZDXZXH_DELTA, MDZDXZXH, 1); 
	insert_node(current + YXBXJSXH_DELTA, YXBXJSXH, 1);
	insert_node(current + YBZLXH_DELTA, YBZLXH, 1);
}

uint16_t update_missile_position(uint32_t current_time){

	uint8_t step = getCurrentStep(current_time, index); 

    // printf("Current time: %ums, Step: %d \n", current_time, step);

	if(step == 0xe2){
		return 0x00e2; // return CurrentStep error code
	}

	if (step == 0XAC){
		// printf("Current Step is 0xAC, Start.\n"); //点火
		return 0x00AC; // Action code
	}
	
	if(current_step != step){
		current_step = step;
		if (step == 1){
			init_trajectory_stepA(current_time);
		}
		else if (step == 2){
			init_trajectory_stepB(current_time);
		}
		else if (step == 3){
			init_trajectory_stepC(current_time);
		}
	}
	// printf("Current Step is  0x%04x \n",step);

	uint16_t ret_command_code = get_current_node(current_time);
	index++;	
	// printf("Current index is %d \n", index);
  	return  ret_command_code;
}
