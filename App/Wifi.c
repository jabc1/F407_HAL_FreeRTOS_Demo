/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Wifi.c
Description		: 主要实现Wifi模块初始化及连接功能
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-04
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Wifi.h"
#include "Delay.h"
_WIFI_t Wifi_t;
/*******************************************************************************
* @Function		:u8 *check_cmd(u8 *cmd)
* @Description	:主要实现check是否有正确返回cmd
* @Input		:*cmd
* @Output		:null
* @Return		:*cmd or null
* @Others		:null
*******************************************************************************/
u8 *check_cmd(u8 *cmd)
{
	char *strx=NULL;
	u8 i = 0;
	u8 tbuf[512];

	while(fifo_getc(&WifiFifo,&tbuf[i++]))
	{
		;
	}

	tbuf[i] = '\0';
	//printf_dma("%s",tbuf);
	strx=strstr((const char*)&tbuf[0],(const char*)cmd);
	return (u8*)strx;
}

/*******************************************************************************
* @Function		:u8 wifi_mode_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
* @Description	:主要实现wifi模块发送相关命令
* @Input		:*cmd发送命令 *ack预期回应命令 waittime等待时间
* @Output		:null
* @Return		:0 or 1
* @Others		:null
*******************************************************************************/
u8 wifi_mode_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0;
	wifi_printf("%s",cmd);
	if(ack && waittime)
	{
		delay_xms(20);
		while(--waittime)
		{
			if(!fifo_empty(&WifiFifo))
			{
				if(check_cmd(ack))
				{
					//printf_dma("send ok %s\n",cmd);
					res = 0;
					break;
				}
			}
		}
		if(waittime == 0)
		{
			return res;
		}
	}
	return res;
}
void wifi_reset()
{
	wifi_mode_send_cmd((u8 *)BACKAT,(u8 *)OK,50);
	delay_xms(2000);
	wifi_mode_send_cmd((u8 *)CLOSESER,(u8 *)OK,50);
	wifi_mode_send_cmd((u8 *)EXITLINK,(u8 *)OK,50);
}
/*******************************************************************************
* @Function		:void wifi_init()
* @Description	:主要实现wifi模块初始化功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void wifi_init()
{
	wifi_reset();
	delay_xms(2000);
	wifi_mode_send_cmd((u8 *)AT,(u8 *)OK,50);
	wifi_mode_send_cmd((u8 *)ATE1,(u8 *)OK,50);
	wifi_mode_send_cmd((u8 *)AT,(u8 *)OK,50);
	wifi_mode_send_cmd((u8 *)AT,(u8 *)OK,50);
	wifi_mode_send_cmd((u8 *)ATE0,(u8 *)OK,50);
	wifi_mode_send_cmd((u8 *)WIFIMODE,(u8 *)OK,100);
	wifi_mode_send_cmd((u8 *)RST,(u8 *)OK,100);
	wifi_mode_send_cmd((u8 *)CWJAP,(u8 *)OK,500);
	delay_xms(2000);
	wifi_mode_send_cmd((u8 *)CIPMUX,(u8 *)OK,100);
	delay_xms(1300);
	wifi_mode_send_cmd((u8 *)CIPMODE1,(u8 *)OK,100);
	wifi_mode_send_cmd((u8 *)CIPSTART,(u8 *)OK,100);
	if(wifi_mode_send_cmd((u8 *)CIPSEND,(u8 *)START,100) == 0)
	{
		wifi_printf("test tcp send\r\n");
		Wifi_t.connect = true;
	}
	else
	{
		Wifi_t.connect = false;
	}
}

















