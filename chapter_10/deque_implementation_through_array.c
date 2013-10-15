#include <stdio.h>
#include <stdlib.h>

#define DEQUE_SIZE 8

void addAtFront(int value);
void addAtBack(int value);
int removeFromFront();
int removeFromBack();
int isDequeFull();
int isDequeEmpty();

int deque[DEQUE_SIZE];
int head = 0;
int tail = 0;

int main()
{
	char response;
	char buffer[512];
	int value;
	do
	{
		puts("Press a to add at front, d to remove from front, j to add at back, l to remove from back and e to exit");
		fgets(buffer, 512, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to add at front: ");
				fgets(buffer, 512, stdin);
				sscanf(buffer, "%d", &value);
				addAtFront(value);
				break;
			case 'd':
				printf("Removed from front: %d\n", removeFromFront());
				break;
			case 'j':
				printf("Enter value to add at back: ");
				fgets(buffer, 512, stdin);
				sscanf(buffer, "%d", &value);
				addAtBack(value);
				break;
			case 'l':
				printf("Removed from back: %d\n", removeFromBack());
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

void addAtFront(int value)
{
	if(isDequeFull())
	{
		printf("Deque Overflow\n");
		exit(-1);
	}
	if(head == 0)
	{
		head = DEQUE_SIZE-1;
		deque[head] = value;
	}
	else
		deque[--head] = value;
}

void addAtBack(int value)
{
	if(isDequeFull())
	{
		printf("Deque Overflow\n");
		exit(-1);
	}
	if(tail == DEQUE_SIZE-1)
	{
		deque[tail] = value;
		tail = 0;
	}
	else
		deque[tail++] = value;
}

int removeFromFront()
{
	if(isDequeEmpty())
	{
		printf("Deque underflow\n");
		exit(-1);
	}
	if(head == DEQUE_SIZE-1)
	{
		head = 0;
		return deque[DEQUE_SIZE-1];
	}
	else
		return deque[head++];
}

int removeFromBack()
{
	if(isDequeEmpty())
	{
		printf("Deque Underflow\n");
		exit(-1);
	}
	if(tail == 0)
	{
		tail = DEQUE_SIZE-1;
		return deque[tail];
	}
	else
		return deque[--tail];
}

int isDequeFull()
{
	if((head-tail == 1) || (head == 0 && tail == DEQUE_SIZE-1))
		return 1;
	else
		return 0;
}

int isDequeEmpty()
{
	if(head == tail)
		return 1;
	else
		return 0;
}

