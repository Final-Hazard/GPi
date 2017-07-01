//#include <iostream>
//#include <wiringPi.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "Bresenham.h"
//TODO: remove reference to motor.h instead return a list of commands from plotline function
#include "Motor.h"
#ifdef DEBUG
#include "Test.h"
#include <assert.h>
#endif
//using namespace std;

bool g_debug = true;

int main(){return 0;}

void PlotLineInternal(Point, Point, void(*)(void), void(*)(void), void(*)(void));
//these functions will move the motor in one step in the specified direction
void StepXp();
void StepYp();
void StepZp();
void StepXn();
void StepYn();
void StepZn();

///Call this function with any values you want, it will automatically translate to octant 1
///and submit to the plot line function
void PlotLine(Point p0, Point p1)
{
	//find largest delta to use as driving axis
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	float dz = p1.z - p0.z;
	float adx = fabs(dx);
	float ady = fabs(dy);
	float adz = fabs(dz);
	//arguments to plotline internal
	//the points get mixed around to ensure that plot line internal always operates on octant 1
	Point arg0, arg1;
	//set the step function arguments
	void (*stepX)(void), (*stepY)(void), (*stepZ)(void);
	
	
	if(adx >= ady && adx >= adz)
	{//driving axis = dx; therefore the slope is -1 < m < 1
		if(p0.x <= p1.x)
		{//Case 1 and 2, X:
			stepX = &StepXp;
			arg0.x = p0.x;
			arg1.x = p1.x;
		}
		else
		{//Case 3 and 4, X:
			stepX = &StepXn;
			arg0.x = -p0.x;
			arg1.x = -p1.x;
		}
		if(p0.y <= p1.y)
		{//Case 1 and 4, Y:
			stepY = &StepYp;
			arg0.y = p0.y;
			arg1.y = p1.y;
		}
		else
		{//Case 2 and 3, Y:
			stepY = &StepYn;
			arg0.y = -p0.y;
			arg1.y = -p1.y;
		}
		if(p0.z <= p1.z)
		{//Case 1 and 4, Z:
			stepZ = &StepZp;
			arg0.z = p0.z;
			arg1.z = p1.z;
		}
		else
		{//Case 2 and 3, Z:
			stepZ = &StepZn;
			arg0.z = -p0.z;
			arg1.z = -p1.z;
		}
	}
	if(ady >= adx && ady >= adz)
	{//driving axis = dy; therefore slope is m < -1 or m > 1
		if(p0.y <= p1.y)
		{//Case 5 and 8, Y:
			stepX = &StepYp;
			arg0.x = p0.y;
			arg1.x = p1.y;
		}
		else
		{//Case 6 and 7, Y:
			stepX = &StepYn;
			arg0.x = -p0.y;
			arg1.x = -p1.y;
		}
		if(p0.x <= p1.x)
		{//Case 5 and 6, X:
			stepY = &StepXp;
			arg0.y = p0.x;
			arg1.y = p1.x;
		}
		else
		{//Case 7 and 8, X:
			stepY = &StepXn;
			arg0.y = -p0.x;
			arg1.y = -p1.x;
		}
		if(p0.z <= p1.z)
		{//Case 5 and 6, Z:
			stepZ = &StepZp;
			arg0.z = p0.z;
			arg1.z = p1.z;
		}
		else
		{//Case 7 and 8, Z:
			stepZ = &StepZn;
			arg0.z = -p0.z;
			arg1.z = -p1.z;
		}
	}
	if(adz >= adx && adz >= ady)
	{//driving axis = dz
		if(p0.z <= p1.z)
		{//Case 5 and 8, Z:
			stepX = &StepZp;
			arg0.x = p0.z;
			arg1.x = p1.z;
		}
		else
		{//Case 6 and 7, Z:
			stepX = &StepZn;
			arg0.x = -p0.z;
			arg1.x = -p1.z;
		}
		if(p0.x <= p1.x)
		{//Case 6 and 7, X:
			stepZ = &StepXp;
			arg0.z = p0.x;
			arg1.z = p1.x;
		}
		else
		{//Case 5 and 8, X:
			stepZ = &StepXn;
			arg0.z = -p0.x;
			arg1.z = -p1.x;
		}
		if(p0.y <= p1.y)
		{//Case 6 and 7, Y:
			stepY = &StepYp;
			arg0.y = p0.y;
			arg1.y = p1.y;
		}
		else
		{//Case 5 and 8, Y;
			stepY = &StepYn;
			arg0.y = -p0.y;
			arg1.y = -p1.y;
		}
	}
	PlotLineInternal(arg0, arg1, stepX, stepY, stepZ);
}

