#include "Config.h"
#include "Interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include "Bresenham.h"
#include "Movement.h"
#include "Motor.h"
#include "MovementStack.h"
#include "Sleep.h"
//#include <WiringPi.h>

int main(int argc, char** args)
{
  if(!ReadConfig())
  {
    printf("Error reading config\n");
    return -1;
  }
	
  if(!SetupWiringPi())
  {
    printf("Wiring pi setup failed\n");
    return -1;
  }

  /*  char *end, *start;
  Point p0, p1;
  start = args[1];
  p0.x = strtof(args[1], &end);
  p0.y = strtof(args[2], &end);
  p0.z = strtof(args[3], &end);
  printf("(%f, %f, %f)\n", p0.x, p0.y, p0.z);*/
  //digitalWrite(motorArr[0][0],1);
  enum MotorPhase phase = 0;
  
  int micros = 1000 * 1000;
  int iters = 10 * 1000 * 1000 / micros;
  for(int i = 0; i < iters; i++)
  {
    StepMotorPositive(MotorZ, &phase);
    Sleep(micros);
  }
  
  
  Reset();
}
