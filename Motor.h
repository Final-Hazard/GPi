#ifndef MOTOR_H
#define MOTOR_H
//#Include WiringPi.h

enum MotorPhase {Phase1, Phase2, Phase3, Phase4};
enum Motor {MotorX, MotorY, MotorZ};
//TODO: Remove global motor phases
enum MotorPhase g_MotorXPhase, g_MotorYPhase, g_MotorZPhase;
extern const int MOTOR_PHASE_MIN;
extern const int MOTOR_PHASE_MAX;
//replace 1 with high and 0 with low in final code
//arrray is {A1, A2, B1, B2}. NEVER have two of the same letter active
//Walking through this array in order will produce ClockWise rotation

extern const int MOTOR_PHASE_ARRAY[4][4];

//drive the given motor one step positive (ClockWise)
void StepMotorPositive(enum Motor motor, enum MotorPhase currentPhase);
//drive the given motor one step negative (CounterClockWise)
void StepMotorNegative(enum Motor motor, enum MotorPhase currentPhase);
#endif