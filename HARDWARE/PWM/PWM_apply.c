#include "PWM_apply.h"

void TIMX_PWM_Init(Obj_PWMInit *pwm)
{
	switch(pwm->timerX)
	{
		case 1: TIM1_PWM_Init(pwm);break;
		case 2: TIM2_PWM_Init(pwm);break;
		case 3: TIM3_PWM_Init(pwm);break;
		case 4: TIM4_PWM_Init(pwm);break;
		case 5: TIM5_PWM_Init(pwm);break;
		default: break;
	}
}
//-----��ʱ��1��ʼ��-----
void TIM1_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	 //ʹ�ܶ�ʱ��1ʱ��
	//----ѡ��ͨ��GPIO��ͨ����ӳ��-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM1_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCNPolarity = pwm->oc_Polarity; //�������:TIM����Ƚϼ��Ը�
	//TIM_OCInitStructure.TIM_Pulse=10;
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset;
	//-----ѡ��PWM�����ͨ��------
	
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			switch(i+1)
			{
				case 1:
					TIM_OC1Init(TIM1, &TIM_OCInitStructure);  
					TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  
					break;
				case 2:
					TIM_OC2Init(TIM1, &TIM_OCInitStructure);  
					TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  
					break;
				case 3:
					TIM_OC3Init(TIM1, &TIM_OCInitStructure);  
					TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  
					break;
				case 4:
					TIM_OC4Init(TIM1, &TIM_OCInitStructure);  
					TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  
					break;
			}
		}
		else;
	}

	TIM_Cmd(TIM1, pwm->isEnable);  //ʹ��TIM1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

//-----��ʱ��2��ʼ��-----
void TIM2_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 //ʹ�ܶ�ʱ��3ʱ��
	//----ѡ��ͨ��GPIO��ͨ����ӳ��-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM2_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = pwm->oc_Polarity; //�������:TIM����Ƚϼ��Ը�
	//-----ѡ��PWM�����ͨ��------
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			switch(i+1)
			{
				case 1:
					TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
					TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  
					break;
				case 2:
					TIM_OC2Init(TIM2, &TIM_OCInitStructure);  
					TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  
					break;
				case 3:
					TIM_OC3Init(TIM2, &TIM_OCInitStructure);  
					TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  
					break;
				case 4:
					TIM_OC4Init(TIM2, &TIM_OCInitStructure);  
					TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  
					break;
			}
		}
		else;
	}
	TIM_Cmd(TIM2, pwm->isEnable);  //ʹ��TIM3
}

//-----��ʱ��3��ʼ��-----
void TIM3_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 //ʹ�ܶ�ʱ��3ʱ��
	//----ѡ��ͨ��GPIO��ͨ����ӳ��-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM3_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = pwm->oc_Polarity; //�������:TIM����Ƚϼ��Ը�
	//-----ѡ��PWM�����ͨ��------
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			switch(i+1)
			{
				case 1:
					TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
					TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  
					break;
				case 2:
					TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
					TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
					break;
				case 3:
					TIM_OC3Init(TIM3, &TIM_OCInitStructure);  
					TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
					break;
				case 4:
					TIM_OC4Init(TIM3, &TIM_OCInitStructure);  
					TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  
					break;
			}
		}
		else;
	}
	TIM_Cmd(TIM3, pwm->isEnable);  //ʹ��TIM3
}

