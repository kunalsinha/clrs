#include <stdio.h>
#include <stdlib.h>

void push(int stack[], int *topOfStack, int sizeOfStack, int value);
int pop(int stack[], int *topOfStack);
int isStackFull(int topOfStack, int sizeOfStack);
int isStackEmpty(int topOfStack);

void enqueue(int storageStack[], int *topOfStorage, int sizeOfStorageStack, int value);
int dequeue(int storageStack[], int *topOfStorageStack, int sizeOfStorageStack, int supportStack[], int *topOfSupportStack, int sizeOfSupportStack);

int main()
{
	char response;
	char buffer[512];
	
	const int sizeOfStackA = 4;
	const int sizeOfStackB = 4;
	int stack_a[sizeOfStackA], stack_b[sizeOfStackB];
	int topOfStackA = -1;
	int topOfStackB = -1;
	
	int value;
	
	do
	{
		puts("Press a to enqueue, d to dequeue and e to exit");
		fgets(buffer, 512, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to enqueue: ");
				fgets(buffer, 512, stdin);
				sscanf(buffer, "%d", &value);
				enqueue(stack_a, &topOfStackA, sizeOfStackA, value);
				break;
			case 'd':
				printf("Popped A: %d\n", dequeue(stack_a, &topOfStackA, sizeOfStackA, stack_b, &topOfStackB, sizeOfStackB));
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

void enqueue(int storageStack[], int *topOfStorageStack, int sizeOfStorageStack, int value)
{
	push(storageStack, topOfStorageStack, sizeOfStorageStack, value);
}

int dequeue(int storageStack[], int *topOfStorageStack, int sizeOfStorageStack, int supportStack[], int *topOfSupportStack, int sizeOfSupportStack)
{
	int popped;
	do
	{
		popped = pop(storageStack, topOfStorageStack);
		if(isStackEmpty(*topOfStorageStack))
			break;
		else
			push(supportStack, topOfSupportStack, sizeOfSupportStack, popped);
	}
	while(1);
	
	while(!isStackEmpty(*topOfSupportStack))
		push(storageStack, topOfStorageStack, sizeOfStorageStack, pop(supportStack, topOfSupportStack));
	return popped;
}

void push(int stack[], int *topOfStack, int sizeOfStack, int value)
{
	if(isStackFull(*topOfStack, sizeOfStack))
	{
		printf("Stack Overflow\n");
		exit(-1);
	}
	else
		stack[++*topOfStack] = value;
}

int pop(int stack[], int *topOfStack)
{
	if(isStackEmpty(*topOfStack))
	{
		printf("Stack Underflow\n");
		exit(-1);
	}
	else
	{
		//printf("Top of stack = %d\n", *topOfStack);
		(*topOfStack)--;
		//printf("Top of stack = %d\n", *topOfStack);
		return stack[*topOfStack + 1];
	}
}

int isStackFull(int topOfStack, int sizeOfStack)
{
	if(topOfStack == sizeOfStack - 1)
		return 1;
	else
		return 0;
}

int isStackEmpty(int topOfStack)
{
	if(topOfStack == -1)
		return 1;
	else
		return 0;
}

