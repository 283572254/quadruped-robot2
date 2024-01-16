#include "pwm.h"

/* USER CODE BEGIN PV */
uint8_t move_mode = 0;
uint8_t flag = 0;
#define move_delay 150 //一般动作调速
#define move_speed 4 //慢速动作调速
uint16_t angle(uint8_t angle) //角度CCR值转换
{
	return angle*2000/180+500;
}
 
void Rbt_Init(void) //立正
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	HAL_Delay(100);
}
 
void move_forward(void) //前进
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(45));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(135));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
 
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(45));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(135));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	HAL_Delay(move_delay);
}
 
void move_behind(void) //后退
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(135));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(45));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
 
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(135));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(45));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	HAL_Delay(move_delay);
}
 
void move_right(void) //右转
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(45));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(135));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	HAL_Delay(move_delay);
}
 
void move_left(void) //左转
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(135));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(45));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	HAL_Delay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	HAL_Delay(move_delay);
}
 
void move_swing(void) //摇摆
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(130));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(130));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(50));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(50));
	HAL_Delay(250);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(50));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(50));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(130));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(130));
	HAL_Delay(250);
}
 
void move_stretch(void){ //伸懒腰+坐下招手
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	if(TIM2->CCR1<angle(155) && TIM2->CCR3>angle(25)){
		for(uint8_t i=0;i<70;i++){       //循环算法，可以减慢舵机运转速度
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90+i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90-i));
			HAL_Delay(move_speed);
		}
		HAL_Delay(1000);
		for(uint8_t i=0;i<70;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(160-i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(20+i));
			HAL_Delay(move_speed);
		}
		for(uint8_t i=0;i<65;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90+i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90-i));
			HAL_Delay(move_speed);
		}
		for(uint8_t i=0;i<20;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90-i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90+i));
			HAL_Delay(move_speed);
		}
		HAL_Delay(1000);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(140));
		HAL_Delay(1000);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(178));
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(140));
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(178));
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(140));
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(70));
	}
}
 
void move_sleep(void){ //睡眠
	if(TIM2->CCR3<angle(160) && TIM2->CCR1>angle(20)){
		for(uint8_t i=0;i<75;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90-i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90+i));
			HAL_Delay(move_speed);
		}
	}
	if(TIM2->CCR2<angle(160) && TIM2->CCR4>angle(20)){
		for(uint8_t i=0;i<75;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90+i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90-i));
			HAL_Delay(move_speed);
		}
	}
 
}








