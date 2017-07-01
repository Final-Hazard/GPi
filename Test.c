#include "Test.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#ifdef DEBUG

int main()
{
	Test();
	return 0;
}

void Test()
{
	printf("TestNoMove();\n");
	TestNoMove();
	printf("===Test1a();===\n");
	Test1a();
	printf("===Test2a();===\n");
	Test2a();
	printf("===Test3a();===\n");
	Test3a();
	printf("===Test4a();===\n");
	Test4a();
	printf("===Test5a();===\n");
	Test5a();
	printf("===Test6a();===\n");
	Test6a();
	printf("===Test7a();===\n");
	Test7a();
	printf("===Test8a();===\n");
	Test8a();
	printf("===Test9a();===\n");
	Test9a();
	printf("===Test10a();===\n");
	Test10a();
	printf("===Test11a();===\n");
	Test11a();
	printf("===Test12a();===\n");
	Test12a();
	
	printf("========================================\n");
	printf("            Testing Complete            \n");
	printf("========================================\n");
}

void TestNoMove()
{
	Point p0, p1;
	p0.x = 0; p0.y = 0; p0.z = 0;
	p1.x = 0; p1.y = 0; p1.z = 0;
	g_x = g_y = g_z = 0; g_steps = 0;
	PlotLine(p0, p1);
	assert(g_x == 0 && g_y == 0 && g_z == 0);
}

