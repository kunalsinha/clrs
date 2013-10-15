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
void reverse(struct node **head);
void display(struct node *head);

int main()
{
	struct node *head = NULL;
	char buffer[128];
	char response;
	int value;
	
	do
	{
		printf("Enter a to insert, d to delete, s to search, r to reverse, f to display the list and e to exit\n");
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
			case 'r':
				reverse(&head);
				printf("List reversed\n");
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

void reverse(struct node **head)
{
	struct node *front, *mid, *back;
	if(*head != NULL && (*head)->next != NULL)
	{
		front = *head;
		mid = front->next;
		back = mid->next;
		front->next = NULL;
		while(1)
		{
			mid->next = front;
			front = mid;
			mid = back;
			if(back != NULL)
				back = back->next;
			else
			{
				*head = front;
				break;
			}
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

