#include "Motor.h"

const int MOTOR_PHASE_MIN = 0;
const int MOTOR_PHASE_MAX = 3;
const int MOTOR_PHASE_ARRAY[4][4] = {{1, 0, 1, 0},
									{1, 0, 0, 1},
									{0, 1, 0, 1},
									{0, 1, 1, 0}};

void SetMotorOutputs(enum Motor motor, const int* output){}

//drive the given motor 1 step in the Positive direction
void StepMotorPositive(enum Motor motor, enum MotorPhase currrentPhase)
{
	int phase = (int) currrentPhase;
	phase++;
	if(phase > MOTOR_PHASE_MAX)
		phase = MOTOR_PHASE_MIN;
	SetMotorOutputs(motor, MOTOR_PHASE_ARRAY[phase]);
}

//drive the motor 1 step in the Negative direction
void StepMotorNegative(enum Motor motor, enum MotorPhase currrentPhase)
{
	int phase = (int) currrentPhase;
	phase--;
	if(phase < MOTOR_PHASE_MIN)
		phase = MOTOR_PHASE_MAX;
	SetMotorOutputs(motor, MOTOR_PHASE_ARRAY[phase]);
}