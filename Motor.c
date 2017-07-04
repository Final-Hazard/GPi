#include "Motor.h"
//#include <WiringPi.h>

const int MOTOR_PHASE_MIN = 0;
const int MOTOR_PHASE_MAX = 3;
const int MOTOR_PHASE_ARRAY[NUM_MOTOR_PHASES][NUM_MOTOR_CONTROL_PINS] = 
{{1, 0, 1, 0},
 {1, 0, 0, 1},
 {0, 1, 0, 1},
 {0, 1, 1, 0}};

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

void DigitalWrite(int a, int b){}

void SetMotorOutputs(enum Motor motor, const int output[NUM_MOTOR_CONTROL_PINS])
{
	for(int i = 0; i < NUM_MOTOR_CONTROL_PINS; i++)
		DigitalWrite(motorArr[motor][i], output[i]);
}