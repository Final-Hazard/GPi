#include "Config.h"
#include "Interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include "Bresenham.h"
#include "Movement.h"
#include "Motor.h"
#include "MovementStack.h"
#include <time.h>
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
  struct timespec sleepTime;
  sleepTime.tv_sec = 0;
  sleepTime.tv_nsec = 1000 * 1000;
  for(int i = 0; i < 500; i++)
  {
    StepMotorPositive(MotorZ, &phase);
    if(phase > 3) phase = 0;
    nanosleep(&sleepTime, NULL);
  }
  /*
  for(int i = 0; i < 10; i++)
  {
    StepMotorNegative(MotorZ, &phase);
    printf("%d\n", phase);
    if(phase < 0 || phase > 100) phase = 3;
    sleep(1);
    }*/
  Reset();
}
