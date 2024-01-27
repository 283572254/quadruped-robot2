#include "pwm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
/* USER CODE BEGIN PV */
uint8_t move_mode = 0;
uint8_t flag = 0;
#define move_delay 150 //һ�㶯������
#define move_speed 4 //���ٶ�������
extern char RxBuffer[RXBUFFERSIZE];   //��������
enum e_instruction {sway = 65,stretch_wave,sleep,up,left,stand,right,down};
extern uint8_t g_instruction;
extern SemaphoreHandle_t g_xConSemaphore; 
uint16_t angle(uint8_t angle) //�Ƕ�CCRֵת��
{
	return angle*2000/180+500;
}
 
void Rbt_Init(void) //����
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	vTaskDelay(100);
}
 
void move_forward(void) //ǰ��
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(45));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(135));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
 
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(45));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(135));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	vTaskDelay(move_delay);
}
 
void move_behind(void) //����
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(135));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(45));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
 
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(135));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(45));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	vTaskDelay(move_delay);
}
 
void move_right(void) //��ת
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(45));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(135));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	vTaskDelay(move_delay);
}
 
void move_left(void) //��ת
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(135));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(135));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(45));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(45));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	vTaskDelay(move_delay);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	vTaskDelay(move_delay);
}
 
void move_swing(void) //ҡ��
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(130));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(130));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(50));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(50));
	vTaskDelay(250);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(50));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(50));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(130));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(130));
	vTaskDelay(250);
}
 
void move_stretch(void){ //������+��������
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90));
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90));
	if(TIM2->CCR1<angle(155) && TIM2->CCR3>angle(25)){
		for(uint8_t i=0;i<70;i++){       //ѭ���㷨�����Լ��������ת�ٶ�
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90+i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90-i));
			vTaskDelay(move_speed);
		}
		vTaskDelay(1000);
		for(uint8_t i=0;i<70;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(160-i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(20+i));
			vTaskDelay(move_speed);
		}
		for(uint8_t i=0;i<65;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90+i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90-i));
			vTaskDelay(move_speed);
		}
		for(uint8_t i=0;i<20;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90-i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90+i));
			vTaskDelay(move_speed);
		}
		vTaskDelay(1000);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(140));
		vTaskDelay(1000);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(178));
		vTaskDelay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(140));
		vTaskDelay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(178));
		vTaskDelay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(140));
		vTaskDelay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(70));
	}
}
 
void move_sleep(void){ //˯��
	if(TIM2->CCR3<angle(160) && TIM2->CCR1>angle(20)){
		for(uint8_t i=0;i<75;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,angle(90-i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,angle(90+i));
			vTaskDelay(move_speed);
		}
	}
	if(TIM2->CCR2<angle(160) && TIM2->CCR4>angle(20)){
		for(uint8_t i=0;i<75;i++){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,angle(90+i));
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,angle(90-i));
			vTaskDelay(move_speed);
		}
	}
 
}




void pwm_contral(void)
{
	
	while (1)
	{
		/*��ȡ�ź���*/
		xSemaphoreTake(g_xConSemaphore,portMAX_DELAY);
		/* code */
		switch (g_instruction)
		{
			case sway:			
				move_swing();
				break;
			case stretch_wave:
				move_stretch();
				break;
			case sleep:
				move_sleep();
				break;
			case up:
				move_forward();
				break;
			case left:
				move_left();
				break;	
			case stand:
				Rbt_Init();
				break;
			case right:
				move_right();
				break;
			case down:
				move_behind();
				break;				
			default:
				break;
		}
		/*�ͷ��ź���*/
		xSemaphoreGive(g_xConSemaphore);
		vTaskDelay(10);
	}
	
	
}



