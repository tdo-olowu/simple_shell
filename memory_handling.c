#include "main.h"


/**
 * free_table - releases a char** from memory.
 * useful for tokenify and readcmd
 * @table: the char**
 * Return: none.
 */
void free_table(char **table)
{
	size_t i;

	for (i = 0 ; table[i] != NULL ; ++i)
	{
		free(table[i]);
	}
	free (table);
}


/**
 * free_links - releases a linked list from memory.
 * useful for pathify in this case.
 * @head: the head of the linked list to free.
 * Return: nothing. why return anything?
 */
void free_links(path_list *head)
{
	path_list *current_node = head;
	path_list *next_node = NULL;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->dir);
		free(current_node);
		current_node = next_node;
	}
}


/**
 * cleanup - clean up and exit.
 */
void cleanup(char *buffer, char **tokens, path_list *path_h)
{
	free(buffer);
	free_table(tokens);
	free_links(path_h);
}
