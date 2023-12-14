#include <stdlib.h>
#include "main.h"
/**
 * cleanup - this is the main function.
 * free_table - this is the main  function.
 * free_links - this is the main function.
 * @tokens: a parameter that relates to table.
 * @head: a parameter that relates to links.
 * Return: success.
 */

void free_table(char **tokens)
{
	if (tokens == NULL)
		return;
	for (int i = 0; tokens[i] != NULL; ++i)
	{
		free(tokens[i]);
	}
	free(tokens);
}

void free_links(path_list *head)
{
path_list *current = head;
path_list *next;
	while (current != NULL)
	{
		next = current->next;
		free(current->dir);
		free(current);
		current = next;
	}
}

void cleanup(char *buffer, char **tokens, path_list *head)
{
	free(buffer);
	free_table(tokens);
	free_links(head);
}
