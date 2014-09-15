#include <reg52.h>
#include <parameter.h>
#include <intrins.h>
#include <dispatch.h>

unsigned char ManiDispatchSteps = 20;

unsigned char SubDispatchSteps = 20; 	


void ManiDispatch(void)
{
	switch(ManiDispatchSteps)
	{
		case 0: 
			
		break;
		case 1:
			
		break;
		default:
			 _nop_();
	}
}


void SubDispatch(void)
{
	switch(SubDispatchSteps)
	{
		case 0:	
			
		break;
		case 1:	
		
		break;
		default:
			 _nop_();
	}
}