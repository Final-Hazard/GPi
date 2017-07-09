#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Constants.h"
#include "Motor.h"

enum Direction{None, Positive, Negative};

typedef struct movement
{
	char arrFlag;
	//delay in microseconds from last movement command
	int delay;
} Movement;

void SetDirection(enum Motor motor, enum Direction direction, Movement *curMovement);
char EncodeDirection(enum Direction directions[NUM_MOTORS]);
void DecodeDirection(char direction, enum Direction out_output[NUM_MOTORS]);

#endif