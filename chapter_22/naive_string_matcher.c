#include <stdio.h>
#include <string.h>

int find_substring(char *text, int text_size, char *pattern, int pattern_size);
int match_pattern(char *text, char *pattern, int index, int pattern_size);

int main()
{
	char buffer[1024], response;
	char text[1024], pattern[1024];
	int text_size, pattern_size, index;
	do
	{
		printf("Enter a to perform a string search and e to exit\n");
		fgets(buffer, 1024, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Enter a text: ");
				fgets(text, 1024, stdin);
				text_size = strlen(text);
				text[text_size-1] = '\0';
				printf("Enter a pattern to match: ");
				fgets(pattern, 1024, stdin);
				pattern_size = strlen(pattern);
				pattern[pattern_size-1] = '\0';
				index = find_substring(text, text_size, pattern, pattern_size);
				if(index != -1)
					printf("Pattern found at index %d in the text\n", index);
				else
					printf("Pattern not found in the text\n");
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

int find_substring(char *text, int text_size, char *pattern, int pattern_size)
{
	int i, found;
	for(i=0; i<=(text_size-pattern_size-1); i++)
	{
		found = match_pattern(text, pattern, i, pattern_size);
		printf("found = %d\n", found);
		if(found)
			return i;
	}
	return 0;
}

int match_pattern(char *text, char *pattern, int index, int pattern_size)
{
	int i, j;
	j = 0;
	for(i=index; i<(index+pattern_size-1); i++)
	{
		if(*(text+i) != *(pattern+j))
			return 0;
		j++;
	}
	return 1;
}

