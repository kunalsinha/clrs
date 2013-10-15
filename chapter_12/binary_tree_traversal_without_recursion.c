#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	struct node *left;
	struct node *right;
};

struct stack
{
	struct node *key;
	struct stack *next;
};

struct stack *node_stack;

void add_node(struct node **root, int value);
void display_tree(struct node *root);

void push(struct stack **head, struct node *value);
struct node *pop(struct stack **head);
int isStackEmpty(struct stack *head);

int main()
{
	struct node *root = NULL;
	char buffer[128];
	char response;
	int value;
	
	do
	{
		printf("Enter a to insert a node in the tree, f to display the nodes and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to insert: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				add_node(&root, value);
				break;
/*			case 's':
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
*/
			case 'f':
				display_tree(root);
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

void add_node(struct node **root, int value)
{
	if(*root == NULL)
	{
		*root = (struct node *) malloc(sizeof(struct node));
		(*root)->key = value;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else
	{
		if(value <= (*root)->key)
			add_node(&((*root)->left), value);
		else
			add_node(&((*root)->right), value);
	}
}

//Non-recursive procedure
void display_tree(struct node *root)
{
	while(!isStackEmpty(node_stack) || root != NULL)
	{
		if(root != NULL)
		{
			push(&node_stack, root);
			root = root->left;
		}
		else
		{
			root = pop(&node_stack);
			printf("%d\n", root->key);
			root = root->right;
		}		
	}
}

void push(struct stack **head, struct node *value)
{
	struct stack *newNode;
	newNode = (struct stack *)malloc(sizeof(struct stack));
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

struct node *pop(struct stack **head)
{
	struct stack *traverser;
	if(*head == NULL)
	{
		printf("Stack Underflow\n");
		exit(-1);
	}
	else
	{
		traverser = *head;
		*head = traverser->next;
		return traverser->key;
	}
}

int isStackEmpty(struct stack *head)
{
	if(head == NULL)
		return 1;
	else
		return 0;
}

