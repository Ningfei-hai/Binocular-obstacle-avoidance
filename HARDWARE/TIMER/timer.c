#include "timer.h"
#include "led.h"

#if SYSTEM_SUPPORT_OS
	#include "FreeRTOS.h"					//FreeRTOSʹ��
	#include "task.h"
#endif

extern int updata_flag;

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM1_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  						//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  				
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 						//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  														//��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx					 
}

//��ʱ��3�жϷ�����
//extern TaskHandle_t TSendMsg_toBBB_Task_Handler;
void TIM1_UP_IRQHandler(void)
{
	
//	BaseType_t xHigherPriorityTaskWoken;
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET) //����ж�
	{
//		LED0=~LED0;
		updata_flag = 1;
//		if(TSendMsg_toBBB_Task_Handler!=NULL)
//		{
//			vTaskNotifyGiveFromISR(TSendMsg_toBBB_Task_Handler,&xHigherPriorityTaskWoken);
//			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//		}	
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //����жϱ�־λ
}










