#ifndef __PWM_APPLY_H
#define __PWM_APPLY_H
#include "sys.h"
//#include "timer_apply.h"

///*****************************************///
//存在的BUG：在选择某个定时器的多通道映射时，会出现输出不了波形的情况，但是如果不映射的话，都可以使用
///*****************************************///
typedef struct PWMInit
{
	u8 timerX;    					//选择不同的定时器
	u8 channel[4];					//定时器通道1-4
	u8 remap[4];						//定时器通道映射 4种类型的
	float duty[4];							//PWM的占|空比 高/低
	u16 reload;							//自动重装载值
	u16 syspcs;							//时钟分频
	uint16_t mode;					//模式
	uint16_t divtim;				//定时器分频
	uint16_t oc_mode;				//PWM的计数模式
	uint16_t oc_Polarity;		//PWM极性
	FunctionalState isEnable;	//定时器使能
	
}Obj_PWMInit;

#define PWM_AFIO  1
#define PWM_NAFIO 0

//-----定义重映射-----
#define GPIO_noRemap    1
#define GPIO_partRemap1 2
#define GPIO_partRemap2 3
#define GPIO_fullRemap  4
//-----定义PWM模式-----
#define OCMode_PWM1              ((uint16_t)0x0060)
#define OCMode_PWM2              ((uint16_t)0x0070)
//-----定义PWM的输出极性-----
#define OCPolarity_High          ((uint16_t)0x0000)
#define OCPolarity_Low           ((uint16_t)0x0002)
//-----定义PWM的通道------
#define PWM_Channel1 1
#define PWM_Channel2 2
#define PWM_Channel3 3
#define PWM_Channel4 4
//-----定义定时通道的开关-----
#define Channel_Open  1
#define Channel_Close 0


void TIMX_PWM_Init(Obj_PWMInit *pwm);  	//初始化定时器X
void TIM1_PWM_Init(Obj_PWMInit *pwm);		//初始化定时器1
void TIM2_PWM_Init(Obj_PWMInit *pwm);		//初始化定时器2
void TIM3_PWM_Init(Obj_PWMInit *pwm);		//初始化定时器3
void TIM4_PWM_Init(Obj_PWMInit *pwm);		//初始化定时器4
void TIM5_PWM_Init(Obj_PWMInit *pwm);		//初始化定时器5
void Set_TIMX_PWMState(Obj_PWMInit *pwm);  //用定义的结构体初始化设置PWM波形
void Choose_TIM1_PWMChannel(u8 channel,u8 remap); //选择PWM的通道
void Choose_TIM2_PWMChannel(u8 channel,u8 remap);
void Choose_TIM3_PWMChannel(u8 channel,u8 remap);
void Choose_TIM4_PWMChannel(u8 channel,u8 remap);
void Choose_TIM5_PWMChannel(u8 channel,u8 remap);
void Change_PWMState(Obj_PWMInit *pwm, u8 channel[],u8 remap[],u32 freqent,float duty[]); //修改PWM通道
void Set_PWMFreqent(Obj_PWMInit *pwm, u32 freqent);  //设置PWM频率
void Set_PWMFreqentandDuty(Obj_PWMInit *pwm, u8 channel,u32 freqent,float duty);
#endif
