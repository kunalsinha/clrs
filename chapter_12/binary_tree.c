#include <stdio.h>
#include <stdlib.h>


struct node
{
	int key;
	struct node *parent;
	struct node *left;
	struct node *right;
};

void insert_node(struct node **root, int key);
struct node *search(struct node *root, int key);
struct node *minimum(struct node *root);
struct node *maximum(struct node *root);
void successor(struct node *root, int key);
void predecessor(struct node *root, int key);
void display_tree_inorder(struct node *root);
void display_tree_preorder(struct node *root);
void delete(struct node **root, struct node *p);

int main()
{
	struct node *root = NULL;
	struct node *temp;
	char buffer[128];
	char response;
	int value;
	
	do
	{
		printf("Enter a to insert, s to search, d to delete, f for successor, g for predecessor, h for minimum, j for maximum, k to display in order, l in preorder and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to insert: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				insert_node(&root, value);
				break;
			case 's':
				printf("Enter value to search: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				if(search(root, value) != NULL)
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
				break;
			case 'k':
				display_tree_inorder(root);
				break;
			case 'l':
				display_tree_preorder(root);
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


void insert_node(struct node **root, int key)
{
	struct node *new_node;
	struct node *traverser;
	struct node *parent;
	new_node = (struct node *) malloc(sizeof(struct node));
	new_node->key = key;
	new_node->left = NULL;
	new_node->right = NULL;
	if(*root == NULL) //Empty tree
	{
		new_node->parent = NULL;
		*root = new_node;
	}
	else
	{
		parent = NULL;
		traverser = *root;
		while(traverser != NULL)
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
}

struct node *search(struct node *root, int key)
{
	if(root == NULL || key == root->key)
		return root;
	else if(key < root->key)
		return search(root->left, key);
	else
		return search(root->right, key);
}

struct node *minimum(struct node *root)
{
	if(root == NULL)
		return NULL;
	else
	{
		while(root->left != NULL)
			root = root->left;
		return root;
	}
}

struct node *maximum(struct node *root)
{
	if(root == NULL)
		return NULL;
	else
	{
		while(root->right != NULL)
			root = root->right;
		return root;
	}
}

void display_tree_inorder(struct node *root)
{
	if(root != NULL)
	{
		display_tree_inorder(root->left);
		printf("%d\n", root->key);
		display_tree_inorder(root->right);
	}
}

void display_tree_preorder(struct node *root)
{
	if(root != NULL)
	{
		printf("%d\n", root->key);
		display_tree_preorder(root->left);
		display_tree_preorder(root->right);
	}
}

void successor(struct node *root, int key)
{
	struct node *p;
	struct node *parent;
	int m;
	p = search(root, key);
	if(p == NULL)
		printf("Node with key %d does not exist\n", key);
	else
	{
		if(p->right != NULL)
			printf("Successor of %d is %d\n", key, minimum(p->right)->key);
		else
		{
			parent = p->parent;
			while(parent != NULL && parent->right == p)
			{
				p = parent;
				parent = p->parent;
			}
			if(parent != NULL)
				printf("Successor of %d is %d\n", key, parent->key);
			else
				printf("%d is the maximum node in the tree\n", key);
		}
	}
}

void predecessor(struct node *root, int key)
{
	struct node *p;
	struct node *parent;
	int m;
	p = search(root, key);
	if(p == NULL)
		printf("Node with key %d does not exist\n", key);
	else
	{
		if(p->left != NULL)
			printf("Predecessor of %d is %d\n", key, maximum(p->left)->key);
		else
		{
			parent = p->parent;
			while(parent != NULL && parent->left == p)
			{
				p = parent;
				parent = p->parent;
			}
			if(parent != NULL)
				printf("Predecessor of %d is %d\n", key, parent->key);
			else
				printf("%d is the minimum node in the tree\n", key);
		}
	}
}

void delete(struct node **root, struct node *p)
{
	struct node *t;
	if(p != NULL)
	{
		if(p->left == NULL && p->right == NULL) //Leaf node
		{
			if(p->parent == NULL) //Root node is to be deleted
				*root = NULL;
			else
			{
				t = p->parent;
				if(p->key < t->key) //To check if the node is left or right child
					t->left = NULL;
				else
					t->right = NULL;
			}
			free(p);
		}
		else if(p->left == NULL || p->right == NULL) //Node with only one child
		{
			if(p->parent == NULL) //root node
			{
				if(p->left == NULL)
					*root = p->right;
				else
					*root = p->left;
			}
			else
			{
				t = p->parent;
				if(p->key < t->key)
				{
					if(p->left == NULL)
						t->left = p->right;
					else
						t->left = p->left;
				}
				else
				{
					if(p->left == NULL)
						t->right = p->right;
					else
						t->right = p->left;
				}
			}
			free(p);
		}
		else //node having two children
		{
			t = minimum(p->right);
			p->key = t->key;
			delete(root, t);
		}
	}
}

