#include "Test.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Constants.h"
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

void CheckResults(Stack *stack, Point *expected, int size)
{
	if(stack == NULL)
	{
		printf("stack is null\n");
		assert(0);
	}
	if(expected == NULL)
	{
		printf("expected array is null\n");
		assert(0);
	}
	if(stack->currentSize != size)
	{
		printf("stack size (%d) is not equal to expected size (%d)\n", stack->currentSize, size);
		assert(stack->currentSize == size);
	}
	Point loc = expected[0];
	int i = 0;
	Movement *mov;
	enum Direction dirs[NUM_MOTORS];
	while((mov = Pop(stack)))
	{
		i++;
		printf("%x\n",mov->arrFlag);
		DecodeDirection(mov->arrFlag, dirs);
		if(dirs[MotorX] == Negative)
			loc.x--;
		else if(dirs[MotorX] == Positive)
			loc.x++;
		if(dirs[MotorY] == Negative)
			loc.y--;
		else if(dirs[MotorY] == Positive)
			loc.y++;
		if(dirs[MotorZ] == Negative)
			loc.z--;
		else if(dirs[MotorZ] == Positive)
			loc.z++;
		printf("expected: (%d, %d, %d) got: (%d, %d, %d)\n", (int)expected[i].x, (int)expected[i].y, 
		(int)expected[i].z, (int)loc.x, (int)loc.y, (int)loc.z);
		assert(expected[i].x == loc.x && expected[i].y == loc.y && expected[i].z == loc.z);
		
		free(mov);
	}
}

void TestNoMove()
{
	Point p0, p1;
	p0.x = 0; p0.y = 0; p0.z = 0;
	p1.x = 0; p1.y = 0; p1.z = 0;
	Stack *stack = CreateStack();
	PlotLine(p0, p1, stack);
	assert(stack->currentSize == 0);
}

