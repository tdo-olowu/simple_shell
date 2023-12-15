#include "main.h"


/**
 * hsh_exit - exits the hshell.
 * Return: value to break control of loop.
 */
int hsh_exit(void)
{
	return (-1);
}


/**
 * penv - prints environment variables.
 * @env: envronment to print.
 * Return: none.
 */
void penv(char **env)
{
	int i;

	for (i = 0 ; env[i] != NULL ; ++i)
	{
		printf("%s\n", env[i]);
	}
}
