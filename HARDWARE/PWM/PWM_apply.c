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
//-----定时器1初始化-----
void TIM1_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	 //使能定时器1时钟
	//----选择通道GPIO和通道的映射-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM1_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCNPolarity = pwm->oc_Polarity; //输出极性:TIM输出比较极性高
	//TIM_OCInitStructure.TIM_Pulse=10;
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset;
	//-----选择PWM的输出通道------
	
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

	TIM_Cmd(TIM1, pwm->isEnable);  //使能TIM1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

//-----定时器2初始化-----
void TIM2_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 //使能定时器3时钟
	//----选择通道GPIO和通道的映射-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM2_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = pwm->oc_Polarity; //输出极性:TIM输出比较极性高
	//-----选择PWM的输出通道------
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
	TIM_Cmd(TIM2, pwm->isEnable);  //使能TIM3
}

//-----定时器3初始化-----
void TIM3_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 //使能定时器3时钟
	//----选择通道GPIO和通道的映射-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM3_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = pwm->oc_Polarity; //输出极性:TIM输出比较极性高
	//-----选择PWM的输出通道------
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
	TIM_Cmd(TIM3, pwm->isEnable);  //使能TIM3
}

//-----定时器4初始化-----
void TIM4_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //使能定时器3时钟
	//----选择通道GPIO和通道的映射-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM4_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = pwm->oc_Polarity; //输出极性:TIM输出比较极性高
	//-----选择PWM的输出通道------
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
	TIM_Cmd(TIM4, pwm->isEnable);  //使能TIM3
}
//-----定时器5初始化-----
void TIM5_PWM_Init(Obj_PWMInit *pwm)
{  
	u8 i=0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	 //使能定时器3时钟
	//----选择通道GPIO和通道的映射-----
	for(i=0;i<4;i++)
	{
		if(pwm->channel[i]==1)
		{
			Choose_TIM5_PWMChannel(i+1,pwm->remap[i]);
		}
		else;
	}
   //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = pwm->reload; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =pwm->syspcs; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = pwm->divtim; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = pwm->mode;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = pwm->oc_mode; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = pwm->oc_Polarity; //输出极性:TIM输出比较极性高
	//-----选择PWM的输出通道------
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
	TIM_Cmd(TIM5, pwm->isEnable);  //使能TIM3
}
//-----设置PWM的输出状态-----
void Set_TIMX_PWMState(Obj_PWMInit *pwm)  //占空比使用百分制 duty:0-100
{
	u8 i=0;
	pwm->reload++;
	switch(pwm->timerX)
	{
		case 1: //定时器1
		for(i=0;i<4;i++)
		{
			if(pwm->channel[i]==1)
			{
				switch(i+1)
				{
					case 1://定时器1通道1
						TIM_SetCompare1(TIM1,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;	
					case 2://定时器1通道2
						TIM_SetCompare2(TIM1,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://定时器1通道3
						TIM_SetCompare3(TIM1,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://定时器1通道4
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
					case 1://定时器2通道1
						TIM_SetCompare1(TIM2,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 2://定时器2通道2
						TIM_SetCompare2(TIM2,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://定时器2通道3
						TIM_SetCompare3(TIM2,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://定时器2通道4
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
					case 1://定时器3通道1
						TIM_SetCompare1(TIM3,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 2://定时器3通道2
						TIM_SetCompare2(TIM3,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://定时器3通道3
						TIM_SetCompare3(TIM3,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://定时器3通道4
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
					case 1://定时器4通道1
						TIM_SetCompare1(TIM4,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 2://定时器4通道2
						TIM_SetCompare2(TIM4,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://定时器4通道3
						TIM_SetCompare3(TIM4,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://定时器4通道4
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
					case 1://定时器5通道1
						TIM_SetCompare1(TIM5,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 2://定时器5通道2
						TIM_SetCompare2(TIM5,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 3://定时器5通道3
						TIM_SetCompare3(TIM5,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					case 4://定时器5通道4
						TIM_SetCompare4(TIM5,(uint16_t)((float)pwm->reload*pwm->duty[i]/100.0));break;
					default: break;
				} 
			}
			else;
		}break;
		default: break;
	}
}

//-----修改结构体成员来修改PWM的波形-----
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

//-----设置PWM的频率-----
void Set_PWMFreqent(Obj_PWMInit *pwm, u32 freqent)
{
	pwm->syspcs=0;
	pwm->reload=72000000/freqent;
	TIMX_PWM_Init(pwm);
}

//-----设置PWM的频率和占空比-----
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
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//
						break;
					case 3:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  			//Timer2部分重映射 
						//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			default: break;
		}
}

//-----选择PWM的输出GPIO和映射情况-------
void Choose_TIM2_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//
						break;
					case 3:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2部分重映射 
						//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2部分重映射
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射					
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);  			//Timer2部分重映射
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射					
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2部分重映射
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射					
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			default: break;
		}
}

//-----选择PWM的输出GPIO和映射情况-------
void Choose_TIM3_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//
						break;
					case 3:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);  			//Timer2部分重映射
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射					
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 3:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:  //完全重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  			//Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
						break;
					default: break;
				}
				break;
			default: break;
		}
}

//-----选择PWM的输出GPIO和映射情况-------
void Choose_TIM4_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &GPIO_InitStructure);//
						break;
					case 2:   //部分重映射
						
						break;
					case 3:   //完全重映射
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:  //部分重映射
						break;
					case 3:  //完全重映射
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:  //部分重映射
						break;
					case 3:  //完全重映射
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
						break;
					case 4:   //部分重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIO外设
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //使能复用功能
						GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //Timer2部分重映射 
						GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //禁止JTAG将引脚设为普通IO口，没有这条语句无法正确映射
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				//复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:  //完全重映射
						break;
					case 3:  //完全重映射
						break;
					default: break;
				}
				break;
			default: break;
		}
}
//-----选择PWM的输出GPIO和映射情况-------
void Choose_TIM5_PWMChannel(u8 channel,u8 remap)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	switch(channel)
		{
			case 1:   //CH1
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						break;
					case 3:   //部分重映射
						break;
					case 4:  //完全重映射
						break;
					default: break;
				}	break;
			case 2:   //CH2
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						break;
					case 3:  //完全重映射
						break;
					case 4:  //完全重映射
						break;
					default: break;
				}
				break;
			case 3:   //CH3
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						break;
					case 3:  //完全重映射
						break;
					case 4:  //完全重映射
						break;
					default: break;
				}
				break;
			case 4:  //CH4
				switch(remap)
				{
					case 1:  //没有重映射
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
						break;
					case 2:   //部分重映射
						break;
					case 3:  //完全重映射
						break;
					case 4:  //完全重映射
						break;
					default: break;
				}
				break;
			default: break;
		}
}


