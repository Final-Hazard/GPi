#ifndef BRESENHAM_H
#define BRESENHAM_H
#include "MovementStack.h"

typedef struct point
{
	float x;
	float y;
	float z;
} Point;

int ffloor(float f);
void PlotLine(Point start, Point end, Stack* movementStack);

#endif