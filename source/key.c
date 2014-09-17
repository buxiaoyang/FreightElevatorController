#include <reg52.h>
#include <intrins.h>
#include <parameter.h>
#include <key.h>
#include <dispatch.h>


void Key_Scan(void);

unsigned char Key_Scan_Steps = 0; 		//0����ʼ״̬ ����а������������1
										//1���ӳ�10ms
										//2���������ȷʵ���������3
										//3��ȷ������
										//4����������ͷ������0

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
			if(sensorButton1 == 0) //һ¥��ť
			{
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 1;
				}
			}
			if(sensorButton2 == 0) //��¥��ť
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