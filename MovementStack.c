#include "MovementStack.h"
#include <stdio.h>
#include <stdlib.h>

Movement* Peek(Stack *stack)
{
	if(stack == NULL || stack->frontPtr == NULL)
		return NULL;
	
	return stack->frontPtr->data;
}

Movement* Pop(Stack* stack)
{
	if(stack == NULL || stack->frontPtr == NULL)
		return NULL;
	
	StackNode *node = stack->frontPtr;
	stack->currentSize--;
	stack->frontPtr = node->nextPtr;
	Movement *data = node->data;
	free(node);
	return data;
}

bool Push(Stack *stack, Movement *data)
{
	if(stack == NULL || data == NULL)
		return false;
	
	StackNode *nodePtr = malloc(sizeof(StackNode));
	if(nodePtr == NULL)
	{
		printf("Unable to allocate memory for StackNode\n");
		return false;
	}
	stack->currentSize++;
	nodePtr->data = data;
	nodePtr->nextPtr = NULL;
	//If there is no front pointer then the queue must be empty
	if(stack->frontPtr == NULL)
		stack->frontPtr = stack->backPtr = nodePtr;
	else
	{
		stack->backPtr->nextPtr = nodePtr;
		stack->backPtr = nodePtr;
	}
	return true;
}

Stack* CreateStack()
{
	Stack *stack = malloc(sizeof(Stack));
	if(stack == NULL)
	{
		printf("Unable to allocate memory\n");
		return NULL;
	}
	stack->frontPtr = NULL;
	stack->backPtr = NULL;
	stack->currentSize = 0;
	return stack;
}