#include "sys.h"
#include "usart3.h"	 
#include "table.h"
#include "string.h"
#include "device.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
	#include "FreeRTOS.h"					//ucos 使用	 
	#include "task.h"
#endif

u8 BBB_Control_flag = 0x01;
  
void uart3_init(u32 bound){
	
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &USART_InitStructure); 
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART3, ENABLE);                  

}

void Usart3_sendByte(u8 data)
{
	USART_SendData(USART3,data);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET){}//等待发送结束
}

u8 Nano_checkState=0;  					//状态机控制标志

void USART3_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	static u8 i=0;
	static u8 data[PacketMAXDataLEN];
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res = USART_ReceiveData(USART3);			//读取接收到的数据
		switch(Nano_checkState)		//状态机
		{	
			case 0:												//帧头校验
				Nano_Agreement.header_H=Res;
				if(Res==0xca)
					Nano_checkState=1;
				else
					Nano_checkState=0;
				break;
			case 1:											//帧头校验
				Nano_Agreement.header_L=Res;
					if(Res==0xac)
					Nano_checkState=2;
				else
					Nano_checkState=0;
				break;
			case 2:											//fish识别位
				Nano_Agreement.funcId_H=Res;
				Nano_checkState=3;
				break;
			case 3:											//帧识别符low位获取	
				Nano_Agreement.funcId_L=Res;
				Nano_checkState=4;
				break;
			case 4:														//帧长获取							
				Nano_Agreement.dataLen=Res;
				Nano_checkState=5;
			  break;
			case 5:														//子功能获取
				Nano_Agreement.subFlag=Res;
				if(Nano_Agreement.dataLen-6==0)  	//无数据时，则跳过数据获取环节
					Nano_checkState=7;
				else
					Nano_checkState=6;
			break;
			case 6:											//数据获取
				data[i]=Res;
				i++;
				if(i>=Nano_Agreement.dataLen-6)
				{
					i=0;
					Nano_checkState=7;
				}
				else
				{
					Nano_checkState=6;
				}
			break;
			case 7:											//获取校验位
				Nano_Agreement.check=Res;
	//			Verify_CheckBit(&F521_Agreement,F521_Agreement.check);
				Nano_checkState=8;
	//			if(Verify_CheckBit(&F521_Agreement,F521_Agreement.check)==1)  //校验成功，进入下一阶段
	//				Nano_checkState=8;
	//			else																		//否则，返回帧头检验
	//				Nano_checkState=0;
			break;
			case 8:																		//帧尾
				Nano_Agreement.footer=Res;
				switch(Nano_Agreement.subFlag)
				{
					case EngineParamFlag:
						memcpy(&board_engines,data,Nano_Agreement.dataLen-6);
						//MainEngine_Driver(board_engines.mainEngine_left,board_engines.mainEngine_right);
						break;
					default:
						break;
				}
				if(Nano_checkState==8)
				{
					memset(data,0,sizeof(data)); //处理完数据后，全部置零
					Nano_checkState=0;
				}	
			break;
			default:break;
		}
	} 
} 


