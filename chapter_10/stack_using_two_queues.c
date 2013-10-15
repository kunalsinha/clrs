#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 8

void enqueue(int queue[], int *head, int *tail, int sizeOfQueue, int value);
int dequeue(int queue[], int *head, int *tail, int sizeOfQueue);
int isQueueFull(int head, int tail);
int isQueueEmpty(int head, int tail);

void push(int storageQueue[], int *headOfStorageQueue, int *tailOfStorageQueue, int sizeOfStorageQueue, int value);
int pop(int storageQueue[], int *headOfStorageQueue, int *tailOfStorageQueue, int sizeOfStorageQueue,
	int supportQueue[], int *headOfSupportQueue, int *tailOfSupportQueue, int sizeOfSupportQueue);

int main()
{
	char response;
	char buffer[512];
	
	const int sizeOfQueueA = 8;
	int queue_a[sizeOfQueueA];
	int headOfQueueA = 0;
	int tailOfQueueA = 0;
	
	const int sizeOfQueueB = 8;
	int queue_b[sizeOfQueueB];
	int headOfQueueB = 0;
	int tailOfQueueB = 0;
	
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
				push(queue_a, &headOfQueueA, &tailOfQueueA, sizeOfQueueA, value);
				break;
			case 'd':
				printf("Popped: %d\n", pop(queue_a, &headOfQueueA, &tailOfQueueA, sizeOfQueueA,
								queue_b, &headOfQueueB, &tailOfQueueB, sizeOfQueueB));
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

void push(int storageQueue[], int *headOfStorageQueue, int *tailOfStorageQueue, int sizeOfStorageQueue, int value)
{
	enqueue(storageQueue, headOfStorageQueue, tailOfStorageQueue, sizeOfStorageQueue, value);
}

int pop(int storageQueue[], int *headOfStorageQueue, int *tailOfStorageQueue, int sizeOfStorageQueue,
	int supportQueue[], int *headOfSupportQueue, int *tailOfSupportQueue, int sizeOfSupportQueue)
{
	int dequeued;
	do
	{
		dequeued = dequeue(storageQueue, headOfStorageQueue, tailOfStorageQueue, sizeOfStorageQueue);
		if(isQueueEmpty(*headOfStorageQueue, *tailOfStorageQueue))
			break;
		else
			enqueue(supportQueue, headOfSupportQueue, tailOfSupportQueue, sizeOfStorageQueue, dequeued);
	}
	while(1);
	
	while(!isQueueEmpty(*headOfSupportQueue, *tailOfSupportQueue))
		enqueue(storageQueue, headOfStorageQueue, tailOfStorageQueue, sizeOfStorageQueue, 
			dequeue(supportQueue, headOfSupportQueue, tailOfSupportQueue, sizeOfSupportQueue));
			
	return dequeued;
}

void enqueue(int queue[], int *head, int *tail, int sizeOfQueue, int value)
{
	if(isQueueFull(*head, *tail))
	{
		printf("Queue overflow\n");
		exit(-1);
	}
	if(*tail == sizeOfQueue-1)
	{
		*tail = 0;
		queue[sizeOfQueue-1] = value;
	}
	else
	{
		(*tail)++;
		queue[*tail-1] = value;
	}
}

int dequeue(int queue[], int *head, int *tail, int sizeOfQueue)
{
	if(isQueueEmpty(*head, *tail))
	{
		printf("Stack Underflow\n");
		exit(-1);
	}
	if(*head == sizeOfQueue-1)
	{
		*head = 0;
		return queue[sizeOfQueue-1];
	}
	else
	{
		(*head)++;
		return queue[*head-1];
	}
}

int isQueueFull(int head, int tail)
{
	if((tail == head-1) || ((head == 0 && tail == QUEUE_SIZE-1)))
		return 1;
	else
		return 0;
}

int isQueueEmpty(int head, int tail)
{
	if(head == tail)
		return 1;
	else
		return 0;
}

