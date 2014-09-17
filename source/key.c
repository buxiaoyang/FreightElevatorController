#include <reg52.h>
#include <intrins.h>
#include <parameter.h>
#include <key.h>
#include <dispatch.h>


void Key_Scan(void);

unsigned char Key_Scan_Steps = 0; 		//0：初始状态 如果有按键按下则进入1
										//1：延迟10ms
										//2：如果按键确实按下则进入3
										//3：确定按键
										//4：如果按键释放则进入0

void Key_Scan(void)
{
	switch(Key_Scan_Steps)
	{
		case 0:
			if(sensorButton1 == 0 || sensorButton2 == 0)
			{
			   	Key_Scan_Steps = 1;
			}
		break;
		case 1:
			if(sensorButton1 == 0 || sensorButton2 == 0)
			{
			   	Key_Scan_Steps = 2;
			}
			else
			{
				Key_Scan_Steps = 0;
			}
		break;
		case 2:
			if(sensorButton1 == 0) //一楼按钮
			{
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 1;
				}
			}
			if(sensorButton2 == 0) //二楼按钮
			{	
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 3;
				}
			}
			Key_Scan_Steps = 3;
		break;
		case 3:
			if(sensorButton1 == 1 && sensorButton2 == 1)
			{
			   	Key_Scan_Steps = 0;
			}
		break;
		default:
			 _nop_();
	}
}