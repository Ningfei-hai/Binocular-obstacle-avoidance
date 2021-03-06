#include "ms5837.h"
#include "math.h"
//-----传感器的空间数据-----
u32 MS5837_promData[8];
u32 MS5837_promPress=0;
u32 MS5837_promTemp=0;
//--------------------------

unsigned char MS5837_CRC4(unsigned int n_prom[]) 
{
	int cnt;
	unsigned int n_rem=0; 
	unsigned char n_bit;
	n_prom[0]=((n_prom[0]) & 0x0FFF); 
	n_prom[7]=0; 
	for (cnt = 0; cnt < 16; cnt++) 
	{ 
			if (cnt%2==1) n_rem ^= (unsigned short) ((n_prom[cnt>>1]) & 0x00FF);
			else n_rem ^= (unsigned short) (n_prom[cnt>>1]>>8);
			for (n_bit = 8; n_bit > 0; n_bit--)
			{
					if (n_rem & (0x8000)) n_rem = (n_rem << 1) ^ 0x3000;
					else n_rem = (n_rem << 1);
			}
	}
	n_rem= ((n_rem >> 12) & 0x000F);
	return (n_rem ^ 0x00);
}

void SendMsg_MS5837(u8 command)
{
	IIC_Start_B30();
	IIC_Send_Byte_B30(MS5837ADDRESS_Write);
	if(!IIC_Wait_Ack_B30())  //地址发送成功
	{
		IIC_Send_Byte_B30(command); 
		IIC_Wait_Ack_B30();
	}
	else
		IIC_Stop_B30();
	  IIC_Stop_B30();
	  delay_xus(5);
}
void MS5837_Reset()
{
	SendMsg_MS5837(MS5837_RESET);
}

uint16_t ReceiveConfigMsg_MS5837()
{
	uint16_t reg;
	u8 h_bit,l_bit=0;	
	IIC_Start_B30();
	IIC_Send_Byte_B30(MS5837ADDRESS_Read);
	IIC_Wait_Ack_B30();
	h_bit=IIC_Read_Byte_B30(ACK_MS5837);
	l_bit=IIC_Read_Byte_B30(NACK_MS5837);
	IIC_Stop_B30();
	
	//-----数据转换-----
	reg=(((uint16_t)h_bit)<<8) | l_bit;
	return reg;
}

u32 ReceiveDataMsg_MS5837()
{
	u32 reg;
	u8 h_bit,m_bit,l_bit=0;	
	IIC_Start_B30();
	IIC_Send_Byte_B30(MS5837ADDRESS_Read);
	IIC_Wait_Ack_B30();
	h_bit=IIC_Read_Byte_B30(ACK_MS5837);
	delay_xus(1);   //....
	m_bit=IIC_Read_Byte_B30(ACK_MS5837);
	delay_xus(1);   //....
	l_bit=IIC_Read_Byte_B30(NACK_MS5837);
	IIC_Stop_B30();
	//-----数据转换-----
	reg=(((uint32_t)h_bit)<<16) |(((uint32_t)m_bit)<<8)| l_bit;
	return reg;
}


void MS5837_Init()
{
	u8 i=0;
//	u8 check_crc=0;
//	u8 crc=0;
	MS5837_Reset();
	for(i=0;i<7;i++)
	{
		SendMsg_MS5837(MS5837_CRC+(2*i));
		delay_xus(5);
		MS5837_promData[i]=ReceiveConfigMsg_MS5837();
		delay_xus(5);
	}
//	check_crc=(u8)((MS5837_promData[0]&0xF000)>>12);
//	crc=MS5837_CRC4(MS5837_promData);
//	printf("CRC:%d   Check_CRC:%d\r\n",crc,check_crc);
//  while(crc==check_crc)
//		printf("successful!!\r\n");
	//else
//		printf("failure!!\r\n");
}

//-----温度值和压力值的转换-----
u32 MS5837_ConvertD1_Press()
{
	u32 D1=0;
	SendMsg_MS5837(MS5837_COVTD1_4096);    
	delay_ms(20);   			//模块采集数据的必要时间
	SendMsg_MS5837(0x00);	//读取ADC转换值
	delay_ms(20);
	D1=ReceiveDataMsg_MS5837();
	MS5837_promPress=D1;
	return D1;
}
u32 MS5837_ConvertD2_Temp()
{
	u32 D2=0;
	SendMsg_MS5837(MS5837_COVTD2_4096);
	delay_ms(20);							//模块采集数据的必要时间
	SendMsg_MS5837(0x00);    //读取ADC转换值
	delay_ms(20);
	D2=ReceiveDataMsg_MS5837();
	MS5837_promTemp=D2;
	return D2;
}
//-----------------------

//-----补偿和校正温度和压力，获得最后的值-----
float Calculate_MS5837Temperature()
{
	u32 temp=0;
	u32 diff_temp=0;
	u32 ms_temp=0;
	float real_temp=0.0;
	long int Ti=0;
	temp=MS5837_ConvertD2_Temp();
	diff_temp=temp-(((uint32_t)MS5837_promData[5])*256);
	ms_temp=2000+diff_temp*((uint32_t)MS5837_promData[6])/8388608;
	
	if(real_temp<20)
		Ti=(3*diff_temp*diff_temp)/(8589934592);
	else
		Ti=(2*diff_temp*diff_temp)/(137438953472);
	
	real_temp=(ms_temp-Ti)/100.0;
	return real_temp;
}


float Calculate_Ms5837waterrPress()
{
	u32 press=0;
	long int offset,sens=0;
	long int offset1,sens1=0;
	long int OFF,SENS=0;
	long int re=0;
	u32 temp=0;
	u32 diff_temp=0;
	u32 ms_temp=0;
	float real_press=0.0;
	//-----温度对水压的影响处理-----
	temp=MS5837_ConvertD2_Temp();
	diff_temp=temp-(((uint32_t)MS5837_promData[5])*256);
	ms_temp=2000+diff_temp*((uint32_t)MS5837_promData[6])/8388608;
	//------------------------------
	press=MS5837_ConvertD1_Press();
	
	if((ms_temp/100)<20)  //ms_temp<2000
	{
		offset=3*(2000-ms_temp)*(2000-ms_temp)/2;
		sens=5*(2000-ms_temp)*(2000-ms_temp)/8;
	}
	else
	{
		offset=(1*(ms_temp-2000)*(ms_temp-2000))/16;
		sens=0;
	}
	
	offset1=MS5837_promData[2]*65536+(MS5837_promData[4]*diff_temp)/128;
	sens1=MS5837_promData[1]*32768+(MS5837_promData[3]*diff_temp)/256;
	
	OFF=(offset1-offset);
	SENS=(sens1-sens);
	re=(long int)(long int)press*(SENS/2097152)-OFF;
	real_press=(re/8192)/10.0;
	
	return real_press;
}



