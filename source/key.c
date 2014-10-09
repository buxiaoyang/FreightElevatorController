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
			if(sensorF2Button1 == 0) //���� һ¥��ť
			{
				if(ManiDispatchSteps == 0 && sensorFloor1 == 1)
				{
					ManiDispatchSteps = 1; //�����ᵽ1¥
				}
			}
			else if(sensorF2Button2 == 0 && sensorFloor1 == 1 ) //���� ��¥��ť
			{	
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 3; //�����ᵽ2¥
				}
			}
			else if(sensorF1Button1 == 0 && sensorFloor2 == 1) //һ�� һ¥��ť
			{	
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 1; //�����ᵽ1¥
				}
			}
			else if(sensorF1Button2 == 0 && sensorFloor2 == 1) //һ�� ��¥��ť
			{	
				if(ManiDispatchSteps == 0)
				{
					ManiDispatchSteps = 3; //�����ᵽ2¥
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