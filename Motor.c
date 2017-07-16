#include "Motor.h"
#include "Config.h"
#include <wiringPi.h>

const int MOTOR_PHASE_MIN = 0;
const int MOTOR_PHASE_MAX = 3;
const int MOTOR_PHASE_ARRAY[NUM_MOTOR_PHASES][NUM_MOTOR_CONTROL_PINS] = 
{{1, 0, 1, 0},
 {1, 0, 0, 1},
 {0, 1, 0, 1},
 {0, 1, 1, 0}};

//drive the given motor 1 step in the Positive direction
void StepMotorPositive(enum Motor motor, enum MotorPhase *currentPhase)
{
  //the enum may be signed or unsigned (yay!)
  int phase = (int) *currentPhase;
  phase++;
  if(phase > MOTOR_PHASE_MAX)
    phase = MOTOR_PHASE_MIN;
  *currentPhase = phase;
  SetMotorOutputs(motor, MOTOR_PHASE_ARRAY[phase]);
}

//drive the motor 1 step in the Negative direction
void StepMotorNegative(enum Motor motor, enum MotorPhase *currentPhase)
{
  int phase = (int) *currentPhase;
  phase--;
  if(phase < MOTOR_PHASE_MIN || phase > MOTOR_PHASE_MAX)
    phase = MOTOR_PHASE_MAX;
  *currentPhase = phase;
  SetMotorOutputs(motor, MOTOR_PHASE_ARRAY[phase]);
}

void SetMotorOutputs(enum Motor motor, const int output[NUM_MOTOR_CONTROL_PINS])
{
  for(int i = 0; i < NUM_MOTOR_CONTROL_PINS; i++)
    digitalWrite(motorArr[motor][i], output[i]);
}

void Reset()
{
  for(int i = 0; i < NUM_MOTOR_CONTROL_PINS; i++)
  {
    digitalWrite(motorArr[0][i], 0);
    digitalWrite(motorArr[1][i], 0);
    digitalWrite(motorArr[2][i], 0);
  }
}
