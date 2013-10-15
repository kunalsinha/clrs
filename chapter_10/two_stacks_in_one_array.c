#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 8

void push(int value);
int pop();
int isStackFull();
int isStackEmpty();

int front_stack[STACK_SIZE];
int back_stack[STACK_SIZE];

int topOfFrontStack = -1;
int topOfBackStack = STACK_SIZE;

void pushInFrontStack(int value);
void pushInBackStack(int value);
int popFrontStack();
int popBackStack();
int isStackFull();
int isFrontStackEmpty();
int isBackStackEmpty();

int main()
{
	char response;
	char buffer[512];
	int value;
	do
	{
		puts("Press a to push, d to pop from front stack. j to push and l to pop from back stack and e to exit ");
		fgets(buffer, 512, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to push into front stack: ");
				fgets(buffer, 512, stdin);
				sscanf(buffer, "%d", &value);
				pushInFrontStack(value);
				break;
			case 'd':
				printf("Popped front stack: %d\n", popFrontStack());
				break;
			case 'j':
				printf("Enter value to push into back stack: ");
				fgets(buffer, 512, stdin);
				sscanf(buffer, "%d", &value);
				pushInBackStack(value);
				break;
			case 'l':
				printf("Popped back stack: %d\n", popBackStack());
				break;
			case 'e':
				break;
			default:
				printf("Wrong choice\n");
				break;
		}
	}
	while(response != 'e');
	return 1;
}

void pushInFrontStack(int value)
{
	if(isStackFull())
	{
		printf("Stack Overflow\n");
		exit(-1);
	}
	else
		front_stack[++topOfFrontStack] = value;
}

void pushInBackStack(int value)
{
	if(isStackFull())
	{
		printf("Stack Overflow\n");
		exit(-1);
	}
	else
		back_stack[--topOfBackStack] = value;
}

int popFrontStack()
{
	if(isFrontStackEmpty())
	{
		printf("Stack Underflow in front stack\n");
		exit(-1);
	}
	else
		return front_stack[topOfFrontStack--];
}

int popBackStack()
{
	if(isBackStackEmpty())
	{
		printf("Stack Underflow in back stack\n");
		exit(-1);

	}
	else
		return back_stack[topOfBackStack++];
}

int isStackFull()
{
	if(topOfBackStack-topOfFrontStack == 1)
		return 1;
	else
		return 0;
}

int isFrontStackEmpty()
{
	if(topOfFrontStack == -1)
		return 1;
	else
		return 0;
}

int isBackStackEmpty()
{
	if(topOfBackStack == STACK_SIZE)
		return 1;
	else
		return 0;
}

