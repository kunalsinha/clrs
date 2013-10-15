#include <stdio.h>
#include <stdlib.h>

#define BLACK 1
#define RED 2

struct interval
{
	int low;
	int high;
};

struct node
{
	struct interval key;
	int max;
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *NIL;

void insert(struct node **root, struct interval i);
//struct node *search(struct node *root, int key);
void display_tree_inorder(struct node *root);

struct node *bst_insert(struct node **root, struct interval i);
void fix_rb_tree(struct node **root, struct node *z);
void left_rotate(struct node **root, struct node *z);
void right_rotate(struct node **root, struct node *z);

struct node *interval_search(struct node *root, struct interval i);

int maximum(int a, int b, int c);

int main()
{
	struct node *root;
	char buffer[128];
	char response;
	int value;
	struct interval i;
	struct node *t;
	
	NIL = (struct node *) malloc(sizeof(struct node));
	NIL->key.low = 0;
	NIL->key.high = 0;
	NIL->max = 0;
	NIL->color = BLACK;
	NIL->parent = NULL;
	NIL->left = NULL;
	NIL->right = NULL;
	
	root = NIL;
	t = NIL;
	
	do
	{
		printf("Enter a to insert an interval, s to search, k to display the red-black tree and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter start of interval: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &i.low);
				printf("Enter end of interval: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &i.high);
				
				insert(&root, i);
				break;
			case 's':
				printf("Enter start of interval to search: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &i.low);
				printf("Enter end of interval to search: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &i.high);
				
				if((t = interval_search(root, i)) != NIL)
					printf("Found interval %d-%d\n", t->key.low, t->key.high);
				else
					printf("Interval not found\n");
				break;
			/*case 'd':
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

void insert(struct node **root, struct interval i)
{
	struct node *z;
	z = bst_insert(root, i);
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
	y->max = z->max;
	z->max = maximum(z->key.high, z->left->max, z->right->max);
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
	y->max = z->max;
	z->max = maximum(z->key.high, z->left->max, z->right->max);
}

/*struct node *search(struct node *root, int key)
{
	
}*/

void display_tree_inorder(struct node *root)
{
	if(root != NIL)
	{
		display_tree_inorder(root->left);
		printf("%d-%d\n", root->key.low, root->key.high);
		display_tree_inorder(root->right);
	}
}

//BST functions
struct node *bst_insert(struct node **root, struct interval i)
{
	struct node *new_node;
	struct node *traverser;
	struct node *parent;
	new_node = (struct node *) malloc(sizeof(struct node));
	new_node->key = i;
	new_node->max = i.high;
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
			if(traverser->max < i.high)
				traverser->max = i.high;
			if(i.low <= traverser->key.low)
				traverser = traverser->left;
			else
				traverser = traverser->right;
		}
		new_node->parent = parent;
		if(new_node->key.low <= parent->key.low)
			parent->left = new_node;
		else
			parent->right = new_node;
	}
	return new_node;
}

int maximum(int a, int b, int c)
{
	if(a>b && a>c)
		return a;
	else if(b>a && b>c)
		return b;
	else
		return c;
}

struct node *interval_search(struct node *root, struct interval i)
{
	struct node *traverser = root;
	printf("i.low = %d\ti.high = %d\n", i.low, i.high);
	printf("traverser->key.low = %d\ttraverser->key.high = %d\n", traverser->key.low, traverser->key.high);
	while(traverser != NIL && (i.high < traverser->key.low || i.low > traverser->key.high))
	{
		printf("In interval %d-%d\n", traverser->key.low, traverser->key.high);
		if(traverser->left != NIL && i.low <= traverser->left->max)
			traverser = traverser->left;
		else
			traverser = traverser->right;
	}
	return traverser;
}