void Test1a()
{
	Point p0, p1;
	p0.x = 3.61; p0.y = 4.93; p0.z = 1;
	p1.x = 10.9; p1.y = 7.32; p1.z = 6.58;
	g_x = 3; g_y = 4; g_z = 1; g_steps = 7;
	g_arr = malloc(sizeof(Point) *  (g_steps + 1));
	g_arr[0].x = 3 ; g_arr[0].y = 4; g_arr[0].z = 1;
	g_arr[1].x = 4 ; g_arr[1].y = 5; g_arr[1].z = 1;
	g_arr[2].x = 5 ; g_arr[2].y = 5; g_arr[2].z = 2;
	g_arr[3].x = 6 ; g_arr[3].y = 5; g_arr[3].z = 2;
	g_arr[4].x = 7 ; g_arr[4].y = 6; g_arr[4].z = 3;
	g_arr[5].x = 8 ; g_arr[5].y = 6; g_arr[5].z = 4;
	g_arr[6].x = 9 ; g_arr[6].y = 6; g_arr[6].z = 5;
	g_arr[7].x = 10; g_arr[7].y = 7; g_arr[7].z = 5;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test2a()
{
	Point p0, p1;
	p0.x = 1.98; p0.y = 7.30; p0.z = 6;
	p1.x = 8.55; p1.y = 3.69; p1.z = 0;
	g_x = 1; g_y = 7; g_z = 6; g_steps = 7;
	g_arr = malloc(sizeof(Point) *  (g_steps + 1));
	g_arr[0].x = 1; g_arr[0].y = 7; g_arr[0].z = 6;
	g_arr[1].x = 2; g_arr[1].y = 7; g_arr[1].z = 5;
	g_arr[2].x = 3; g_arr[2].y = 6; g_arr[2].z = 5;
	g_arr[3].x = 4; g_arr[3].y = 6; g_arr[3].z = 4;
	g_arr[4].x = 5; g_arr[4].y = 5; g_arr[4].z = 3;
	g_arr[5].x = 6; g_arr[5].y = 5; g_arr[5].z = 2;
	g_arr[6].x = 7; g_arr[6].y = 4; g_arr[6].z = 1;
	g_arr[7].x = 8; g_arr[7].y = 3; g_arr[7].z = 0;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test3a()
{
	Point p0, p1;
	p0.x = 8.42; p0.y = 5.67; p0.z = 5.92;
	p1.x = 1.83; p1.y = 4.85; p1.z = -.53;
	g_x = 8; g_y = 5; g_z =5; g_steps = 7;
	g_arr = malloc(sizeof(Point) *  (g_steps + 1));
	g_arr[0].x = 8; g_arr[0].y = 5; g_arr[0].z =  5;
	g_arr[1].x = 7; g_arr[1].y = 5; g_arr[1].z =  5;
	g_arr[2].x = 6; g_arr[2].y = 5; g_arr[2].z =  4;
	g_arr[3].x = 5; g_arr[3].y = 5; g_arr[3].z =  3;
	g_arr[4].x = 4; g_arr[4].y = 5; g_arr[4].z =  2;
	g_arr[5].x = 3; g_arr[5].y = 5; g_arr[5].z =  1;
	g_arr[6].x = 2; g_arr[6].y = 4; g_arr[6].z =  0;
	g_arr[7].x = 1; g_arr[7].y = 4; g_arr[7].z = -1;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test4a()
{
	Point p0, p1;
	p0.x = 6.58; p0.y = 3.42; p0.z = -1.79;
	p1.x = 1.18; p1.y = 7.89; p1.z =  2.69;
	g_x = 6; g_y = 3; g_z = -1; g_steps = 5;
	g_arr = malloc(sizeof(Point) *  (g_steps + 1));
	g_arr[0].x = 6; g_arr[0].y = 3; g_arr[0].z = -1;
	g_arr[1].x = 5; g_arr[1].y = 3; g_arr[1].z = -1;
	g_arr[2].x = 4; g_arr[2].y = 4; g_arr[2].z = 0;
	g_arr[3].x = 3; g_arr[3].y = 5; g_arr[3].z = 1;
	g_arr[4].x = 2; g_arr[4].y = 6; g_arr[4].z = 2;
	g_arr[5].x = 1; g_arr[5].y = 7; g_arr[5].z = 3;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test5a()
{
	Point p0, p1;
	p0.x = -2.61; p0.y = 1.93; p0.z = 9.22;
	p1.x = 2.90 ; p1.y = 8.32; p1.z = 4.86;
	g_x = -2; g_y = 1; g_z = 9; g_steps = 7;
	g_arr = malloc(sizeof(Point) * (g_steps + 1));
	g_arr[0].x = -2; g_arr[0].y = 1; g_arr[0].z = 9;
	g_arr[1].x = -2; g_arr[1].y = 2; g_arr[1].z = 9;
	g_arr[2].x = -1; g_arr[2].y = 3; g_arr[2].z = 8;
	g_arr[3].x =  0; g_arr[3].y = 4; g_arr[3].z = 7;
	g_arr[4].x =  1; g_arr[4].y = 5; g_arr[4].z = 7;
	g_arr[5].x =  1; g_arr[5].y = 6; g_arr[5].z = 6;
	g_arr[6].x =  2; g_arr[6].y = 7; g_arr[6].z = 5;
	g_arr[7].x =  3; g_arr[7].y = 8; g_arr[7].z = 5;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test6a()
{
	Point p0, p1;
	p0.x = 6.86; p0.y = 8.52; p0.z = 0;
	p1.x = 9.32; p1.y = 2.27; p1.z = 0;
	g_x = 6; g_y = 8; g_z = 0; g_steps = 6;
	g_arr = malloc(sizeof(Point) * (g_steps + 1));
	g_arr[0].x = 6; g_arr[0].y = 8; g_arr[0].z = 0;
	g_arr[1].x = 7; g_arr[1].y = 7; g_arr[1].z = 0;
	g_arr[2].x = 7; g_arr[2].y = 6; g_arr[2].z = 0;
	g_arr[3].x = 7; g_arr[3].y = 5; g_arr[3].z = 0;
	g_arr[4].x = 8; g_arr[4].y = 4; g_arr[4].z = 0;
	g_arr[5].x = 8; g_arr[5].y = 3; g_arr[5].z = 0;
	g_arr[6].x = 9; g_arr[6].y = 2; g_arr[6].z = 0;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test7a()
{
	Point p0, p1;
	p0.x = 5.34; p0.y =  4.87; p0.z = 0;
	p1.x = 1.13; p1.y = -2.98; p1.z = 0;
	g_x = 5; g_y = 4; g_z = 0; g_steps = 7;
	g_arr = malloc(sizeof(Point) * (g_steps + 1));
	g_arr[0].x = 5; g_arr[0].y =  4; g_arr[0].z = 0;
	g_arr[1].x = 4; g_arr[1].y =  3; g_arr[1].z = 0;
	g_arr[2].x = 4; g_arr[2].y =  2; g_arr[2].z = 0;
	g_arr[3].x = 3; g_arr[3].y =  1; g_arr[3].z = 0;
	g_arr[4].x = 3; g_arr[4].y =  0; g_arr[4].z = 0;
	g_arr[5].x = 2; g_arr[5].y = -1; g_arr[5].z = 0;
	g_arr[6].x = 2; g_arr[6].y = -2; g_arr[6].z = 0;
	g_arr[7].x = 1; g_arr[7].y = -3; g_arr[7].z = 0;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test8a()
{
	Point p0, p1;
	p0.x = 3.76; p0.y = 3.94 ; p0.z = 1.84;
	p1.x = 0.11; p1.y = -1.05; p1.z = 4.25;
	g_x = 3; g_y = 3; g_z = 1; g_steps = 5;
	g_arr = malloc(sizeof(Point) * (g_steps + 1));
	g_arr[0].x = 3; g_arr[0].y =  3; g_arr[0].z = 1;
	g_arr[1].x = 3; g_arr[1].y =  2; g_arr[1].z = 2;
	g_arr[2].x = 2; g_arr[2].y =  1; g_arr[2].z = 2;
	g_arr[3].x = 1; g_arr[3].y =  0; g_arr[3].z = 3;
	g_arr[4].x = 0; g_arr[4].y = -1; g_arr[4].z = 3;
	g_arr[5].x = 0; g_arr[5].y = -2; g_arr[5].z = 4;
	PlotLine(p0, p1);
	free(g_arr);
}

void Test9a()
{
	Point p0, p1;
	p0.x = 2.51; p0.y = 0.35; p0.z = 0.37;
	p1.x = 5.49; p1.y = 3.30; p1.z = 6.75;
	g_x = 2; g_y = 0; g_z = 0; g_steps = 6;
	g_arr = malloc(sizeof(Point) * (g_steps + 1));
	g_arr[0].x = 2; g_arr[0].y = 0; g_arr[0].z = 0;
	g_arr[1].x = 2; g_arr[1].y = 0; g_arr[1].z = 1;
	g_arr[2].x = 3; g_arr[2].y = 1; g_arr[2].z = 2;
	g_arr[3].x = 3; g_arr[3].y = 1; g_arr[3].z = 3;
	g_arr[4].x = 4; g_arr[4].y = 2; g_arr[4].z = 4;
	g_arr[5].x = 4; g_arr[5].y = 2; g_arr[5].z = 5;
	g_arr[6].x = 5; g_arr[6].y = 2; g_arr[6].z = 6;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test10a()
{
	Point p0, p1;
	p0.x = 5.53; p0.y = 8.05; p0.z = 9.95;
	p1.x = 9.41; p1.y = 5.53; p1.z = 3.05;
	g_x = 5; g_y = 8; g_z = 9; g_steps = 6;
	g_arr = malloc(sizeof(Point) * (g_steps + 1));
	g_arr[0].x = 5; g_arr[0].y = 8; g_arr[0].z = 9;
	g_arr[1].x = 6; g_arr[1].y = 7; g_arr[1].z = 8;
	g_arr[2].x = 6; g_arr[2].y = 7; g_arr[2].z = 7;
	g_arr[3].x = 7; g_arr[3].y = 6; g_arr[3].z = 6;
	g_arr[4].x = 7; g_arr[4].y = 6; g_arr[4].z = 5;
	g_arr[5].x = 8; g_arr[5].y = 6; g_arr[5].z = 4;
	g_arr[6].x = 8; g_arr[6].y = 5; g_arr[6].z = 3;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test11a()
{
	Point p0, p1;
	p0.x = 5.06; p0.y = 4.73; p0.z = 6.50;
	p1.x = 3.52; p1.y = 4.41; p1.z = 0.94;
	g_x = 5; g_y = 4; g_z = 6; g_steps = 6;
	g_arr = malloc(sizeof(Point) * (g_steps + 1));
	g_arr[0].x = 5; g_arr[0].y = 4; g_arr[0].z = 6;
	g_arr[1].x = 4; g_arr[1].y = 4; g_arr[1].z = 5;
	g_arr[2].x = 4; g_arr[2].y = 4; g_arr[2].z = 4;
	g_arr[3].x = 4; g_arr[3].y = 4; g_arr[3].z = 3;
	g_arr[4].x = 4; g_arr[4].y = 4; g_arr[4].z = 2;
	g_arr[5].x = 3; g_arr[5].y = 4; g_arr[5].z = 1;
	g_arr[6].x = 3; g_arr[6].y = 4; g_arr[6].z = 0;
	PlotLine(p0, p1);
	free(g_arr);
}
void Test12a()
{
	Point p0, p1;
	p0.x = 9.92; p0.y = 9.31; p0.z = -.43;
	p1.x = 7.03; p1.y = 5.94; p1.z = 5.13;
	g_x = 9; g_y = 9; g_z = -1; g_steps = 6;
	g_arr = malloc(sizeof(Point) * (g_steps + 1));
	g_arr[0].x = 9; g_arr[0].y = 9; g_arr[0].z = -1;
	g_arr[1].x = 9; g_arr[1].y = 9; g_arr[1].z =  0;
	g_arr[2].x = 9; g_arr[2].y = 8; g_arr[2].z =  1;
	g_arr[3].x = 8; g_arr[3].y = 7; g_arr[3].z =  2;
	g_arr[4].x = 8; g_arr[4].y = 7; g_arr[4].z =  3;
	g_arr[5].x = 7; g_arr[5].y = 6; g_arr[5].z =  4;
	g_arr[6].x = 7; g_arr[6].y = 6; g_arr[6].z =  5;
	PlotLine(p0, p1);
	free(g_arr);
}

#endif