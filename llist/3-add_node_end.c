#include "lists.h"

/**
 * add_node_end - appends a node to the end of a list_t linked list
 * @head: pointer to the address of the head.
 * @str: the string for the new node.
 * Return: address of new tail, NULL if failed.
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new_tail;
	list_t *current_node;

	new_tail = malloc(sizeof(list_t));

	if (new_tail == NULL)
		return (NULL);
	new_tail->str = strdup(str);
	if (new_tail->str == NULL)
	{
		free(new_tail);
		return (NULL);
	}

	new_tail->len = strlen(str);
	new_tail->next = NULL;

	if (*head == NULL)
		*head = new_tail;
	else
	{
		current_node = *head;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new_tail;
	}

	return (new_tail);
}
