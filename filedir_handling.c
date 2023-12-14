#include "main.h"

/**
 * build_path_chain - builds a linked-list of directory paths.
 * @dirs: the PATh variable, preferably.
 * Return: head of linked list, or NULL.
 */
path_list *build_path_chain(char **dirs)
{
	/* if dirs is NULL, return NULL.
	 * else if dirs[0] is NULL, return NULL.
	 * else create the head and set it to dirs[0].
	 * set prev_node to head.
	 * from there, while dirs[i] != NULL,
	 * create a new node. if successful, point prev to new_node.
	 * and point new to NULL. then set prev to new.
	 */
	int i;
	path_list *head;
	path_list *node;
	path_list *prev_node;

	if (dirs == NULL)
		return (NULL);
	if (dirs[0] == NULL)
		return (NULL);
	head = malloc(sizeof(path_list));
	if (head == NULL)
		return (NULL);
	head->dir = strdup(dirs[0]);
	head->next = NULL;
	prev_node = head;
	for (i = 1 ; dirs[i] != NULL ; ++i)
	{
		node = malloc(sizeof(path_list));
		if (node == NULL)
			break;
		node->dir = strdup(dirs[i]);
		/* check if it worked */
		node->next = NULL;
		prev_node->next = node;
		prev_node = node;
	}

	return (head);
}
