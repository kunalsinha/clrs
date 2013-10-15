#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 32

void push(int value);
int pop();
int isStackFull();
int isStackEmpty();

int stack[STACK_SIZE];
int topOfStack = -1;

int main()
{
	char response;
	char buffer[512];
	int value;
	do
	{
		puts("Press a to push, d to pop and e to exit");
		fgets(buffer, 512, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to push: ");
				fgets(buffer, 512, stdin);
				sscanf(buffer, "%d", &value);
				push(value);
				break;
			case 'd':
				printf("Popped: %d\n", pop());
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

void push(int value)
{
	if(isStackFull())
	{
		printf("Stack Overflow\n");
		exit(-1);
	}
	else
		stack[++topOfStack] = value;
}

int pop()
{
	if(isStackEmpty())
	{
		printf("Stack Underflow\n");
		exit(-1);
	}
	else
		return stack[topOfStack--];
}

int isStackFull()
{
	if(topOfStack == STACK_SIZE - 1)
		return 1;
	else
		return 0;
}

int isStackEmpty()
{
	if(topOfStack == -1)
		return 1;
	else
		return 0;
}

