#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 8

void enqueue(int value);
int dequeue();
int isStackFull();
int isStackEmpty();

int queue[QUEUE_SIZE];
int head = 0;
int tail = 0;

int main()
{
	char response;
	char buffer[512];
	int value;
	do
	{
		puts("Press a to queue, d to dequeue and e to exit");
		fgets(buffer, 512, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to queue: ");
				fgets(buffer, 512, stdin);
				sscanf(buffer, "%d", &value);
				enqueue(value);
				break;
			case 'd':
				printf("Dequeued: %d\n", dequeue());
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

void enqueue(int value)
{
	if(isQueueFull())
	{
		printf("Queue overflow\n");
		exit(-1);
	}
	if(tail == QUEUE_SIZE-1)
	{
		tail = 0;
		queue[QUEUE_SIZE-1] = value;
	}
	else
		queue[++tail-1] = value;
}

int dequeue()
{
	if(isQueueEmpty())
	{
		printf("Stack Underflow\n");
		exit(-1);
	}
	if(head == QUEUE_SIZE-1)
	{
		head = 0;
		return queue[QUEUE_SIZE-1];
	}
	else
		return queue[head++];
}

int isQueueFull()
{
	if((tail == head-1) || ((head == 0 && tail == QUEUE_SIZE-1)))
		return 1;
	else
		return 0;
}

int isQueueEmpty()
{
	if(head == tail)
		return 1;
	else
		return 0;
}

