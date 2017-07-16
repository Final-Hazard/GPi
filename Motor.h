#ifndef MOTOR_H
#define MOTOR_H
#include "Constants.h"
#include "Config.h"

enum MotorPhase {Phase1, Phase2, Phase3, Phase4};

//TODO: Remove global motor phases
enum MotorPhase g_MotorXPhase, g_MotorYPhase, g_MotorZPhase;
extern const int MOTOR_PHASE_MIN;
extern const int MOTOR_PHASE_MAX;

//replace 1 with high and 0 with low in final code
//array is {A1, A2, B1, B2}. NEVER have two of the same letter active
//Walking through this array in order will produce ClockWise rotation
extern const int MOTOR_PHASE_ARRAY[NUM_MOTOR_PHASES][NUM_MOTOR_CONTROL_PINS];

//drive the given motor one step positive (ClockWise)
void StepMotorPositive(enum Motor motor, enum MotorPhase *currentPhase);
//drive the given motor one step negative (CounterClockWise)
void StepMotorNegative(enum Motor motor, enum MotorPhase *currentPhase);
//set the actual low level hardware outputs. 0 for low, 1 for high
void SetMotorOutputs(enum Motor motor, const int outputs[NUM_MOTOR_CONTROL_PINS]);
void Reset();
#endif