///Do not use this method except from PlotLine method
///These are labeled as x, y, and z axes but in reality they are swapped around in the
///PlotLine function. The only thing to note is that the x values are always the driving
///axis.
void PlotLineInternal(Point p0, Point p1, void (*stepX)(void), void (*stepY)(void), void (*stepZ)(void))
{
	if(g_debug)
		printf("(%.2f, %.2f, %.2f) -> (%.2f, %.2f, %.2f)\n", p0.x, p0.y, p0.z, p1.x, p1.y, p1.z);
	int SCALE_FACTOR = 2 << 12;
	//dx, dy, dz always positive
	int dx = (int) (SCALE_FACTOR * (p1.x - p0.x));
	int dy = (int) (SCALE_FACTOR * (p1.y - p0.y));
	int dz = (int) (SCALE_FACTOR * (p1.z - p0.z));
	bool bDy = dy > 0;
	bool bDz = dz > 0;
	float xOffset = p0.x - ffloor(p0.x);
	float yOffset = p0.y - ffloor(p0.y);
	float zOffset = p0.z - ffloor(p0.z);
	int daLoops = ffloor(p1.x) - ffloor(p0.x);
	#ifdef DEBUG
	printf("expected %d steps, got %d\n", g_steps, daLoops);
	assert(g_steps == daLoops);
	#endif
	
	int yError = ffloor(dy * (1 - xOffset) - dx * (1 - yOffset));
	int zError = ffloor(dz * (1 - xOffset) - dx * (1 - zOffset));
	if(g_debug)
	{
		printf("xoff:%f, yoff:%f\n", xOffset, yOffset);
		printf("dx:%d dy:%d dz:%d\n", dx, dy, dz);
		printf("yerror:%d, zerror:%d\n", yError, zError);
	}
	for(int i = 0; i < daLoops; i++)
	{
		#ifdef DEBUG
		printf("expected: (%d, %d, %d) got: (%d, %d, %d)\n", (int)g_arr[i].x, (int)g_arr[i].y, (int)g_arr[i].z, g_x, g_y, g_z);
		assert(g_x == g_arr[i].x && g_y == g_arr[i].y && g_z == g_arr[i].z);
		if(g_debug)
			printf("%d - (%d,%d,%d)\n", i, g_x, g_y, g_z);
		#endif
		
		(*stepX)();
		if(yError >= 0 && bDy)
		{
			(*stepY)();
			//dx is always driving axis
			yError -= dx;
		}
		if(zError >= 0 && bDz)
		{
			(*stepZ)();
			//dx is always driving axis
			zError -= dx;
		}
		yError += dy;
		zError += dz;
		if(g_debug)
			printf("yerror:%d, zerror:%d\n",yError, zError);
	}
	#ifdef DEBUG
	if(g_debug)
		printf("(%d,%d,%d)\n", g_x, g_y, g_z);
	if(daLoops > 0)
	{
		printf("expected: (%d, %d, %d) got: (%d, %d, %d)\n", (int)g_arr[daLoops].x, (int)g_arr[daLoops].y, (int)g_arr[daLoops].z, g_x, g_y, g_z);
		assert(g_x == g_arr[daLoops].x && g_y == g_arr[daLoops].y && g_z == g_arr[daLoops].z);
	}
	#endif
}

#ifdef DEBUG
//these functions simulate moving the motor in one step in the specified direction
void StepXp(){g_x++;}
void StepYp(){g_y++;}
void StepZp(){g_z++;}
void StepXn(){g_x--;}
void StepYn(){g_y--;}
void StepZn(){g_z--;}
#else
void StepXp(){StepMotorPositive(MotorX, g_MotorXPhase);}
void StepYp(){StepMotorPositive(MotorY, g_MotorYPhase);}
void StepZp(){StepMotorPositive(MotorZ, g_MotorZPhase);}
void StepXn(){StepMotorNegative(MotorX, g_MotorXPhase);}
void StepYn(){StepMotorNegative(MotorY, g_MotorYPhase);}
void StepZn(){StepMotorNegative(MotorZ, g_MotorZPhase);}
#endif

int ffloor(float f)
{
	return f >= 0 ? (int) f : ((int) (f - 1));
}