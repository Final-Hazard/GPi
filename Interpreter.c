#include "Config.h"
#include <stdio.h>
//#include <WiringPi.h>

int main()
{
	if(ReadConfig() != 0)
		printf("Error reading config\n");
	
	//PrintConfig();
	
	
}