void Test1a()
{
	Point p0, p1;
	p0.x = 3.61; p0.y = 4.93; p0.z = 1;
	p1.x = 10.9; p1.y = 7.32; p1.z = 6.58;
	int steps = 7; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) *  (steps + 1));
	arr[0].x = 3 ; arr[0].y = 4; arr[0].z = 1;
	arr[1].x = 4 ; arr[1].y = 5; arr[1].z = 1;
	arr[2].x = 5 ; arr[2].y = 5; arr[2].z = 2;
	arr[3].x = 6 ; arr[3].y = 5; arr[3].z = 2;
	arr[4].x = 7 ; arr[4].y = 6; arr[4].z = 3;
	arr[5].x = 8 ; arr[5].y = 6; arr[5].z = 4;
	arr[6].x = 9 ; arr[6].y = 6; arr[6].z = 5;
	arr[7].x = 10; arr[7].y = 7; arr[7].z = 5;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test2a()
{
	Point p0, p1;
	p0.x = 1.98; p0.y = 7.30; p0.z = 6;
	p1.x = 8.55; p1.y = 3.69; p1.z = 0;
	int steps =  7; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) *  (steps + 1));
	arr[0].x = 1; arr[0].y = 7; arr[0].z = 6;
	arr[1].x = 2; arr[1].y = 7; arr[1].z = 5;
	arr[2].x = 3; arr[2].y = 6; arr[2].z = 5;
	arr[3].x = 4; arr[3].y = 6; arr[3].z = 4;
	arr[4].x = 5; arr[4].y = 5; arr[4].z = 3;
	arr[5].x = 6; arr[5].y = 5; arr[5].z = 2;
	arr[6].x = 7; arr[6].y = 4; arr[6].z = 1;
	arr[7].x = 8; arr[7].y = 3; arr[7].z = 0;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test3a()
{
	Point p0, p1;
	p0.x = 8.42; p0.y = 5.67; p0.z = 5.92;
	p1.x = 1.83; p1.y = 4.85; p1.z = -.53;
	int steps =  7; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) *  (steps + 1));
	arr[0].x = 8; arr[0].y = 5; arr[0].z =  5;
	arr[1].x = 7; arr[1].y = 5; arr[1].z =  5;
	arr[2].x = 6; arr[2].y = 5; arr[2].z =  4;
	arr[3].x = 5; arr[3].y = 5; arr[3].z =  3;
	arr[4].x = 4; arr[4].y = 5; arr[4].z =  2;
	arr[5].x = 3; arr[5].y = 5; arr[5].z =  1;
	arr[6].x = 2; arr[6].y = 4; arr[6].z =  0;
	arr[7].x = 1; arr[7].y = 4; arr[7].z = -1;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test4a()
{
	Point p0, p1;
	p0.x = 6.58; p0.y = 3.42; p0.z = -1.79;
	p1.x = 1.18; p1.y = 7.89; p1.z =  2.69;
	int steps =  5; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) *  (steps + 1));
	arr[0].x = 6; arr[0].y = 3; arr[0].z = -1;
	arr[1].x = 5; arr[1].y = 3; arr[1].z = -1;
	arr[2].x = 4; arr[2].y = 4; arr[2].z = 0;
	arr[3].x = 3; arr[3].y = 5; arr[3].z = 1;
	arr[4].x = 2; arr[4].y = 6; arr[4].z = 2;
	arr[5].x = 1; arr[5].y = 7; arr[5].z = 3;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test5a()
{
	Point p0, p1;
	p0.x = -2.61; p0.y = 1.93; p0.z = 9.22;
	p1.x = 2.90 ; p1.y = 8.32; p1.z = 4.86;
	int steps =  7; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) * (steps + 1));
	arr[0].x = -2; arr[0].y = 1; arr[0].z = 9;
	arr[1].x = -2; arr[1].y = 2; arr[1].z = 9;
	arr[2].x = -1; arr[2].y = 3; arr[2].z = 8;
	arr[3].x =  0; arr[3].y = 4; arr[3].z = 7;
	arr[4].x =  1; arr[4].y = 5; arr[4].z = 7;
	arr[5].x =  1; arr[5].y = 6; arr[5].z = 6;
	arr[6].x =  2; arr[6].y = 7; arr[6].z = 5;
	arr[7].x =  3; arr[7].y = 8; arr[7].z = 5;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test6a()
{
	Point p0, p1;
	p0.x = 6.86; p0.y = 8.52; p0.z = 0;
	p1.x = 9.32; p1.y = 2.27; p1.z = 0;
	int steps =  6; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) * (steps + 1));
	arr[0].x = 6; arr[0].y = 8; arr[0].z = 0;
	arr[1].x = 7; arr[1].y = 7; arr[1].z = 0;
	arr[2].x = 7; arr[2].y = 6; arr[2].z = 0;
	arr[3].x = 7; arr[3].y = 5; arr[3].z = 0;
	arr[4].x = 8; arr[4].y = 4; arr[4].z = 0;
	arr[5].x = 8; arr[5].y = 3; arr[5].z = 0;
	arr[6].x = 9; arr[6].y = 2; arr[6].z = 0;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test7a()
{
	Point p0, p1;
	p0.x = 5.34; p0.y =  4.87; p0.z = 0;
	p1.x = 1.13; p1.y = -2.98; p1.z = 0;
	int steps =  7; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) * (steps + 1));
	arr[0].x = 5; arr[0].y =  4; arr[0].z = 0;
	arr[1].x = 4; arr[1].y =  3; arr[1].z = 0;
	arr[2].x = 4; arr[2].y =  2; arr[2].z = 0;
	arr[3].x = 3; arr[3].y =  1; arr[3].z = 0;
	arr[4].x = 3; arr[4].y =  0; arr[4].z = 0;
	arr[5].x = 2; arr[5].y = -1; arr[5].z = 0;
	arr[6].x = 2; arr[6].y = -2; arr[6].z = 0;
	arr[7].x = 1; arr[7].y = -3; arr[7].z = 0;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test8a()
{
	Point p0, p1;
	p0.x = 3.76; p0.y = 3.94 ; p0.z = 1.84;
	p1.x = 0.11; p1.y = -1.05; p1.z = 4.25;
	int steps =  5; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) * (steps + 1));
	arr[0].x = 3; arr[0].y =  3; arr[0].z = 1;
	arr[1].x = 3; arr[1].y =  2; arr[1].z = 2;
	arr[2].x = 2; arr[2].y =  1; arr[2].z = 2;
	arr[3].x = 1; arr[3].y =  0; arr[3].z = 3;
	arr[4].x = 0; arr[4].y = -1; arr[4].z = 3;
	arr[5].x = 0; arr[5].y = -2; arr[5].z = 4;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}

