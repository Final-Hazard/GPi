#ifndef MOVEMENT_STACK_H
#define MOVEMENT_STACK_H
#include "Movement.h"
#include <stdbool.h>

typedef struct node
{
	Movement *data;
	struct node *nextPtr;
} StackNode;

typedef struct stack
{
	//store size for convenience, don't use it for any internal queue logic
	int currentSize;
	StackNode *frontPtr;
	//always points to the last element. Only valid if the stack has elements
	StackNode *backPtr;
} Stack;

Movement* Peek(Stack *stack);
//When finished with this data don't forget to free it
Movement* Pop(Stack *stack);
//returns true if push succeeded, false otherwise (can fail due to memory constraints)
bool Push(Stack *stack, Movement *data);
Stack* CreateStack();

#endif