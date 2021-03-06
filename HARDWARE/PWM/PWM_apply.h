#ifndef __PWM_APPLY_H
#define __PWM_APPLY_H
#include "sys.h"
//#include "timer_apply.h"

///*****************************************///
//���ڵ�BUG����ѡ��ĳ����ʱ���Ķ�ͨ��ӳ��ʱ�������������˲��ε���������������ӳ��Ļ���������ʹ��
///*****************************************///
typedef struct PWMInit
{
	u8 timerX;    					//ѡ��ͬ�Ķ�ʱ��
	u8 channel[4];					//��ʱ��ͨ��1-4
	u8 remap[4];						//��ʱ��ͨ��ӳ�� 4�����͵�
	float duty[4];							//PWM��ռ|�ձ� ��/��
	u16 reload;							//�Զ���װ��ֵ
	u16 syspcs;							//ʱ�ӷ�Ƶ
	uint16_t mode;					//ģʽ
	uint16_t divtim;				//��ʱ����Ƶ
	uint16_t oc_mode;				//PWM�ļ���ģʽ
	uint16_t oc_Polarity;		//PWM����
	FunctionalState isEnable;	//��ʱ��ʹ��
	
}Obj_PWMInit;

#define PWM_AFIO  1
#define PWM_NAFIO 0

//-----������ӳ��-----
#define GPIO_noRemap    1
#define GPIO_partRemap1 2
#define GPIO_partRemap2 3
#define GPIO_fullRemap  4
//-----����PWMģʽ-----
#define OCMode_PWM1              ((uint16_t)0x0060)
#define OCMode_PWM2              ((uint16_t)0x0070)
//-----����PWM���������-----
#define OCPolarity_High          ((uint16_t)0x0000)
#define OCPolarity_Low           ((uint16_t)0x0002)
//-----����PWM��ͨ��------
#define PWM_Channel1 1
#define PWM_Channel2 2
#define PWM_Channel3 3
#define PWM_Channel4 4
//-----���嶨ʱͨ���Ŀ���-----
#define Channel_Open  1
#define Channel_Close 0


void TIMX_PWM_Init(Obj_PWMInit *pwm);  	//��ʼ����ʱ��X
void TIM1_PWM_Init(Obj_PWMInit *pwm);		//��ʼ����ʱ��1
void TIM2_PWM_Init(Obj_PWMInit *pwm);		//��ʼ����ʱ��2
void TIM3_PWM_Init(Obj_PWMInit *pwm);		//��ʼ����ʱ��3
void TIM4_PWM_Init(Obj_PWMInit *pwm);		//��ʼ����ʱ��4
void TIM5_PWM_Init(Obj_PWMInit *pwm);		//��ʼ����ʱ��5
void Set_TIMX_PWMState(Obj_PWMInit *pwm);  //�ö���Ľṹ���ʼ������PWM����
void Choose_TIM1_PWMChannel(u8 channel,u8 remap); //ѡ��PWM��ͨ��
void Choose_TIM2_PWMChannel(u8 channel,u8 remap);
void Choose_TIM3_PWMChannel(u8 channel,u8 remap);
void Choose_TIM4_PWMChannel(u8 channel,u8 remap);
void Choose_TIM5_PWMChannel(u8 channel,u8 remap);
void Change_PWMState(Obj_PWMInit *pwm, u8 channel[],u8 remap[],u32 freqent,float duty[]); //�޸�PWMͨ��
void Set_PWMFreqent(Obj_PWMInit *pwm, u32 freqent);  //����PWMƵ��
void Set_PWMFreqentandDuty(Obj_PWMInit *pwm, u8 channel,u32 freqent,float duty);
#endif
