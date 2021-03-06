#include "timer.h"
#include "led.h"

#if SYSTEM_SUPPORT_OS
	#include "FreeRTOS.h"					//FreeRTOS使用
	#include "task.h"
#endif

extern int updata_flag;

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM1_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  						//TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  				
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 						//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  														//初始化NVIC寄存器

	TIM_Cmd(TIM1, ENABLE);  //使能TIMx					 
}

//定时器3中断服务函数
//extern TaskHandle_t TSendMsg_toBBB_Task_Handler;
void TIM1_UP_IRQHandler(void)
{
	
//	BaseType_t xHigherPriorityTaskWoken;
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET) //溢出中断
	{
//		LED0=~LED0;
		updata_flag = 1;
//		if(TSendMsg_toBBB_Task_Handler!=NULL)
//		{
//			vTaskNotifyGiveFromISR(TSendMsg_toBBB_Task_Handler,&xHigherPriorityTaskWoken);
//			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//		}	
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //清除中断标志位
}










