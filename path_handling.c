#include "main.h"


/**
 * append_dir - appends a node to head of dir_type
 * @head: address of head
 * Return: pointer to appended node
 */
dir_type *append_dir_node(dir_type **head, char *path)
{
	dir_type *new_tail;
	dir_type *current_node;

	new_tail = malloc(sizeof(dir_type));
	if (new_tail == NULL)
		return (NULL);
	new_tail->dir = strdup(path);
	if (new_tail->dir == NULL)
	{
		free(new_tail);
		return (NULL);
	}
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



/**
 * free_list - free the list
 * @head: pointer to the address of the list's head.
 * Return: no return, just free memory occupied by the linkedlist.
 */
void free_list(dir_type *head)
{
	dir_type *current_node = head;
	dir_type *next_node = NULL;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->dir);
		free(current_node);
		current_node = next_node;
	}
}
