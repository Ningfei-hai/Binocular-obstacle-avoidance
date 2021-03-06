#ifndef _FISHAGREEMENT_H_
#define _FISHAGREEMENT_H_
#include "sys.h"
//#include "usart2.h"
//#include "usart3.h"	

#define BBB_ENABLE  0X01
#define BBB_DISABLE  0X00

#define WRITEMSG_TOHOST 	0x30
#define READMSG_FROMHOST 	0x31

#define WRITEMSG_TOBBB 		0x30
#define READMSG_FROMBBB 	0x31

#define FRAMEFLAG_LEN 6

#define SensorMsgLEN 11
#define SensorFlag 0x01

typedef struct{
		u8 header_H;								//֡ͷ
		u8 header_L;
		u8 funcId_H;								//fishʶ��
		u8 funcId_L;								//��д
		u8 dataLen;									//���ݳ��� ��λbyte
		u8 subFlag;
    float navi_time_ms;
    float longtitude;
    float latitude;
    float height;
    float GPS_head;
    float GPS_v;
    float acc_x;
    float acc_y;
    float acc_z;
    float v_north;
    float v_sky;
    float v_east;
    float omg_x;
    float omg_y;
    float omg_z;
    float pitch;
    float yaw;
    float roll;
    float mag_heading;
    float gps_lat;
    float gps_long;
		u8 check;										//У��λ				
		u8 footer;									//֡β
} PolaV6_Data;

typedef struct SensorMsg
{
	float waterDepth;			//ˮ��	
	float waterTemp;			//ˮ��	
	float btryVlot;		//��ص�ѹ
	float ultrasonic_data;//���������
	float GPS_time;				//GPS_ʱ���
	float GPS_longitude;	//GPS_����
	float GPS_latitude;		//GPS_γ��
	float GPS_high;				//GPS_�߶�
	float Reserve_1;			//Ԥ��1
	float Reserve_2;			//Ԥ��2
	float Reserve_3;      //Ԥ��3
}Obj_SensorMsg;

#define EngineParamLEN 9
#define EngineParamFlag 0x03
typedef struct EngineParam
{
	float mainEngine_left;		//���Ƶ����				
	float mainEngine_right;		//���Ƶ����						
	float Engine_pitch;				//�������					
	float camera_PWM;					//��������				
	float LED_PWM;						//LED����	
	float Laser_PWM;					//���⿪��								
	float Reserve_1;    			//Ԥ��1
	float Reserve_2;					//Ԥ��2
	float Reserve_3;					//Ԥ��3
}Obj_EngineParam;

typedef struct AgreementSelect
{
	Obj_EngineParam EngineParam;
	Obj_SensorMsg SensorMsg;
	
}Uon_AgSelect;


#define LoraAddr 0x03
#define PacketMAXDataLEN 100 	//���ݰ�����󳤶�100/4Byte
typedef struct FishAgreement  //F521Э��ṹ��
{
	u8 header_H;								//֡ͷ
	u8 header_L;
	u8 funcId_H;								//fishʶ��
	u8 funcId_L;								//��д
	u8 dataLen;									//���ݳ��� ��λbyte
	u8 subFlag;									//�ӹ���
	Uon_AgSelect data;					//����
	u8 check;										//У��λ				
	u8 footer;									//֡β	
}Obj_Fish;

Obj_Fish Encode_FishAgreement(Uon_AgSelect ag,u8 type);
void Usart3_sendFishAgreement(Obj_Fish f);
void Usart3_sendPolaV6_Data(PolaV6_Data f);
#endif

