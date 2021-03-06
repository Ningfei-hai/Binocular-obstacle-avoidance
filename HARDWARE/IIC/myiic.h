#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

//IO��������
 
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;} //PB������������������
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;} //PB�����������������

//IO��������	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //����SDA 

//IIC���в�������
void IIC_Init_B30(void);                //��ʼ��IIC��IO��				 
void IIC_Start_B30(void);				//����IIC��ʼ�ź�
void IIC_Stop_B30(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte_B30(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte_B30(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack_B30(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack_B30(void);					//IIC����ACK�ź�
void IIC_NAck_B30(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















