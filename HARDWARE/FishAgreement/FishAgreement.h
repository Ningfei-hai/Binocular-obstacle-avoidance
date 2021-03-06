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
		u8 header_H;								//帧头
		u8 header_L;
		u8 funcId_H;								//fish识别
		u8 funcId_L;								//读写
		u8 dataLen;									//数据长度 单位byte
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
		u8 check;										//校验位				
		u8 footer;									//帧尾
} PolaV6_Data;

typedef struct SensorMsg
{
	float waterDepth;			//水深	
	float waterTemp;			//水温	
	float btryVlot;		//电池电压
	float ultrasonic_data;//超声波测距
	float GPS_time;				//GPS_时间戳
	float GPS_longitude;	//GPS_经度
	float GPS_latitude;		//GPS_纬度
	float GPS_high;				//GPS_高度
	float Reserve_1;			//预留1
	float Reserve_2;			//预留2
	float Reserve_3;      //预留3
}Obj_SensorMsg;

#define EngineParamLEN 9
#define EngineParamFlag 0x03
typedef struct EngineParam
{
	float mainEngine_left;		//主推电机左				
	float mainEngine_right;		//主推电机右						
	float Engine_pitch;				//俯仰电机					
	float camera_PWM;					//摄像机舵机				
	float LED_PWM;						//LED控制	
	float Laser_PWM;					//机光开关								
	float Reserve_1;    			//预留1
	float Reserve_2;					//预留2
	float Reserve_3;					//预留3
}Obj_EngineParam;

typedef struct AgreementSelect
{
	Obj_EngineParam EngineParam;
	Obj_SensorMsg SensorMsg;
	
}Uon_AgSelect;


#define LoraAddr 0x03
#define PacketMAXDataLEN 100 	//数据包的最大长度100/4Byte
typedef struct FishAgreement  //F521协议结构体
{
	u8 header_H;								//帧头
	u8 header_L;
	u8 funcId_H;								//fish识别
	u8 funcId_L;								//读写
	u8 dataLen;									//数据长度 单位byte
	u8 subFlag;									//子功能
	Uon_AgSelect data;					//数据
	u8 check;										//校验位				
	u8 footer;									//帧尾	
}Obj_Fish;

Obj_Fish Encode_FishAgreement(Uon_AgSelect ag,u8 type);
void Usart3_sendFishAgreement(Obj_Fish f);
void Usart3_sendPolaV6_Data(PolaV6_Data f);
#endif

