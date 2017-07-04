#ifndef CONFIG_H
#define CONFIG_H
#include <stdbool.h>
#include "Constants.h"

const char* CONFIG_NAME ;
//allow usage of either wiringPi pins or GPIO pins
enum PinMode { WiringPi, GPIO };
enum Motor {MotorX, MotorY, MotorZ};

enum PinMode ConfiguredPinMode;
//The mapping of each control to its pin.
int motorArr[NUM_MOTORS][NUM_MOTOR_CONTROL_PINS];

int limitSel[NUM_LIMIT_SELECT_PINS];
int limitIn, pwmPin;

extern const char CONFIGURABLE_VALUES[][10];

int ReadConfig();
bool IsNewLine(char* line);
char* Trim(char* string);
char* ToLower(char* string);
int SetConfigValue(const char* name, long value);
bool IsConfigurableValue(char* string);
bool IsIntegerConfigurable(char* string);
void PrintConfig();
#endif