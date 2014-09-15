/***************************************************************************/
// 程序：清洗设备控制器
// 模块：参数头文件
// 文件：parameter.h
// 作者：卜晓旸
// 版本：V0.02
// 日期：2013年11月8日
// 功能：参数头文件
// 芯片：STC12C5A60S2
// 编译：Keil uVision3 V3.90
/***************************************************************************/

#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <reg52.h>
// 扩展内存口
sfr AUXR = 0x8e;
sfr P4 = 0xE8;
/***************************************************************************/
// 引脚定义
/***************************************************************************/
//Input Signal									   			 
sbit sensorFloor1 = P3^2;        // 线头：101     1层状态感应器	       X0
sbit sensorFloor2 = P3^3;        // 线头：102     2层状态感应器		   X1
sbit sensorDoortop = P0^2;       // 线头：KMW   1.2层门上部感应器	   X2
sbit sensorDoorbelow = P0^3;     // 线头：GMW   1.2层门下部感应器 	   X3
sbit sensorLimit  = P0^4;         // 线头：SWX    2层限位开关		   X4	
sbit sensorButton1 = P0^5;        // 线头：301      1.2层面板数字1按钮  X5
sbit sensorButton2  = P0^6;       // 线头：302      1.2层面板数字2按钮  X6
sbit sensorF2 = P4^0;             // 线头：F2      假如油泵工作，此信号处于没有输出状态 X11
sbit sensorEmergency = P0^7;      // 线头;JT        假如有高电位输入，全部输出停止工作            X7
//Output Signal 
sbit Dooropen = P4^2;             //激活卷门开门输出         Y0
sbit Doorclose = P4^3;            //激活卷门关门输出         Y1
sbit Doorfloor1   = P3^4;         //一楼卷门激活             Y2
sbit Doorfloor2 = P3^5;	          //二楼卷门激活             Y3
sbit BoxUp   = P3^6;              //油泵电梯轿厢向上推       Y4
sbit Boxdown = P3^7;              //油泵电梯轿厢向下推       Y5
//================================================
sbit ledDS151  = P2^0;            //电梯指示灯1              Y6
sbit ledDS152 = P2^1;             //电梯指示灯2              Y7
sbit ledS  = P2^2;                //指示灯 箭头向上      	 Y10
sbit ledX = P2^3;                 //指示灯 箭头向下	     	 Y11
sbit Led601  = P2^4;              //指示灯按钮①             Y12
sbit Led602 = P2^5;               //指示灯按钮②             Y13

#endif
