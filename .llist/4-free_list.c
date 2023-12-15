#include "lists.h"

/**
 * free_list - get it while offer lasts!
 * @head: pointer to the address of the list's head.
 * Return: no return, just free memory occupied by the linkedlist.
 */
void free_list(list_t *head)
{
	list_t *current_node = head;
	list_t *next_node = NULL;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
}
