#ifndef CONSTANTS_H
#define CONSTANTS_H

//define some compile time constants

//the number of stepper motors, one per axis = 3
#define NUM_MOTORS 3
//the number of control wires per motor (currently 4)
#define NUM_MOTOR_CONTROL_PINS 4
//the number of pins we need to select the given limit switch wire (currently log(6))
#define NUM_LIMIT_SELECT_PINS 3
//The number of phases each motor has
#define NUM_MOTOR_PHASES 4
//The number of directions in the directions enum (currently None, Positive, Negative)
#define NUM_DIRECTIONS 3

#endif