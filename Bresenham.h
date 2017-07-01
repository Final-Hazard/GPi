#ifndef BRESENHAM_H
#define BRESENHAM_H

typedef struct point
{
	float x;
	float y;
	float z;
} Point;

int ffloor(float f);
void PlotLine(Point, Point);

#endif