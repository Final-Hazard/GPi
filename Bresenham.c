#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "Bresenham.h"
#include "Movement.h"
#ifdef DEBUG
#include "Test.h"
#endif
//using namespace std;

bool g_debug = true;

void PlotLineInternal(Point, Point, Stack *movementStack, void(*)(Movement*), void(*)(Movement*), void(*)(Movement*));
//these functions will move the motor in one step in the specified direction
void StepXp(Movement *movement);
void StepYp(Movement *movement);
void StepZp(Movement *movement);
void StepXn(Movement *movement);
void StepYn(Movement *movement);
void StepZn(Movement *movement);

///Call this function with any values you want, it will automatically translate to octant 1
///and submit to the plot line function
void PlotLine(Point p0, Point p1, Stack *movementStack)
{
	if(movementStack == NULL)
	{
		printf("Movement stack is null");
		return;
	}
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
	void (*stepX)(Movement*), (*stepY)(Movement*), (*stepZ)(Movement*);
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
	PlotLineInternal(arg0, arg1, movementStack, stepX, stepY, stepZ);
}

///Do not use this method except from PlotLine method
///These are labeled as x, y, and z axes but in reality they are swapped around in the
///PlotLine function. The only thing to note is that the x values are always the driving
///axis.
void PlotLineInternal(Point p0, Point p1, Stack* movementStack, void (*stepX)(Movement*), void (*stepY)(Movement*), void (*stepZ)(Movement*))
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
	
	int yError = ffloor(dy * (1 - xOffset) - dx * (1 - yOffset));
	int zError = ffloor(dz * (1 - xOffset) - dx * (1 - zOffset));
	if(g_debug)
	{
		printf("xoff:%f, yoff:%f\n", xOffset, yOffset);
		printf("dx:%d dy:%d dz:%d\n", dx, dy, dz);
		printf("yerror:%d, zerror:%d\n", yError, zError);
	}
	/*
	Movement *mov = malloc(sizeof(Movement));
	if(mov == NULL)
	{
		printf("Unable to allocate memory for movement data\n");
		return;
	}*/
	for(int i = 0; i < daLoops; i++)
	{
		Movement *mov = malloc(sizeof(Movement));
		if(mov == NULL)
		{
			printf("Unable to allocate memory for movement\n");
			return;
		}
		mov->arrFlag = 0;
		(*stepX)(mov);
		if(yError >= 0 && bDy)
		{
			(*stepY)(mov);
			//dx is always driving axis
			yError -= dx;
		}
		if(zError >= 0 && bDz)
		{
			(*stepZ)(mov);
			//dx is always driving axis
			zError -= dx;
		}
		yError += dy;
		zError += dz;
		Push(movementStack, mov);
	}
}


void StepXp(Movement *movement){SetDirection(MotorX, Positive, movement);}
void StepYp(Movement *movement){SetDirection(MotorY, Positive, movement);}
void StepZp(Movement *movement){SetDirection(MotorZ, Positive, movement);}
void StepXn(Movement *movement){SetDirection(MotorX, Negative, movement);}
void StepYn(Movement *movement){SetDirection(MotorY, Negative, movement);}
void StepZn(Movement *movement){SetDirection(MotorZ, Negative, movement);}

int ffloor(float f)
{
	return f >= 0 ? (int) f : ((int) (f - 1));
}