void Test9a()
{
	Point p0, p1;
	p0.x = 2.51; p0.y = 0.35; p0.z = 0.37;
	p1.x = 5.49; p1.y = 3.30; p1.z = 6.75;
	int steps =  6; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) * (steps + 1));
	arr[0].x = 2; arr[0].y = 0; arr[0].z = 0;
	arr[1].x = 2; arr[1].y = 0; arr[1].z = 1;
	arr[2].x = 3; arr[2].y = 1; arr[2].z = 2;
	arr[3].x = 3; arr[3].y = 1; arr[3].z = 3;
	arr[4].x = 4; arr[4].y = 2; arr[4].z = 4;
	arr[5].x = 4; arr[5].y = 2; arr[5].z = 5;
	arr[6].x = 5; arr[6].y = 2; arr[6].z = 6;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test10a()
{
	Point p0, p1;
	p0.x = 5.53; p0.y = 8.05; p0.z = 9.95;
	p1.x = 9.41; p1.y = 5.53; p1.z = 3.05;
	int steps =  6; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) * (steps + 1));
	arr[0].x = 5; arr[0].y = 8; arr[0].z = 9;
	arr[1].x = 6; arr[1].y = 7; arr[1].z = 8;
	arr[2].x = 6; arr[2].y = 7; arr[2].z = 7;
	arr[3].x = 7; arr[3].y = 6; arr[3].z = 6;
	arr[4].x = 7; arr[4].y = 6; arr[4].z = 5;
	arr[5].x = 8; arr[5].y = 6; arr[5].z = 4;
	arr[6].x = 8; arr[6].y = 5; arr[6].z = 3;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test11a()
{
	Point p0, p1;
	p0.x = 5.06; p0.y = 4.73; p0.z = 6.50;
	p1.x = 3.52; p1.y = 4.41; p1.z = 0.94;
	int steps =  6; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) * (steps + 1));
	arr[0].x = 5; arr[0].y = 4; arr[0].z = 6;
	arr[1].x = 4; arr[1].y = 4; arr[1].z = 5;
	arr[2].x = 4; arr[2].y = 4; arr[2].z = 4;
	arr[3].x = 4; arr[3].y = 4; arr[3].z = 3;
	arr[4].x = 4; arr[4].y = 4; arr[4].z = 2;
	arr[5].x = 3; arr[5].y = 4; arr[5].z = 1;
	arr[6].x = 3; arr[6].y = 4; arr[6].z = 0;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}
void Test12a()
{
	Point p0, p1;
	p0.x = 9.92; p0.y = 9.31; p0.z = -.43;
	p1.x = 7.03; p1.y = 5.94; p1.z = 5.13;
	int steps =  6; Stack *stack = CreateStack();
	Point *arr = malloc(sizeof(Point) * (steps + 1));
	arr[0].x = 9; arr[0].y = 9; arr[0].z = -1;
	arr[1].x = 9; arr[1].y = 9; arr[1].z =  0;
	arr[2].x = 9; arr[2].y = 8; arr[2].z =  1;
	arr[3].x = 8; arr[3].y = 7; arr[3].z =  2;
	arr[4].x = 8; arr[4].y = 7; arr[4].z =  3;
	arr[5].x = 7; arr[5].y = 6; arr[5].z =  4;
	arr[6].x = 7; arr[6].y = 6; arr[6].z =  5;
	PlotLine(p0, p1, stack);
	CheckResults(stack, arr, steps);
	free(arr);
	free(stack);
}

#endif