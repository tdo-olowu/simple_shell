#include "lists.h"

/**
 * list_len - compute the number of elements in a linked list_t list.
 * @h: head of the list, a pointer to a struct.
 * Return: the number of elements (nodes?) in the list.
 */
size_t list_len(const list_t *h)
{
	const list_t *node = h;
	int count = 0;

	while (node != NULL)
	{
		++count;
		node = node->next;
	}

	return ((size_t)count);
}
