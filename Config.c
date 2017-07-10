#include "Config.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <wiringPi.h>
#include "Constants.h"

const char* CONFIG_NAME = "pinout.config";
const int LINE_SIZE = 256;

const char CONFIGURABLE_VALUES[][10] = {"motorxa1", "motorxa2", "motorxb1", "motorxb2", 
"motorya1", "motorya2", "motoryb1", "motoryb2", 
"motorza1", "motorza2", "motorzb1", "motorzb2",
"limitsel0", "limitsel1", "limitsel2", "limitin", "pwmpin", "pinmode"};
//if adding or removing values don't forget to change the list size as well
const int LIST_SIZE = 18;

bool ReadConfig()
{
	FILE *file = fopen(CONFIG_NAME, "r");
	char line[LINE_SIZE];
	char *variable, *value, *unused;
	long nValue;
	bool pinmodeSet = false;
	bool returnValue = true;
	
	if(file == NULL)
	{	
		printf("Error reading file %s\n", CONFIG_NAME);
		return false;
	}
	while(fgets(line, LINE_SIZE, file))
	{
		//We may not have read the entire line.
		//We shouldn't have any config values this long
		//though so it shouldn't matter.
		
		//ignore comment lines
		if(line[0] == '#' || (line[0] == '/' && line[1] == '/'))
		{
			while(!IsNewLine(line))
			{
				fgets(line, LINE_SIZE, file);
				printf("%s", line);
			}
		}
		
		variable = strtok(line, "=");
		value = strtok(NULL, "=");
		if(variable == NULL || value == NULL)
			continue;
		variable = ToLower(Trim(variable));
		value = Trim(value);
		if(IsIntegerConfigurable(variable))
		{
			nValue = strtol(value, &unused, 10);
			if(SetConfigValue(variable, nValue) != 0)
			{
				printf("Unable to configure %s\n", variable);
				returnValue = false;
			}
		}
		else{
			if(IsConfigurableValue(variable))
			{
				if(strcmp(variable, "pinmode") == 0)
				{
					value = ToLower(value);
					if(strcmp(value, "wiringpi") == 0){
						ConfiguredPinMode = WiringPi;
						pinmodeSet = true;
					}
					else if(strcmp(value, "gpio") == 0){
						ConfiguredPinMode = GPIO;
						pinmodeSet = true;
					}
					else
					{
						printf("unknown pinmode '%s'\n", value);
						returnValue = false;
					}
				}
			}
		}
	}
	if(!pinmodeSet)
	{
		printf("Defaulting pinmode to WiringPi\n");
		ConfiguredPinMode = WiringPi;
	}
	fclose(file);
	if(ConfiguredPinMode == WiringPi)
	{
		if(pwmPin != 1)
		{
			printf("Only WiringPi pin 1 supports PWM\n");
			return false;
		}
	}
	if(ConfiguredPinMode == GPIO)
	{
		if(pwmPin != 18)
		{
			printf("Only GPIO pin 18 supports PWM\n");
			return false;
		}
	}
	return returnValue;
}

void PrintConfig()
{
	char axis, letter, number;
	for(int i = 0; i < NUM_MOTORS; i++)
	{
		for(int j = 0; j < NUM_MOTOR_CONTROL_PINS; j++)
		{
			if(i == 0) axis = 'x';
			if(i == 1) axis = 'y';
			if(i == 2) axis = 'z';
			if(j / 2 == 0) letter = 'a';
			else letter = 'b';
			if(j % 2 == 0) number = '1';
			else number = '2';
			printf("motor%c%c%c = %d\n", axis, letter, number, motorArr[i][j]);
		}
	}
	
	for(int i = 0; i < NUM_LIMIT_SELECT_PINS; i++)
	{
		number = '0' + i;
		printf("limitSel%c = %d\n", number, limitSel[i]);
	}
	printf("limitIn = %d\n", limitIn);
	printf("pwmPin = %d\n", pwmPin);
}

