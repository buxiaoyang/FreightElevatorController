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
			if(sensorF2Button1 == 0 || sensorF2Button2 == 0 || sensorF1Button1 == 0 || sensorF1Button2 == 0)
			{
			   	Key_Scan_Steps = 1;
			}
		break;
		case 1:
			if(sensorF2Button1 == 0 || sensorF2Button2 == 0 || sensorF1Button1 == 0 || sensorF1Button2 == 0)
			{
			   	Key_Scan_Steps = 2;
			}
			else
			{
				Key_Scan_Steps = 0;
			}
		break;
		case 2:
			if(sensorF2Button1 == 0) //二层 一楼按钮
			{
				if(ManiDispatchSteps == 0 && sensorFloor1 == 1)
				{
					ManiDispatchSteps = 1; //电梯厢到1楼
				}
			}
			else if(sensorF2Button2 == 0 && sensorFloor1 == 1 ) //二层 二楼按钮
			{	
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 3; //电梯厢到2楼
				}
			}
			else if(sensorF1Button1 == 0 && sensorFloor2 == 1) //一层 一楼按钮
			{	
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 1; //电梯厢到1楼
				}
			}
			else if(sensorF1Button2 == 0 && sensorFloor2 == 1) //一层 二楼按钮
			{	
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 3; //电梯厢到2楼
				}
			}
			Key_Scan_Steps = 3;
		break;
		case 3:
			if(sensorF2Button1 == 1 && sensorF2Button2 == 1 && sensorF1Button1 == 1 && sensorF1Button2 == 1)
			{
			   	Key_Scan_Steps = 0;
			}
		break;
		default:
			 _nop_();
	}
}