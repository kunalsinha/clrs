#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	struct node *next;
	struct node *prev;
};

void insert(struct node **head, int value);
struct node *search(struct node *head, int value);
void delete(struct node **head, struct node *nodeToDelete);
void display(struct node *head);

int main()
{
	struct node *head = NULL;
	char buffer[128];
	char response;
	int value;
	
	do
	{
		printf("Enter a to insert, d to delete, s to search, f to display the list and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to insert: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				insert(&head, value);
				break;
			case 's':
				printf("Enter value to search: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				if(search(head, value) != NULL)
					printf("%d is present\n", value);
				else
					printf("%d is not present\n", value);
				break;
			case 'd':
				printf("Enter value to delete: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				delete(&head, search(head, value));
				break;
			case 'f':
				display(head);
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

void insert(struct node **head, int value)
{
	struct node *newNode;
	newNode = (struct node *)malloc(sizeof(struct node));
	newNode->key = value;
	if(*head == NULL)
	{
		newNode->next = newNode;
		newNode->prev = newNode;
		*head = newNode;
	}
	else
	{
		newNode->next = *head;
		(*head)->prev->next = newNode;
		newNode->prev = (*head)->prev;
		(*head)->prev = newNode;
		*head = newNode;
	}
}

struct node *search(struct node *head, int value)
{
	struct node *traverser;
	if(head == NULL)
		return NULL;
	traverser = head;
	do
	{
		if(traverser->key == value)
			return traverser;
		else
			traverser = traverser->next;
	}
	while(traverser != head);
	return NULL;
}

void delete(struct node **head, struct node *nodeToDelete)
{
	struct node *traverser;
	if(nodeToDelete == NULL)
		printf("Value not present in the list\n");
	else
	{
		if(*head == nodeToDelete)
		{
			if(nodeToDelete->next == *head)
			{
				free(nodeToDelete);
				*head = NULL;
			}
			else
			{
				(*head)->prev->next = (*head)->next;
				*head = (*head)->next;
				(*head)->prev = nodeToDelete->prev;
				free(nodeToDelete);
			}
		}
		else
		{
			traverser = *head;
			while(traverser->next != nodeToDelete)
				traverser = traverser->next;
			traverser->next = nodeToDelete->next;
			nodeToDelete->next->prev = traverser;
			free(nodeToDelete);
		}
	}
}

void display(struct node *head)
{
	struct node *traverser;
	if(head == NULL)
		printf("Empty list\n");
	else
	{
		traverser = head;
		do
		{
			printf("%d\t", 	traverser->key);
			traverser = traverser->next;
		}
		while(traverser != head);
		printf("\n");
	}
}

