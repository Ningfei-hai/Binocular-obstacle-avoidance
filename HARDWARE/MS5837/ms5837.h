#ifndef __MS5837_H_
#define __MS5837_H_
#include "sys.h"
#include "myiic.h"
#include "delay.h"

#define MS5837ADDRESS_Write 0xEC    //��������
#define MS5837ADDRESS_Read  0xED 		//��ȡ����

#define ACK_MS5837  1
#define NACK_MS5837 0

////-----MS5837��ָ�-----
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

//#define MS5837ADDRESS_Write  0xEC  //д���ݵ�Ms
//#define MS5837ADDRESS_Read   0xED	//��Ms��ȡ����

//#define ACK_MS5837 1
//#define NACK_MS5837 0

////-----MS5837��ָ�-----
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

////-----��������-----
//void SendCommand_MS5837(u8 command);     	//����ָ���MS5837
//void ReceiveData_MS5837(u8 ms_memory[]); 	//���մ�MS5837��ȡ������
//void MS5837_Init(void);										//��ʼ��MS5837����ȡ6������������
//void MS5837_Reset(void);									//��λMS5837
//void MS5837_ConvertD1_Press(void);        //��ȡ12bit�Ĵ�����ѹ��ֵ
//void MS5837_ConvertD2_Temp(void);					//��ȡ12bit�Ĵ������¶�ֵ
//void MS5867_PressCheck(void);							//���㴫������������
//u32 MS5837_getTemperature(void);					//���ش������ɼ��Ļ����¶ȵ�100��
//u32 MS5837_getWaterPress(void);						//���ش������ɼ��Ļ���ѹ��
////-----end-----
//#endif





