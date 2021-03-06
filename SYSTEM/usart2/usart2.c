#include "sys.h"
#include "usart2.h"	 
#include "table.h"
#include "string.h"
#include "FishAgreement.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
	#include "FreeRTOS.h"					//ucos 使用	 
	#include "task.h"
#endif
  
void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //使能UART3所在GPIOB的时钟  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
	//USART2_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);					//初始化GPIOA.2
   
  //USART2_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3  

  //USART2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=9;		//抢占优先级0 高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);														//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2 

}

void Usart2_sendByte(u8 data)
{
	USART_SendData(USART2,data);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}//等待发送结束
}

u8 Nano_checkState=0;  					//状态机控制标志

void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	static u8 i=0;
	static u8 data[PacketMAXDataLEN];
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART2);			//读取接收到的数据
		switch(Nano_checkState)		//状态机
		{	
			case 0:												//帧头校验
				bbbAgreement.header_H=Res;
				if(Res==0xca)
					Nano_checkState=1;
				else
					Nano_checkState=0;
				break;
			case 1:											//帧头校验
				bbbAgreement.header_L=Res;
					if(Res==0xac)
					Nano_checkState=2;
				else
					Nano_checkState=0;
				break;
			case 2:											//fish识别位
				bbbAgreement.funcId_H=Res;
				Nano_checkState=3;
				break;
			case 3:											//帧识别符low位获取	
				bbbAgreement.funcId_L=Res;
				Nano_checkState=4;
				break;
			case 4:														//帧长获取							
				bbbAgreement.dataLen=Res;
				Nano_checkState=5;
			  break;
			case 5:														//子功能获取
				bbbAgreement.subFlag=Res;
				if(bbbAgreement.dataLen-6==0)  	//无数据时，则跳过数据获取环节
					Nano_checkState=7;
				else
					Nano_checkState=6;
			  break;
			case 6:											//数据获取
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
			case 7:											//获取校验位
				bbbAgreement.check=Res;
	//			Verify_CheckBit(&F521_Agreement,F521_Agreement.check);
				Nano_checkState=8;
	//			if(Verify_CheckBit(&F521_Agreement,F521_Agreement.check)==1)  //校验成功，进入下一阶段
	//				Agreement_BBB_checkState=8;
	//			else																		//否则，返回帧头检验
	//				Agreement_BBB_checkState=0;
			break;
			case 8:																		//帧尾
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
					memset(data,0,sizeof(data)); //处理完数据后，全部置零
					Nano_checkState=0;
				}	
			break;
			default:break;
		}
	} 
} 


