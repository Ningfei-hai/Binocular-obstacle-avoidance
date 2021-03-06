#include "sys.h"
#include "usart2.h"	 
#include "table.h"
#include "string.h"
#include "FishAgreement.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
	#include "FreeRTOS.h"					//ucos ʹ��	 
	#include "task.h"
#endif
  
void uart2_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //ʹ��UART3����GPIOB��ʱ��  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
	//USART2_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					//��ʼ��GPIOA.2
   
  //USART2_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3  

  //USART2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=9;		//��ռ���ȼ�0 ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);														//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2 

}

void Usart2_sendByte(u8 data)
{
	USART_SendData(USART2,data);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}//�ȴ����ͽ���
}

u8 Nano_checkState=0;  					//״̬�����Ʊ�־

void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	static u8 i=0;
	static u8 data[PacketMAXDataLEN];
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART2);			//��ȡ���յ�������
		switch(Nano_checkState)		//״̬��
		{	
			case 0:												//֡ͷУ��
				bbbAgreement.header_H=Res;
				if(Res==0xca)
					Nano_checkState=1;
				else
					Nano_checkState=0;
				break;
			case 1:											//֡ͷУ��
				bbbAgreement.header_L=Res;
					if(Res==0xac)
					Nano_checkState=2;
				else
					Nano_checkState=0;
				break;
			case 2:											//fishʶ��λ
				bbbAgreement.funcId_H=Res;
				Nano_checkState=3;
				break;
			case 3:											//֡ʶ���lowλ��ȡ	
				bbbAgreement.funcId_L=Res;
				Nano_checkState=4;
				break;
			case 4:														//֡����ȡ							
				bbbAgreement.dataLen=Res;
				Nano_checkState=5;
			  break;
			case 5:														//�ӹ��ܻ�ȡ
				bbbAgreement.subFlag=Res;
				if(bbbAgreement.dataLen-6==0)  	//������ʱ�����������ݻ�ȡ����
					Nano_checkState=7;
				else
					Nano_checkState=6;
			  break;
			case 6:											//���ݻ�ȡ
				data[i]=Res;
				i++;
				if(i>=bbbAgreement.dataLen-6)
				{
					i=0;
					Nano_checkState=7;
				}
				else
				{
					Nano_checkState=6;
				}
			break;
			case 7:											//��ȡУ��λ
				bbbAgreement.check=Res;
	//			Verify_CheckBit(&F521_Agreement,F521_Agreement.check);
				Nano_checkState=8;
	//			if(Verify_CheckBit(&F521_Agreement,F521_Agreement.check)==1)  //У��ɹ���������һ�׶�
	//				Agreement_BBB_checkState=8;
	//			else																		//���򣬷���֡ͷ����
	//				Agreement_BBB_checkState=0;
			break;
			case 8:																		//֡β
				bbbAgreement.footer=Res;
				switch(bbbAgreement.subFlag)
				{
					case SensorFlag:
						memcpy(&bbbAgreement.data.SensorMsg,data,sizeof(bbbAgreement.data.SensorMsg));
						break;
					case EngineParamFlag:
						memcpy(&bbbAgreement.data.EngineParam,data,sizeof(bbbAgreement.data.EngineParam));
//					  PolaV6_EnCode(bbbAgreement);
						break;
					default:
						break;
				}
				if(Nano_checkState==8)
				{
					memset(data,0,sizeof(data)); //���������ݺ�ȫ������
					Nano_checkState=0;
				}	
			break;
			default:break;
		}
	} 
} 


