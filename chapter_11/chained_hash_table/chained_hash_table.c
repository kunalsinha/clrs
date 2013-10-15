#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node
{
	int key;
	struct node *next;
};

//const int m = 41; //Used for division hash function
const int m = 32; //used for multiplication hash function

void insert_in_table(struct node *hash_table[], int key);
struct node *search_in_table(struct node *hash_table[], int key);
void delete_from_table(struct node *hash_table[], int key);
void display_table(struct node *hash_table[]);
int hash(int key);

//Linked list functions
void insert(struct node **head, int value);
struct node *search(struct node *head, int value);
void delete(struct node **head, struct node *nodeToDelete);
void display(struct node *head);

int main()
{
	struct node *hash_table[m];
	char buffer[128];
	char response;
	int value;
	int i;
	for(i=0; i<m; i++)
		hash_table[i] = NULL;
	
	do
	{
		printf("Enter a to insert, s to search, d to delete, f to display the hash table and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter value to insert: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				insert_in_table(hash_table, value);
				break;
			case 's':
				printf("Enter value to search: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				if(search_in_table(hash_table, value) != NULL)
					printf("%d is present\n", value);
				else
					printf("%d is not present\n", value);
				break;
			case 'd':
				printf("Enter value to delete: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				delete_from_table(hash_table, value);
				break;
			case 'f':
				display_table(hash_table);
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

void insert_in_table(struct node *hash_table[], int key)
{
	int index;
	index = hash(key);
	insert(&hash_table[index], key);
}

struct node *search_in_table(struct node *hash_table[], int key)
{
	int index;
	index = hash(key);
	return search(hash_table[index], key);
}

void delete_from_table(struct node *hash_table[], int key)
{
	int index;
	index = hash(key);
	delete(&hash_table[index], search(hash_table[index], key));
}

void display_table(struct node *hash_table[])
{
	int i;
	for(i=0; i < m; i++)
	{
		printf("%d\t", i);
		display(hash_table[i]);
		printf("\n");
	}
}

/*
//Using division method
int hash(int key)
{
	return key % m;
}
*/

//Using multipliclation method
int hash(int key)
{
	double a;
	double n;
	double r;
	double one = 1.0;
	a = (pow(5, 0.5) - 1)/2;
	printf("A = %f\n", a);
	n = modf(key*a, &one);
	printf("key * A = %f\n", key*a);
	printf("(key  * A) mod 1 = %f\n", n);
	r = n*m;
	printf("m * [(key  * A) mod 1] = %f\n", r);
	r -= modf(r, &one);
	printf("floor{m * [(key  * A) mod 1]} = %f\n", r);
	return r;
}

