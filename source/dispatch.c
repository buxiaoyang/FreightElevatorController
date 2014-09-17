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

/*主调度程序*/
// 0	空操作，
// 1	电梯厢到1楼
// 3	电梯厢到2楼

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
			Led601 = 0;	//一楼按钮指示灯；
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
			Led602 = 0;	//二楼按钮指示灯
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

/*电梯厢到一楼调度程序*/
// 0	空操作，调度未开始
// 1	延迟一定时间,关闭2楼电梯门
// 2	门关闭之后，延迟一段时间
// 3	延迟时间到，电梯厢向下
// 4	电梯厢到一楼，延迟一段时间
// 5	延迟时间到，打开1楼电梯门
// 6	门打开之后，操作完成
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
				ledDS152 = 1; //关闭2层指示灯
				ledX = 0;  //电梯向下指示灯
				SubDispatchGo1FloorSteps ++;
			}
		break;
		case 4:	
			if(sensorFloor1 == 0)
			{
				BoxDown = 1;
				ledDS151  = 0; //打开1层指示灯
				ledX = 1;  //电梯向下指示灯
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


/*电梯厢到二楼调度程序*/
// 0	空操作，调度未开始
// 1	延迟一定时间,关闭1楼电梯门
// 2	门关闭之后，延迟一段时间
// 3	延迟时间到，电梯厢向上
// 4	电梯厢到二楼，延迟一段时间
// 5	延迟时间到，打开2楼电梯门
// 6	门打开之后，操作完成

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
				ledDS151  = 1; //关闭1层指示灯
				ledS  = 0; //向上指示灯
				SubDispatchGo2FloorSteps ++;
			}
		break;
		case 4:	
			if(sensorFloor2 == 0)
			{
				BoxUp = 1;
				ledDS152 = 0; //打开2层指示灯
				ledS  = 1; //向上指示灯
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

