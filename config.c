#include "config.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char* CONFIG_NAME = "pinout.config";
const int LINE_SIZE = 256;

const char CONFIGURABLE_VALUES[][10] = {"motorxa1", "motorxa2", "motorxb1", "motorxb2", 
"motorya1", "motorya2", "motoryb1", "motoryb2", 
"motorza1", "motorza2", "motorzb1", "motorzb2",
"limitsel0", "limitsel1", "limitsel2", "limitin", "pwmpin", "pinmode"};
//if adding or removing values don't forget to change the list size as well
const int LIST_SIZE = 18;

int main()
{
	if(ReadConfig() != 0)
		printf("error reading\n");
	return 0;
}

int ReadConfig()
{
	FILE *file = fopen(CONFIG_NAME, "r");
	char line[LINE_SIZE];
	char *variable, *value, *unused;
	long nValue;
	bool pinmodeSet = false;
	int returnValue = 0;
	
	if(file == NULL)
	{	
		printf("Error reading file %s\n", CONFIG_NAME);
		return -1;
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
				returnValue = -1;
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
						returnValue = -1;
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
			return -1;
		}
	}
	if(ConfiguredPinMode == GPIO)
	{
		if(pwmPin != 18)
		{
			printf("Only GPIO pin 18 supports PWM\n");
			return -1;
		}
	}
		
	return returnValue;
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
	if(strcmp(name, "motorxa1") == 0){
		motorXA1 = value; return 0;
	}
	if(strcmp(name, "motorxa2") == 0){
		motorXA2 = value; return 0;
	}
	if(strcmp(name, "motorxb1") == 0){
		motorXB1 = value; return 0;
	}
	if(strcmp(name, "motorxb2") == 0){
		motorXB2 = value; return 0;
	}
	if(strcmp(name, "motorya1") == 0){
		motorYA1 = value; return 0;
	}
	if(strcmp(name, "motorya2") == 0){
		motorYA2 = value; return 0;
	}
	if(strcmp(name, "motoryb1") == 0){
		motorYB1 = value; return 0;
	}
	if(strcmp(name, "motoryb2") == 0){
		motorYB2 = value; return 0;
	}
	if(strcmp(name, "motorza1") == 0){
		motorZA1 = value; return 0;
	}
	if(strcmp(name, "motorza2") == 0){
		motorZA2 = value; return 0;
	}
	if(strcmp(name, "motorzb1") == 0){
		motorZB1 = value; return 0;
	}
	if(strcmp(name, "motorzb2") == 0){
		motorZB2 = value; return 0;
	}
	if(strcmp(name, "limitsel0") == 0){
		limitSel0 = value; return 0;
	}
	if(strcmp(name, "limitsel1") == 0){
		limitSel1 = value; return 0;
	}
	if(strcmp(name, "limitsel2") == 0){
		limitSel2 = value; return 0;
	}
	if(strcmp(name, "limitin") == 0){
		limitIn = value; return 0;
	}
	if(strcmp(name, "pwmpin") == 0){
		pwmPin = value; return 0;
	}
	return -1;
}