#include <reg52.h>
#include <parameter.h>
#include <intrins.h>
#include <dispatch.h>

unsigned char ManiDispatchSteps = 0;

unsigned char SubDispatchGo1FloorSteps = 0; 	
unsigned char SubDispatchGo2FloorSteps = 0;

unsigned int SubDispatchGo1FloorTimer = 0;
unsigned int SubDispatchGo2FloorTimer = 0;

void checkSensor()
{
	if(sensorLimit == 1 || sensorEmergency == 0 || SensorStop == 1 || sensor402 == 1)
	{
		ManiDispatchSteps = 0;	
	}
}

/*�����ȳ���*/
// 0	�ղ�����
// 1	�����ᵽ1¥
// 3	�����ᵽ2¥

void ManiDispatch(void)
{
	checkSensor();
	switch(ManiDispatchSteps)
	{
		case 0: 
			IO_init();
			SubDispatchGo1FloorSteps = 0;
			SubDispatchGo2FloorSteps = 0;	
		break;
		case 1:
			SubDispatchGo1FloorSteps = 1;
			Led601 = 0;	//һ¥��ťָʾ�ƣ�
			ManiDispatchSteps ++;
		break;
		case 2:
			if(SubDispatchGo1FloorSteps == 0)
			{
				ManiDispatchSteps = 0;	
			}
		break;
		case 3:
			SubDispatchGo2FloorSteps = 1;
			Led602 = 0;	//��¥��ťָʾ��
			ManiDispatchSteps ++;
		break;
		case 4:
			if(SubDispatchGo2FloorSteps == 0)
			{
				ManiDispatchSteps = 0;
			}
		break;
		default:
			 _nop_();
	}
}

/*�����ᵽһ¥���ȳ���*/
// 0	�ղ���������δ��ʼ
// 1	�ӳ�һ��ʱ��,�ر�2¥������
// 2	�Źر�֮���ӳ�һ��ʱ��
// 3	�ӳ�ʱ�䵽������������
// 4	�����ᵽһ¥���ӳ�һ��ʱ��
// 5	�ӳ�ʱ�䵽����1¥������
// 6	�Ŵ�֮�󣬲������
void SubDispatchGo1Floor(void)
{
	switch(SubDispatchGo1FloorSteps)
	{
		case 0:	
			SubDispatchGo1FloorTimer = 0;
		break;
		case 1:	
			if(SubDispatchGo1FloorTimer > 100)
			{
				if(sensorDoorbelow == 0)
				{
				   	SubDispatchGo1FloorTimer = 0;
					SubDispatchGo1FloorSteps = 3;
				}
				else
				{
					DoorClose = 0;
					DoorFloor2 = 0;
					SubDispatchGo1FloorSteps ++;
				}
			}
		break;
		case 2:	
			if(sensorDoorbelow == 0)
			{
				DoorClose = 1;
				DoorFloor2 = 1;
				SubDispatchGo1FloorTimer = 0;
				SubDispatchGo1FloorSteps ++;
			}
		break;
		case 3:	
			if(SubDispatchGo1FloorTimer > 100)
			{
				BoxDown = 0;
				ledDS152 = 1; //�ر�2��ָʾ��
				ledX = 0;  //��������ָʾ��
				SubDispatchGo1FloorSteps ++;
			}
		break;
		case 4:	
			if(sensorFloor1 == 0)
			{
				BoxDown = 1;
				ledDS151  = 0; //��1��ָʾ��
				ledX = 1;  //��������ָʾ��
				SubDispatchGo1FloorTimer = 0;
				SubDispatchGo1FloorSteps ++;
			}
		break;
		case 5:	
			if(SubDispatchGo1FloorTimer > 100)
			{
				DoorOpen = 0;
				DoorFloor1 = 0;
				SubDispatchGo1FloorSteps ++;
			}
		break;
		case 6:	
			if(sensorDoortop == 1)
			{
				DoorOpen = 1;
				DoorFloor1 = 1;
				SubDispatchGo1FloorSteps = 0;
			}
		break;
		default:
			 _nop_();
	}
}


/*�����ᵽ��¥���ȳ���*/
// 0	�ղ���������δ��ʼ
// 1	�ӳ�һ��ʱ��,�ر�1¥������
// 2	�Źر�֮���ӳ�һ��ʱ��
// 3	�ӳ�ʱ�䵽������������
// 4	�����ᵽ��¥���ӳ�һ��ʱ��
// 5	�ӳ�ʱ�䵽����2¥������
// 6	�Ŵ�֮�󣬲������

void SubDispatchGo2Floor(void)
{
	switch(SubDispatchGo2FloorSteps)
	{
		case 0:	
			SubDispatchGo2FloorTimer = 0;
		break;
		case 1:	
			if(SubDispatchGo2FloorTimer > 100)
			{
				if(sensorDoorbelow == 0)
				{
					SubDispatchGo2FloorTimer = 0;
					SubDispatchGo2FloorSteps = 3;
				}
				else
				{
					DoorClose = 0;
					DoorFloor1 = 0;
					SubDispatchGo2FloorSteps ++;
				}
			}
		break;
		case 2:	
			if(sensorDoorbelow == 0)
			{
				DoorClose = 1;
				DoorFloor1 = 1;
				SubDispatchGo2FloorTimer = 0;
				SubDispatchGo2FloorSteps ++;
			}
		break;
		case 3:	
			if(SubDispatchGo2FloorTimer > 100)
			{
				BoxUp = 0;
				ledDS151  = 1; //�ر�1��ָʾ��
				ledS  = 0; //����ָʾ��
				SubDispatchGo2FloorSteps ++;
			}
		break;
		case 4:	
			if(sensorFloor2 == 0)
			{
				BoxUp = 1;
				ledDS152 = 0; //��2��ָʾ��
				ledS  = 1; //����ָʾ��
				SubDispatchGo2FloorTimer = 0;
				SubDispatchGo2FloorSteps ++;
			}
		break;
		case 5:	
			if(SubDispatchGo2FloorTimer > 100)
			{
				DoorOpen = 0;
				DoorFloor2 = 0;
				SubDispatchGo2FloorSteps ++;
			}
		break;
		case 6:	
			if(sensorDoortop == 1)
			{
				DoorOpen = 1;
				DoorFloor2 = 1;
				SubDispatchGo2FloorSteps = 0;
			}
		break;
		default:
			 _nop_();
	}
}

