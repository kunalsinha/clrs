#include <stdio.h>
#include <stdlib.h>

#define BLACK 1
#define RED 2

struct node
{
	int key;
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *NIL;

void insert(struct node **root, int key);
//struct node *search(struct node *root, int key);
void display_tree_inorder(struct node *root);

struct node *bst_insert(struct node **root, int key);
void fix_rb_tree(struct node **root, struct node *z);
void left_rotate(struct node **root, struct node *z);
void right_rotate(struct node **root, struct node *z);

int main()
{
	struct node *root;
	char buffer[128];
	char response;
	int value;
	
	NIL = (struct node *) malloc(sizeof(struct node));
	NIL->key = -1;
	NIL->color = BLACK;
	NIL->parent = NULL;
	NIL->left = NULL;
	NIL->right = NULL;
	
	root = NIL;
	
	do
	{
		printf("Enter a to insert, s to search, k to display the red-black tree and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to insert: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				insert(&root, value);
				break;
			/*case 's':
				printf("Enter value to search: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				if(search(root, value) != NIL)
					printf("%d is present\n", value);
				else
					printf("%d is not present\n", value);
				break;
			case 'd':
				printf("Enter value to delete: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				delete(&root, search(root, value));
				break;
			case 'f':
				printf("Which value's successor should be displayed?\n");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				successor(root, value);
				break;
			case 'g':
				printf("Which value's predecessor should be displayed?\n");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				predecessor(root, value);
				break;
			case 'h':
				temp = minimum(root);
				if(temp != NULL)
					printf("Minimum node in the tree is %d\n", temp->key);
				else
					printf("Empty tree\n");
				break;
			case 'j':
				temp = maximum(root);
				if(temp != NULL)
					printf("Maximum node in the tree is %d\n", temp->key);
				else
					printf("Empty tree\n");
				break;*/
			case 'k':
				display_tree_inorder(root);
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

void insert(struct node **root, int key)
{
	struct node *z;
	z = bst_insert(root, key);
	z->color = RED;
	fix_rb_tree(root, z);
}

void fix_rb_tree(struct node **root, struct node *z)
{
	struct node *y;
	while(z->parent->color == RED)
	{
		if(z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if(y != NIL && y->color == RED)
			{
				//Case 1.1
				z->parent->color = y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else //Segmentation fault should come
			{
				if(z == z->parent->right)
				{
					//Case 1.2
					z = z->parent;
					left_rotate(root, z);
				}
				//Case 1.3
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(root, z->parent->parent);
			}
		}
		else
		{
			y = z->parent->parent->left;
			if(y != NIL && y->color == RED)
			{
				//Case 2.1
				z->parent->color = y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if(z == z->parent->left)
				{
					//Case 2.2
					z = z->parent;
					right_rotate(root, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(root, z->parent->parent);
			}
		}
	}
	(*root)->color = BLACK;
}

void left_rotate(struct node **root, struct node *z)
{
	struct node *y;
	y = z->right;
	z->right = y->left;
	if(y->left != NIL)
		y->left->parent = z;
	y->parent = z->parent;
	if(z->parent != NIL)
	{
		if(z = z->parent->left)
			z->parent->left = y;
		else
			z->parent->right = y;
	}
	else
	{
		*root = y;
	}
	y->left = z;
	z->parent = y;
		
}

void right_rotate(struct node **root, struct node *z)
{
	struct node *y;
	y = z->left;
	z->left = y->right;
	if(y->right != NIL)
		y->right->parent = z;
	y->parent = z->parent;
	if(z->parent != NIL)
	{
		if(z == z->parent->left)
			z->parent->left = y;
		else
			z->parent->right = y;
	}
	else
	{
		*root = y;
	}
	y->right = z;
	z->parent = y;
}

/*struct node *search(struct node *root, int key)
{
	
}*/

void display_tree_inorder(struct node *root)
{
	if(root != NIL)
	{
		display_tree_inorder(root->left);
		printf("%d\n", root->key);
		display_tree_inorder(root->right);
	}
}

//BST functions
struct node *bst_insert(struct node **root, int key)
{
	struct node *new_node;
	struct node *traverser;
	struct node *parent;
	new_node = (struct node *) malloc(sizeof(struct node));
	new_node->key = key;
	new_node->left = NIL;
	new_node->right = NIL;
	if(*root == NIL) //Empty tree
	{
		new_node->parent = NIL;
		*root = new_node;
	}
	else
	{
		parent = NIL;
		traverser = *root;
		while(traverser != NIL)
		{
			parent = traverser;
			if(key < traverser->key)
				traverser = traverser->left;
			else
				traverser = traverser->right;
		}
		new_node->parent = parent;
		if(new_node->key < parent->key)
			parent->left = new_node;
		else
			parent->right = new_node;
	}
	return new_node;
}

