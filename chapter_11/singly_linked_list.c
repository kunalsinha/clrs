#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	struct node *next;
};

void insert(struct node **head, int value);
struct node *search(struct node *head, int value);
void delete(struct node **head, struct node *nodeToDelete);
void display(struct node *head);

void insert(struct node **head, int value)
{
	struct node *newNode;
	newNode = (struct node *)malloc(sizeof(struct node));
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

struct node *search(struct node *head, int value)
{
	while(head != NULL)
	{
		if(head->key == value)
			return head;
		else
			head = head->next;
	}
	
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
			*head = nodeToDelete->next;
			free(nodeToDelete);
		}
		else
		{
			traverser = *head;
			while(traverser->next != nodeToDelete)
				traverser = traverser->next;
			traverser->next = nodeToDelete->next;
			free(nodeToDelete);
		}
	}
}

void display(struct node *head)
{
	if(head == NULL)
		printf("Empty list\n");
	else
	{
		do
		{
			printf("%d\t", 	head->key);
			head = head->next;
		}
		while(head != NULL);
		printf("\n");
	}
}

