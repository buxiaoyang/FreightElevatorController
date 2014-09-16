#ifndef 		__DISPATCH_H__
#define 		__DISPATCH_H__

extern unsigned char ManiDispatchSteps;
extern unsigned int SubDispatchGo1FloorTimer;
extern unsigned int SubDispatchGo2FloorTimer;

void ManiDispatch(void);	
void checkSensor(void);

#endif