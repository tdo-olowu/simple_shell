#include "main.h"

/**
 * leave - exit the shell.
 * @ptr: will be important in updates.
 * Return: int for loop control.
 */
int leave(void *ptr)
{
	(void)ptr;
	return (-1);
}


/**
 * _env - print environment variables.
 * @ptr: will be important in updates.
 * Return: int for loop control.
 */
int _env(void *ptr)
{
	extern char *environ;
	char *pair;

	while ((pair = strtok(environ, " ")) != NULL)
		printf("%s\n", pair);
	(void)ptr;
	return (1);
}
