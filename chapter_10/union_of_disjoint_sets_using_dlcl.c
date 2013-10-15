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
void unite_sets(struct node **target_set, struct node **dest_set);
void display(struct node *head);

int main()
{
	struct node *head_of_set_a = NULL;
	struct node *head_of_set_b = NULL;
	char buffer[128];
	char response;
	int value;
	
	do
	{
		printf("Enter a to insert, d to delete, s to search, f to display set A and\nenter h to insert, j to delete, k to search, l to display set B, u to perform union of sets and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to insert in set A: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				if(search(head_of_set_a, value) == NULL)
					if(search(head_of_set_b, value) == NULL)
						insert(&head_of_set_a, value);
					else
						printf("%d already exists in set B\n", value);
				else
					printf("%d already exists in set A\n", value);
				break;
			case 's':
				printf("Enter value to search in set A: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				if(search(head_of_set_a, value) != NULL)
					printf("%d is present in set A\n", value);
				else
					printf("%d is not present in set A\n", value);
				break;
			case 'd':
				printf("Enter value to delete from set A: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				delete(&head_of_set_a, search(head_of_set_a, value));
				break;
			case 'f':
				display(head_of_set_a);
				break;
			case 'h':
				printf("Enter value to insert in set B: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				if(search(head_of_set_b, value) == NULL)
					if(search(head_of_set_a, value) == NULL)
						insert(&head_of_set_b, value);
					else
						printf("%d already exists in set A\n", value);
				else
					printf("%d already exists in set B\n", value);
				break;
			case 'j':
				printf("Enter value to search in set B: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				if(search(head_of_set_b, value) != NULL)
					printf("%d is present in set B\n", value);
				else
					printf("%d is not present in set B\n", value);
				break;
			case 'k':
				printf("Enter value to delete from set B: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				delete(&head_of_set_b, search(head_of_set_b, value));
				break;
			case 'l':
				display(head_of_set_b);
				break;
			case 'u':
				unite_sets(&head_of_set_a, &head_of_set_b);
				display(head_of_set_a);
				break;
			case 'e':
				break;
			default:
				printf("Wrong option chosen. Try again...\n");
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

void unite_sets(struct node **dest_set, struct node **target_set)
{
	struct node *temp;
	(*dest_set)->prev->next = *target_set;
	(*target_set)->prev->next = *dest_set;
	temp = (*target_set)->prev;
	(*target_set)->prev = (*dest_set)->prev;
	(*dest_set)->prev = temp;
	*target_set = NULL;
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

