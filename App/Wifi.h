#ifndef _wifi_h
#define _wifi_h
#include "arm_base_define.h"
#include "Memory.h"
#include "Debugprintf.h"

#define			OK					"OK"
#define			START				">"
#define			AT					"AT\r\n"//检测wifi模块是否在线
#define			ATE0				"ATE0\r\n"//关闭回显
#define			ATE1				"ATE1\r\n"//开启回显
#define			WIFIMODE			"AT+CWMODE=3\r\n"//设置为STA+AP模式
#define			RST					"AT+RST\r\n"//设置模式进行重启生效
#define			CWJAP				"AT+CWJAP=\"LINK_001\",\"0123456789\"\r\n"//连接wifi
#define			CIPMUX				"AT+CIPMUX=0\r\n"//设置但连接，透传模式只能设置但连接
#define			CIPMODE1			"AT+CIPMODE=1\r\n"//设置透传模式
#define			CIPSTART			"AT+CIPSTART=\"TCP\",\"192.168.1.100\",8080\r\n"//连接远端
#define			CIPSEND				"AT+CIPSEND\r\n"//进入透传模式,返回>

#define			BACKAT				"+++"//返回指令模式
#define			CLOSESER			"AT+CIPCLOSE\r\n"//断开与服务器的连接
#define			EXITLINK			"AT+CWQAP\r\n"//退出与路由器的连接

#pragma pack(push,1)
typedef struct{
	u8 connect;
}_WIFI_t;
#pragma pack(pop)

extern _WIFI_t Wifi_t;

u8 *check_cmd(u8 *cmd);
u8 wifi_mode_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
void wifi_init(void);


#endif
