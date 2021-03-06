#include "FishAgreement.h"
#include "table.h"
#include "string.h"
#include "stdio.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "ms5837.h"
#include "myiic.h"
#include "device.h"	
#include "usart3.h"
#include "adc.h"
#include "timer.h"

#include "control.h"
#include "timetask.h"

int updata_flag = 0;
extern __IO uint16_t ADC_ConvertedValue;

void OLED_Display(void)
{
		u8 display[30];
		fill_picture(0x00);

		sprintf((char *)display,"mE:%5.2lf",board_engines.mainEngine_left);
		OLED_ShowString(2,0, (u8 *)display,16);
		sprintf((char *)display,"pit:%5.2lf",board_engines.mainEngine_right);
		OLED_ShowString(2,2, (u8 *)display,16);
		sprintf((char *)display,"pE:%5.2lf V",board_sensors.btryVlot);
		OLED_ShowString(2,4, (u8 *)display,16);
		sprintf((char *)display,"Tem:%5.2lf m",board_sensors.waterDepth++); 
		OLED_ShowString(2,6, (u8 *)display,16);	
}

void B30Read(void)
{
		board_sensors.waterTemp = Calculate_MS5837Temperature();
		board_sensors.waterDepth = Calculate_Ms5837waterrPress();
		board_sensors.btryVlot = (float)ADC_ConvertedValue/4096*3.3*6.1;
}

void SendMsg(void)
{
		Obj_Fish agFish;
		agSelect.SensorMsg=board_sensors;
		agFish=Encode_FishAgreement(agSelect,SensorFlag);
		Usart3_sendFishAgreement(agFish);	
}
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main (void)
{	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		delay_init();	
		uart3_init(115200);
		IIC_Init_B30();
		MS5837_Init();
		ADC1_Init();
		TIM1_Int_Init(50-1,7200-1);
//		MainEngine_Init();
//		SteeringEngine_Init();
//		LED_Laser_Init();
		LED_Init();
		OLED_Init();
		
		while(1)
		{
				if(updata_flag)
				{
						B30Read();
						OLED_Display(); 
						SendMsg();
						updata_flag = 0;
				}
		}
}

/*********************************************END OF FILE**********************/












