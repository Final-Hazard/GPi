#include "Movement.h"
#include <stdio.h>

const char MASK = 0x03;
//directions None, Positive, Negative
const char ENCODING[] = {0x00, 0x02, 0x03};

char EncodeDirection(enum Direction directions[NUM_MOTORS])
{
	char encoding = 0;
	char returnValue = 0;
	for(int i = 0; i < NUM_MOTORS; i++)
	{
		if(directions[i] < 0 || directions[i] > NUM_DIRECTIONS)
			printf("Invalid direction enum %d", (int) directions[i]);
		encoding = ENCODING[directions[i]] << (i << 1);
		returnValue = returnValue | encoding;
	}
	return returnValue;
}

void SetDirection(enum Motor motor, enum Direction direction, Movement *curMovement)
{
	if(curMovement == NULL)
	{
		printf("curMovement is null, cannot set direction");
		return;
	}
	char current = curMovement->arrFlag;
	char mask = (char) (MASK << (motor << 1));
	//clear current position
	current = current & ~mask;
	//set new value
	if(direction < 0 || direction > NUM_DIRECTIONS)
		printf("Invalid direction enum %d", direction);
	
	current = current | ENCODING[direction] << (motor << 1);
	curMovement->arrFlag = current;
}

void DecodeDirection(char direction, enum Direction out_output[NUM_MOTORS])
{	
	if(out_output == NULL)
	{
		printf("passed in null out parameter");
		return;
	}
	for(int i = 0; i < NUM_MOTORS; i++)
	{
		char mask = (MASK << (i << 1));
		char value = (direction & mask) >> (i << 1);
		switch(value)
		{
			case 0x00:
				out_output[i] = None;
				break;
			case 0x02:
				out_output[i] = Positive;
				break;
			case 0x03:
				out_output[i] = Negative;
				break;
			default:
				printf("Problem decoding Direction character\n");
		}
	}
}