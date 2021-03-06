#ifndef __MS5837_H_
#define __MS5837_H_
#include "sys.h"
#include "myiic.h"
#include "delay.h"

#define MS5837ADDRESS_Write 0xEC    //发送命令
#define MS5837ADDRESS_Read  0xED 		//读取数据

#define ACK_MS5837  1
#define NACK_MS5837 0

////-----MS5837的指令集-----
#define MS5837_CRC 					0xA0
#define MS5837_PRESS_SENS 	0xA2
#define MS5837_PRESS_OFFSET 0xA4
#define MS5837_TEMP_SENS		0xA6
#define MS5837_TEMP_OFFSET 	0xA8
#define MS5837_TEMP_REFER 	0xAA
#define MS5837_TEMPERATURE 	0xAC
#define MS5837_RESET 				0x1E

#define MS5837_COVTD1_4096 0x48
#define MS5837_COVTD2_4096 0x58

void MS5837_Init(void);
void SendMsg_MS5837(u8 command);
u32 MS5837_ConvertD1_Press(void);
u32 MS5837_ConvertD2_Temp(void);
float Calculate_MS5837Temperature(void);
float Calculate_Ms5837waterrPress(void);

#endif


//#ifndef _MS5837_H_
//#define _MS5837_H_
//#include "myiic.h"

//#define MS5837ADDRESS_Write  0xEC  //写数据到Ms
//#define MS5837ADDRESS_Read   0xED	//从Ms读取数据

//#define ACK_MS5837 1
//#define NACK_MS5837 0

////-----MS5837的指令集-----
//#define MS5837_CRC 					0xA0
//#define MS5837_PRESS_SENS 	0xA2
//#define MS5837_PRESS_OFFSET 0xA4
//#define MS5837_TEMP_SENS		0xA6
//#define MS5837_TEMP_OFFSET 	0xA8
//#define MS5837_TEMP_REFER 	0xAA
//#define MS5837_TEMPERATURE 	0xAC
//#define MS5837_RESET 				0x1E

//#define MS5837_COVTD1_4096 0x48
//#define MS5837_COVTD2_4096 0x58
////-----end-----

////-----操作函数-----
//void SendCommand_MS5837(u8 command);     	//发送指令集到MS5837
//void ReceiveData_MS5837(u8 ms_memory[]); 	//接收从MS5837获取的数据
//void MS5837_Init(void);										//初始化MS5837，获取6个传感器参数
//void MS5837_Reset(void);									//复位MS5837
//void MS5837_ConvertD1_Press(void);        //获取12bit的传感器压力值
//void MS5837_ConvertD2_Temp(void);					//获取12bit的传感器温度值
//void MS5867_PressCheck(void);							//计算传感器的误差参数
//u32 MS5837_getTemperature(void);					//返回传感器采集的环境温度的100倍
//u32 MS5837_getWaterPress(void);						//返回传感器采集的环境压力
////-----end-----
//#endif





