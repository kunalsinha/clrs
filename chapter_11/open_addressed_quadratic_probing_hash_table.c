#include <stdio.h>
#include <stdlib.h>

#define NIL_VALUE -1;

const int m = 29;

int insert_in_table(int hash_table[], int key);
int search_in_table(int hash_table[], int key);
void display_table(int hash_table[]);
int hash(int key, int index);
int aux_hash(int key);

int main()
{
	int hash_table[m];
	char buffer[128];
	char response;
	int value;
	int i;
	for(i=0; i<m; i++)
		hash_table[i] = NIL_VALUE;
	
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
				if(search_in_table(hash_table, value) != -1)
					printf("%d is present\n", value);
				else
					printf("%d is not present\n", value);
				break;
			/*case 'd':
				printf("Enter value to delete: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &value);
				delete_from_table(hash_table, value);
				break;*/
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

int insert_in_table(int hash_table[], int key)
{
	int i = 0;
	int h;
	while(i < m)
	{
		h = hash(key, i);
		if(hash_table[h] == -1)
		{
			hash_table[h] = key;
			return h;
		}
		i++;
	}
	printf("HashTable overflow\n");
	return -1;
}

int search_in_table(int hash_table[], int key)
{
	int i = 0;
	int h;
	while(i < m)
	{
		h = hash(key, i);
		printf("Hash = %d\n", h);
		if(hash_table[h] == -1)
			return -1;
		if(hash_table[h] == key)
			return h;
		i++;
	}
	return -1;
}

void display_table(int hash_table[])
{
	int i = 0;
	for(i=0; i<m; i++)
	{
		printf("%d\t", i);
		if(hash_table[i] == -1)
			printf("NIL\n");
		else
			printf("%d\n", hash_table[i]);
	}
}

int hash(int key, int index)
{
	double c1, c2;
	c1 = c2 = 0.5;
	int j = (int)(aux_hash(key) + c1 * index + c2 * index * index);
	j = j % m;
	printf("Hash = %d\n", j);
	return j;
}


int aux_hash(int key)
{
	return key % m;
}

