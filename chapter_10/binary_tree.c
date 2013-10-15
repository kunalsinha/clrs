#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	struct node *left;
	struct node *right;
};

void add_node(struct node **root, int value);
void display_tree(struct node *root);

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

void display_tree(struct node *root)
{
	if(root != NULL)
	{
		printf("%d\n", root->key);
		display_tree(root->left);
		display_tree(root->right);
	}
}

