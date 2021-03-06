#include "FishAgreement.h"
#include "table.h"
#include "usart2.h"
#include "usart3.h"

Obj_Fish Encode_FishAgreement(Uon_AgSelect ag,u8 type)
{
	Obj_Fish fish;
	u8 *data;
	u8 i=0;
	
	fish.header_H=0xca;
	fish.header_L=0xac;
	fish.funcId_H=LoraAddr;
	fish.funcId_L=0x30;

	switch(type)
	{
		case EngineParamFlag:
			fish.subFlag=EngineParamFlag;
			fish.dataLen=4*EngineParamLEN+FRAMEFLAG_LEN;
			data=(u8 *)&ag.EngineParam;
			fish.data.EngineParam=ag.EngineParam;
		break;
		case SensorFlag:
			fish.subFlag=SensorFlag;
			fish.dataLen=4*SensorMsgLEN+FRAMEFLAG_LEN;
			data=(u8 *)&ag.SensorMsg;
			fish.data.SensorMsg=ag.SensorMsg;
		break;
		default:
			break;
	}
	fish.check=fish.funcId_H^fish.funcId_L;
	fish.check=fish.check^fish.dataLen;
	fish.check=fish.check^fish.subFlag;
	for(i=0;i<fish.dataLen-FRAMEFLAG_LEN;i++)
		fish.check=fish.check^data[i];
	fish.footer=0xcc;
	return fish;
}
void Usart3_sendFishAgreement(Obj_Fish f)
{
	u8 i=0;
	u8 *data=(u8 *)&f.data.SensorMsg;
	Usart3_sendByte(f.header_H);
	Usart3_sendByte(f.header_L);
	Usart3_sendByte(f.funcId_H);
	Usart3_sendByte(f.funcId_L);
	Usart3_sendByte(f.dataLen);
	Usart3_sendByte(f.subFlag);
	for(i=0;i<f.dataLen-FRAMEFLAG_LEN;i++)
			Usart3_sendByte(data[i]);
	Usart3_sendByte(f.check);
	Usart3_sendByte(f.footer);
}
void Usart3_sendPolaV6_Data(PolaV6_Data f)
{
	u8 i=0;
	u8 *data=(u8 *)&f.navi_time_ms;
	Usart3_sendByte(f.header_H);
	Usart3_sendByte(f.header_L);
	Usart3_sendByte(f.funcId_H);
	Usart3_sendByte(f.funcId_L);
	Usart3_sendByte(f.dataLen);
	Usart3_sendByte(f.subFlag);
	for(i=0;i<f.dataLen-FRAMEFLAG_LEN;i++)
			Usart3_sendByte(data[i]);
	Usart3_sendByte(f.check);
	Usart3_sendByte(f.footer);
}

