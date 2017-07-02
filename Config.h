#ifndef CONFIG_H
#define CONFIG_H
#include <stdbool.h>

extern const char* CONFIG_NAME;
//allow usage of either wiringPi pins or GPIO pins
enum PinMode { WiringPi, GPIO };

enum PinMode ConfiguredPinMode;
//The mapping of each control to its pin.
int motorXA1, motorXA2, motorXB1, motorXB2;
int motorYA1, motorYA2, motorYB1, motorYB2;
int motorZA1, motorZA2, motorZB1, motorZB2;
int limitSel0, limitSel1, limitSel2, limitIn;
int pwmPin;
extern const char CONFIGURABLE_VALUES[][10];


int ReadConfig();
bool IsNewLine(char* line);
char* Trim(char* string);
char* ToLower(char* string);
int SetConfigValue(const char* name, long value);
bool IsConfigurableValue(char* string);
bool IsIntegerConfigurable(char* string);
#endif