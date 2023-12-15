#include "lists.h"

/**
 * add_node - adds a bew bide at vefubbubg if a list_t list.
 * @head: pointer to the address of original head.
 * @str: the string for the node
 * 'prepend_node' would have been a better name.
 *
 * Return: the address of new head. NULL if failed.
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new_head;

	new_head = malloc(sizeof(list_t));
	if (new_head == NULL)
		return (NULL);

	new_head->str = strdup(str);
	if (new_head->str == NULL)
	{
		free(new_head);
		return (NULL);
	}
	new_head->len = strlen(str);
	new_head->next = *head;

	*head = new_head;

	return (new_head);
}