//-----��ʱ��4��ʼ��-----
void TIM4_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //ʹ�ܶ�ʱ��3ʱ��
	//----ѡ��ͨ��GPIO��ͨ����ӳ��-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM4_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = pwm->oc_Polarity; //�������:TIM����Ƚϼ��Ը�
	//-----ѡ��PWM�����ͨ��------
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			switch(i+1)
			{
				case 1:
					TIM_OC1Init(TIM4, &TIM_OCInitStructure);  
					TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  
					break;
				case 2:
					TIM_OC2Init(TIM4, &TIM_OCInitStructure);  
					TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  
					break;
				case 3:
					TIM_OC3Init(TIM4, &TIM_OCInitStructure);  
					TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  
					break;
				case 4:
					TIM_OC4Init(TIM4, &TIM_OCInitStructure);  
					TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  
					break;
			}
		}
		else;
	}
	TIM_Cmd(TIM4, pwm->isEnable);  //ʹ��TIM3
}
//-----��ʱ��5��ʼ��-----
void TIM5_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	 //ʹ�ܶ�ʱ��3ʱ��
	//----ѡ��ͨ��GPIO��ͨ����ӳ��-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM5_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = pwm->oc_Polarity; //�������:TIM����Ƚϼ��Ը�
	//-----ѡ��PWM�����ͨ��------
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			switch(i+1)
			{
				case 1:
					TIM_OC1Init(TIM5, &TIM_OCInitStructure);  
					TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  
					break;
				case 2:
					TIM_OC2Init(TIM5, &TIM_OCInitStructure);  
					TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  
					break;
				case 3:
					TIM_OC3Init(TIM5, &TIM_OCInitStructure);  
					TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  
					break;
				case 4:
					TIM_OC4Init(TIM5, &TIM_OCInitStructure);  
					TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  
					break;
			}
		}
		else;
	}
	TIM_Cmd(TIM5, pwm->isEnable);  //ʹ��TIM3
}
//-----����PWM�����״̬-----
void Set_TIMX_PWMState(Obj_PWMInit *pwm)  //ռ�ձ�ʹ�ðٷ��� duty:0-100
{
	u8 i=0;
	pwm->reload++;
	switch(pwm->timerX)
	{
		case 1: //��ʱ��1
		for(i=0;i<4;i++)
		{
			if(pwm->channel[i]==1)
			{
				switch(i+1)
				{
					case 1://��ʱ��1ͨ��1
						TIM_SetCompare1(TIM1,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;	
					case 2://��ʱ��1ͨ��2
						TIM_SetCompare2(TIM1,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://��ʱ��1ͨ��3
						TIM_SetCompare3(TIM1,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://��ʱ��1ͨ��4
						TIM_SetCompare4(TIM1,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					default: break;
				} 
			}
			else;
		}break;
		case 2:
		for(i=0;i<4;i++)
		{
			if(pwm->channel[i]==1)
			{
				switch(i+1)
				{
					case 1://��ʱ��2ͨ��1
						TIM_SetCompare1(TIM2,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 2://��ʱ��2ͨ��2
						TIM_SetCompare2(TIM2,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://��ʱ��2ͨ��3
						TIM_SetCompare3(TIM2,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://��ʱ��2ͨ��4
						TIM_SetCompare4(TIM2,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					default: break;
				} 
			}
			else;
		} break;
		case 3:
		for(i=0;i<4;i++)
		{
			if(pwm->channel[i]==1)
			{
				switch(i+1)
				{
					case 1://��ʱ��3ͨ��1
						TIM_SetCompare1(TIM3,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 2://��ʱ��3ͨ��2
						TIM_SetCompare2(TIM3,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://��ʱ��3ͨ��3
						TIM_SetCompare3(TIM3,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://��ʱ��3ͨ��4
						TIM_SetCompare4(TIM3,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					default: break;
				} 
			}
			else;
		}break;
		case 4:
		for(i=0;i<4;i++)
		{
			if(pwm->channel[i]==1)
			{
				switch(i+1)
				{
					case 1://��ʱ��4ͨ��1
						TIM_SetCompare1(TIM4,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 2://��ʱ��4ͨ��2
						TIM_SetCompare2(TIM4,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://��ʱ��4ͨ��3
						TIM_SetCompare3(TIM4,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://��ʱ��4ͨ��4
						TIM_SetCompare4(TIM4,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					default: break;
				} 
			}
			else;
		}break;
		case 5:
		for(i=0;i<4;i++)
		{
			if(pwm->channel[i]==1)
			{
				switch(i+1)
				{
					case 1://��ʱ��5ͨ��1
						TIM_SetCompare1(TIM5,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 2://��ʱ��5ͨ��2
						TIM_SetCompare2(TIM5,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://��ʱ��5ͨ��3
						TIM_SetCompare3(TIM5,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://��ʱ��5ͨ��4
						TIM_SetCompare4(TIM5,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					default: break;
				} 
			}
			else;
		}break;
		default: break;
	}
}

//-----�޸Ľṹ���Ա���޸�PWM�Ĳ���-----
void Change_PWMState(Obj_PWMInit *pwm, u8 channel[],u8 remap[],u32 freqent,float duty[])
{
	u8 i=0;
	for(i=0;i<4;i++)
	{
		pwm->channel[i]=channel[i];
		pwm->remap[i] = remap[i];
		pwm->duty [i] = duty[i];
	}
	pwm->syspcs=0;
	pwm->reload=72000000/freqent;
	TIMX_PWM_Init(pwm);
}

//-----����PWM��Ƶ��-----
void Set_PWMFreqent(Obj_PWMInit *pwm, u32 freqent)
{
	pwm->syspcs=0;
	pwm->reload=72000000/freqent;
	TIMX_PWM_Init(pwm);
}

//-----����PWM��Ƶ�ʺ�ռ�ձ�-----
void Set_PWMFreqentandDuty(Obj_PWMInit *pwm, u8 channel,u32 freqent,float duty)
{
	pwm->syspcs=99;
	pwm->reload=720000/freqent;
	pwm->channel[channel-1]=Channel_Open;
	pwm->duty[channel-1]=duty;
	TIMX_PWM_Init(pwm);
}


//-----------------------------------------------------------
//-----------------------------------------------------------
void Choose_TIM1_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//
						break;
					case 3:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  			//Timer2������ӳ�� 
						//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			default: break;
		}
}

//-----ѡ��PWM�����GPIO��ӳ�����-------
void Choose_TIM2_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//
						break;
					case 3:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2������ӳ�� 
						//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2������ӳ��
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��					
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);  			//Timer2������ӳ��
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��					
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2������ӳ��
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��					
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			default: break;
		}
}

//-----ѡ��PWM�����GPIO��ӳ�����-------
void Choose_TIM3_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//
						break;
					case 3:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);  			//Timer2������ӳ��
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��					
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 3:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:  //��ȫ��ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					default: break;
				}
				break;
			default: break;
		}
}

//-----ѡ��PWM�����GPIO��ӳ�����-------
void Choose_TIM4_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &GPIO_InitStructure);//
						break;
					case 2:   //������ӳ��
						
						break;
					case 3:   //��ȫ��ӳ��
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:  //������ӳ��
						break;
					case 3:  //��ȫ��ӳ��
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:  //������ӳ��
						break;
					case 3:  //��ȫ��ӳ��
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 4:   //������ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //ʹ��GPIO����
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //ʹ�ܸ��ù���
						GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //Timer2������ӳ�� 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //��ֹJTAG��������Ϊ��ͨIO�ڣ�û����������޷���ȷӳ��
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:  //��ȫ��ӳ��
						break;
					case 3:  //��ȫ��ӳ��
						break;
					default: break;
				}
				break;
			default: break;
		}
}
//-----ѡ��PWM�����GPIO��ӳ�����-------
void Choose_TIM5_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						break;
					case 3:   //������ӳ��
						break;
					case 4:  //��ȫ��ӳ��
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						break;
					case 3:  //��ȫ��ӳ��
						break;
					case 4:  //��ȫ��ӳ��
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						break;
					case 3:  //��ȫ��ӳ��
						break;
					case 4:  //��ȫ��ӳ��
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //û����ӳ��
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
						break;
					case 2:   //������ӳ��
						break;
					case 3:  //��ȫ��ӳ��
						break;
					case 4:  //��ȫ��ӳ��
						break;
					default: break;
				}
				break;
			default: break;
		}
}


