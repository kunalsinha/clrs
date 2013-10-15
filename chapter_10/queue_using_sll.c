#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	struct node *next;
};

void insert(struct node **head, struct node **tail, int value);
void delete(struct node **head, struct node **tail);

int main()
{
	struct node *head = NULL;
	struct node *tail = NULL;
	char buffer[128];
	char response;
	int value;
	
	do
	{
		printf("Enter a to enqueue, d to dequeue and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to enqueue: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				insert(&head, &tail, value);
				break;
			case 'd':
				delete(&head, &tail);
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

void insert(struct node **head, struct node **tail, int value)
{
	struct node *newNode;
	newNode = (struct node *)malloc(sizeof(struct node));
	if(newNode == NULL)
	{
		//perform cleanup
		printf("Queue Overflow\n");
		exit(-1);
	}
	newNode->key = value;
	if(*head == NULL)
	{
		newNode->next = NULL;
		*head = newNode;
		*tail = newNode;
	}
	else
	{
		newNode->next = NULL;
		(*tail)->next = newNode;
		*tail = newNode;
	}
}

void delete(struct node **head, struct node **tail)
{
	struct node *traverser;
	if(*head == NULL)
	{
		printf("Queue Underflow\n");
		exit(-1);
	}
	else
	{
		traverser = *head;
		*head = traverser->next;
		printf("Popped: %d\n", traverser->key);
		free(traverser);
		if(*head == NULL)
			*tail == NULL;
	}
}