bool SetupWiringPi()
{
  if(ConfiguredPinMode == WiringPi){
    wiringPiSetup();
  }
  else if(ConfiguredPinMode == GPIO){
    wiringPiSetupGpio();
  }
  else
    {
      printf("Unable to configure WiringPi");
      return false;
    }
  
  //Set motor pins to out
  for(int i = 0; i < NUM_MOTORS; i++)
    {
      for(int j = 0; j < NUM_MOTOR_CONTROL_PINS; j++)
	{
	  pinMode(motorArr[i][j], OUTPUT);
	}
    }
  //set selector pins to out
  for(int i = 0; i < NUM_LIMIT_SELECT_PINS; i++)
    {
      pinMode(limitSel[i], OUTPUT);
    }
  //set selector pin Input
  pinMode(limitIn, INPUT);
  //set PWM pin
  pinMode(pwmPin, PWM_OUTPUT);
  return true;
}

bool IsNewLine(char* line)
{
	for(int i = 0; i < LINE_SIZE; i++)
	{
		if(line[i] == '\n')
			return true;
	}
	return false;
}

char* Trim(char* string)
{
	int index = 0, len, trimFront = 0, trimBack = 0;
	bool charFound = false;
	char* returnString;
	//trim the front of string
	while(string[index] != '\0')
	{
		if(!charFound && isspace(string[index]))
			trimFront++;
		if(!isspace(string[index]))
			charFound = true;
		index++;
	}
	len = index;
	//trim the back of string
	index--;
	while(index > 0)
	{
		if(isspace(string[index]))
			trimBack++;
		else 
			break;
		index--;
	}
	
	if(len == trimFront)
	{//the entire string is spaces
		string[0] = '\0';
		return string;
	}
	else
	{
		string[len - trimBack] = '\0';
		returnString = &(string[trimFront]);
		return returnString;
	}
}

char* ToLower(char* string)
{
	int index = 0;
	while(string[index] != '\0')
	{
		string[index] = tolower(string[index]);
		index++;
	}
	return string;
}

bool IsConfigurableValue(char* string)
{
	for(int i = 0; i < LIST_SIZE; i++)
	{
		if(strcmp(string, CONFIGURABLE_VALUES[i]) == 0)
			return true;
	}
	printf("%s is not configurable\n", string);
	return false;
}
bool IsIntegerConfigurable(char* string)
{
	if(IsConfigurableValue(string))
	{
		if(strcmp(string, "pinmode") == 0)
			return false;
		else
			return true;
	}
	return false;
}

int SetConfigValue(const char* name, long value)
{
	printf("setting %s to %ld\n", name, value);
	char *subString;
	char fullString[9] = "motorxxx";
	enum Motor motorDir;
	int motorIdx = 0, limitIdx;
	char axis, letter, number;
	subString = strstr(name, "motor");
	if(subString != NULL)
	{
		//will read strings of the format "motorDL#"
		//where D = direction 'x', 'y', 'z'; L = letter 'a', 'b'; # = number '1', '2'
		if(subString[5] != '\0' && subString[6] != '\0' && subString[7] != '\0')
		{
			axis = subString[5]; letter = subString[6]; number = subString[7];
			if((axis == 'x' || axis == 'y' || axis == 'z') && 
				(letter == 'a' || letter == 'b') && 
				(number == '1' || number == '2'))
			{
				if(subString[5] == 'x')
					motorDir = MotorX;
				if(subString[5] == 'y')
					motorDir = MotorY;
				if(subString[5] == 'z')
					motorDir = MotorZ;
				
				if(subString[6] == 'b')
					motorIdx = 2;
				if(subString[7] == '2')
					motorIdx++;
				fullString[5] = axis; fullString[6] = letter; fullString[7] = number;
				if(strcmp(name, fullString) == 0)
				{
					motorArr[motorDir][motorIdx] = value;
					return 0;
				}
			}
		}
	}
	subString = strstr(name, "limitsel");
	if(subString != NULL)
	{
		if(subString[8] != '\0')
		{
			number = subString[8];
			limitIdx = (int) (number - '0');
			if(limitIdx >= 0 && limitIdx < NUM_LIMIT_SELECT_PINS)
			{
				limitSel[limitIdx] = value;
				return 0;
			}
		}
	}
	if(strcmp(name, "limitin") == 0){
		limitIn = value; return 0;
	}
	if(strcmp(name, "pwmpin") == 0){
		pwmPin = value; return 0;
	}
	return -1;
}
