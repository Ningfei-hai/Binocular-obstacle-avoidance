#include "device.h"
#include "delay.h"

#define LED_UseChannel 1
#define Laser_UseChannel 2
#define LED_WorkFreq 500
#define Laser_WorkFreq 50
	
Obj_PWMInit LED_Laser_Ctrl=
{
	2,
	{Channel_Open,Channel_Open,Channel_Open,Channel_Open},
	{GPIO_noRemap,GPIO_noRemap,GPIO_noRemap,GPIO_noRemap},
	{10,20,30,40},
	1000-1,
	72-1,
	TIM_CounterMode_Up,
	0,
	OCMode_PWM2,
	OCPolarity_Low,
	ENABLE
};

void LED_Laser_Driver(float led,float laser)
{	
	Set_PWMFreqentandDuty(&LED_Laser_Ctrl,LED_UseChannel,500,led); //需要注意一下频率范围
	Set_TIMX_PWMState(&LED_Laser_Ctrl);
	Set_PWMFreqentandDuty(&LED_Laser_Ctrl,Laser_UseChannel,50,laser); //需要注意一下频率范围
	Set_TIMX_PWMState(&LED_Laser_Ctrl);
}

void LED_Laser_Init()
{
	LED_Laser_Driver(0,0);
	delay_ms(1000);
	LED_Laser_Driver(0,100);
	delay_ms(1000);
	LED_Laser_Driver(0,0);
	delay_ms(1000);
	LED_Laser_Driver(0,100);
	delay_ms(1000);
	LED_Laser_Driver(0,0);

}

#define Pitch_UseChannel 3
#define Dir_UseChannel 4
#define Steering_WorkFreq 50
	
Obj_PWMInit SteeringEngineCtrl=
{
	4,
	{Channel_Open,Channel_Open,Channel_Open,Channel_Open},
	{GPIO_noRemap,GPIO_noRemap,GPIO_noRemap,GPIO_noRemap},
	{10,20,30,40},
	1000-1,
	72-1,
	TIM_CounterMode_Up,
	0,
	OCMode_PWM2,
	OCPolarity_Low,
	ENABLE
};

/*---------------------------------------------
函数功能：驱动方向和俯仰舵机  (该电机的旋转角度为0-60)
函数参数：pitch表示俯仰电机的旋转速叮dir:摄像头舵机的旋转角度
注释:
-----------------------------------------------*/
void SteeringEngine_Driver(float pitch,float dir)
{
	pitch=(0.05*pitch+50.0);
	pitch=pitch/10.0;							
	dir=(0.05*dir+50.0);
	dir=dir/10.0;	
	Set_PWMFreqentandDuty(&SteeringEngineCtrl,Pitch_UseChannel,50,pitch); //需要注意一下频率范围
	Set_TIMX_PWMState(&SteeringEngineCtrl);
	Set_PWMFreqentandDuty(&SteeringEngineCtrl,Dir_UseChannel,50,dir); //需要注意一下频率范围
	Set_TIMX_PWMState(&SteeringEngineCtrl);
}

void SteeringEngine_Init()
{
	SteeringEngine_Driver(500,500);
	delay_ms(1500);
	SteeringEngine_Driver(200,500);
	delay_ms(2000);
	SteeringEngine_Driver(500,500);
	delay_ms(1500);
	SteeringEngine_Driver(800,500);
	delay_ms(2000);
	SteeringEngine_Driver(500,500);
	delay_ms(1500);
}

#define MainEngine_WorkFreq 50
#define Main_UseChannel_L 3
#define Main_UseChannel_R 4
Obj_PWMInit MainEngineCtrl=
{
	3,
	{Channel_Open,Channel_Open,Channel_Open,Channel_Open},
	{GPIO_noRemap,GPIO_noRemap,GPIO_noRemap,GPIO_noRemap},
	{10,20,30,40},
	1000-1,
	72-1,
	TIM_CounterMode_Up,
	0,
	OCMode_PWM2,
	OCPolarity_Low,
	ENABLE
};

/*---------------------------------------------
函数功能：驱动左右主推电机
前进：200，800
后退：800，200
函数参数：enable:使能驱动函数，dir:驱动方向，speed:电机的转速（百分制）
注释：speed的范围为：0-1000，0-500为反转，500-1000为正转
-----------------------------------------------*/
void MainEngine_Driver(float speed_L, float speed_R)
{
	float duty_L =0;
	float duty_R =0;
	if((speed_L>=0 && speed_L<=2000) || (speed_R>=0 && speed_R<=2000))		//规定范围内
	{
		duty_L=(0.05*speed_L+50.0);
		duty_L=duty_L/10.0;							
		duty_R=(0.05*speed_R+50.0);
		duty_R=duty_R/10.0;	
		Set_PWMFreqentandDuty(&MainEngineCtrl,Main_UseChannel_L,MainEngine_WorkFreq,duty_L); //需要注意一下频率范围
		Set_TIMX_PWMState(&MainEngineCtrl);
		Set_PWMFreqentandDuty(&MainEngineCtrl,Main_UseChannel_R,MainEngine_WorkFreq,duty_R); //需要注意一下频率范围
		Set_TIMX_PWMState(&MainEngineCtrl);
	}
}

void MainEngine_Init()
{
	MainEngine_Driver(500,500); 
	delay_ms(1500);
	MainEngine_Driver(800,800); //左转
	delay_ms(2000);
	MainEngine_Driver(500,500); 
	delay_ms(1500);
	MainEngine_Driver(200,200); //右转
	delay_ms(2000);
	MainEngine_Driver(500,500);
	delay_ms(1500);
}

