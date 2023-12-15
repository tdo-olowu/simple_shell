#include "main.h"


/**
 * free_table - frees a null-terminated array of strings
 * @table: an array of strings.
 * Return: none.
 */
void free_table(char **table)
{
	int i;

	printf("freeing table.\n");
	if (table != NULL)
	{
		for (i = 0 ; table[i] != NULL ; ++i)
			free(table[i]);
	}
	free(table);
}


/**
 * free_list - free the list
 * @head: pointer to the address of the list's head.
 * Return: no return, just free memory occupied by the linkedlist.
 */
void free_list(dir_type *head)
{
	dir_type *current_node = head;
	dir_type *next_node = NULL;

	printf("freeing list...\n");
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->dir);
		free(current_node);
		current_node = next_node;
	}
}



/**
 * cleanup - a function for convenience.
 * @line: a string.
 * @table: an array of strings.
 * Return: none.
 */
void cleanup(char *line, char **table)
{
	if (line != NULL)
	{
		printf("About to free line.\n");
		free(line);
	}
	if (table != NULL)
		free_table(table);
}
