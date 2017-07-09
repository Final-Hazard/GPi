#include "Config.h"
#include <stdio.h>
#include <stdlib.h>
#include "Movement.h"
#include "Motor.h"
#include "MovementStack.h"
//#include <WiringPi.h>

int main()
{
	if(ReadConfig() != 0)
		printf("Error reading config\n");
	
	SetupWiringPi();
}