#include "main.h"


/**
 * is_a_dir - crudely test if fname is directory name.
 * @cmd: given command.
 * Return: 1 means yes, 0 means no.
 */
int is_a_dir(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (cmd[0] == '/')
		return (1);
	return (0);
}


/**
 * append_dir_node - appends a node to head of dir_type
 * is this even useful anymore?
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



/*
 * append_node - appends a new node to tail of existing node.
 * @tail: tail of existing linked list.
 * @str: string associated with tail.
 * Return: pointer to tail of appended node.
 */
dir_type *append_node(dir_type **tail, char *str)
{
	dir_type *new_tail;
	dir_type *old_tail = *tail;

	new_tail = malloc(sizeof(dir_type));
	if (new_tail == NULL)
		return (NULL);

	new_tail->dir = strdup(str);
	if (new_tail->dir == NULL)
	{
		free(new_tail);
		return (NULL);
	}
	new_tail->next = NULL;

	if (old_tail == NULL)
		old_tail = new_tail;
	else
		old_tail->next = new_tail;

	return (new_tail);
}


/**
 * build_dir_chain - builds linked list of paths from scratch
 * @paths: an array of paths e.g {/bin/, etc.}
 * Return: pointer to head of list.
 */
dir_type *build_dir_chain(char **paths)
{
	int i;
	dir_type *init_tail = NULL;
	dir_type *new_tail = init_tail;

	if (paths == NULL)
		return (NULL);

	for (i = 0 ; paths[i] != NULL ; ++i)
	{
		new_tail = append_node(&new_tail, paths[i]);
		if (new_tail == NULL)
		{
			free_list(init_tail);
			return (NULL);
		}
		if (i == 0)
			init_tail = new_tail;
	}

	return (init_tail);
}
