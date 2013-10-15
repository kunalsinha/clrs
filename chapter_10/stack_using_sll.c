#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	struct node *next;
};

void push(struct node **head, int value);
void pop(struct node **head);

int main()
{
	struct node *head = NULL;
	char buffer[128];
	char response;
	int value;
	
	do
	{
		printf("Enter a to push, d to pop and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to push: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				push(&head, value);
				break;
			case 'd':
				pop(&head);
				break;
			case 'e':
				break;
			default:
				printf("Wrong option\n");
				break;
		}
	}
	while(response != 'e');
	return 1;
}

void push(struct node **head, int value)
{
	struct node *newNode;
	newNode = (struct node *)malloc(sizeof(struct node));
	if(newNode == NULL)
	{
		//perform cleanup
		printf("Stack Overflow\n");
		exit(-1);
	}
	newNode->key = value;
	if(*head == NULL)
	{
		newNode->next = NULL;
		*head = newNode;
	}
	else
	{
		newNode->next = *head;
		*head = newNode;
	}
}

void pop(struct node **head)
{
	struct node *traverser;
	if(*head == NULL)
	{
		printf("Stack Underflow\n");
		exit(-1);
	}
	else
	{
		traverser = *head;
		*head = traverser->next;
		printf("Popped: %d\n", traverser->key);
		free(traverser);
	}
}

